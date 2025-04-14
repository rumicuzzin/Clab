#include <common.h>

// We store the pointers to the GPIO and USART that are used
//  for a specific serial port. To add another serial port
//  you need to select the appropriate values.
struct _SerialPort {
	USART_TypeDef *UART;
	GPIO_TypeDef *GPIO;
	volatile uint32_t MaskAPB2ENR;	// mask to enable RCC APB2 bus registers
	volatile uint32_t MaskAPB1ENR;	// mask to enable RCC APB1 bus registers
	volatile uint32_t MaskAHBENR;	// mask to enable RCC AHB bus registers
	volatile uint32_t SerialPinModeValue;
	volatile uint32_t SerialPinSpeedValue;
	volatile uint32_t SerialPinAlternatePinValueLow;
	volatile uint32_t SerialPinAlternatePinValueHigh;

};
// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
SerialPort USART1_PORT = {USART1,
		GPIOC,
		RCC_APB2ENR_USART1EN, // bit to enable for APB2 bus
		0x00,	// bit to enable for APB1 bus
		RCC_AHBENR_GPIOCEN, // bit to enable for AHB bus
		0xA00,
		0xF00,
		0x770000,  // for USART1 PC10 and 11, this is in the AFR low register
		0x00, // no change to the high alternate function register
		0x00 // default function pointer is NULL
		};

// Buffer to store incoming characters
#define BUFFER 256
//RX completion callback function
void (*rx_complete_callback)(unsigned char *incoming_buff, int incoming_counter);
//TX completion callback function
//void (*completion_function)(uint32_t);


// Two buffers to store incoming characters
unsigned char buffer1[BUFFER];
unsigned char buffer2[BUFFER];

// Variable for keeping track of content sizes
int buffer1Size = 0;
int buffer2Size = 0;

// User terminated character variable
signed char ter_char;
int activeBufferNum = 1; // 1 for buffer1, 2 for buffer2

// Pointer to initialise the active buffer and its size
unsigned char* activeBuffer = buffer1;
int* activeBufferSize = &buffer1Size;

void USART1_EXTI25_IRQHandler() {
	// Check for overrun or frame errors
	if ((USART1->ISR & USART_ISR_FE_Msk) && (USART1->ISR & USART_ISR_ORE_Msk)) {
		return;
	}

	// Checking if max storage capacity has been reached
	if (activeBufferSize == BUFFER) {
		return;
	}

    // Check if data is received
    if (USART1->ISR & USART_ISR_RXNE_Msk)
    {
        // Read data
        unsigned char data = (uint8_t) USART1->RDR;

		// Store the read data in active buffer if there's space
		if (*activeBufferSize < BUFFER) {
			activeBuffer[*activeBufferSize] = data;
			(*activeBufferSize)++;
		}
			// Toggle LEDs to indicate char received
			// Note: probably not needed
			if (data == ter_char) {



				// Switch to the other buffer and process the now-inactive buffer
				if (activeBufferNum == 1) {

					// Parse active buffer contents and size
					rx_complete_callback(buffer1, buffer1Size);

					// Switch active buffer to buffer2
					activeBuffer = buffer2;
					activeBufferSize = &buffer2Size;
					activeBufferNum = 2;
				} else {
					// Process the buffer we're switching from
					rx_complete_callback(buffer2, buffer2Size);

					// Switch active buffer to buffer1
					activeBuffer = buffer1;
					activeBufferSize = &buffer1Size;
					activeBufferNum = 1;
				}

				// Reset the size for the new active buffer
				// Note: need to be able to reset the buffer too
				*activeBufferSize = 0;
 				memset(activeBuffer, 0, BUFFER);
    	}
    }

}

// InitialiseSerial - Initialise the serial port
// Input: baudRate is from an enumerated set
void SerialInitialise(uint32_t baudRate, SerialPort *serial_port, char terminator, void (*rx_parsing)(unsigned char*, int)) {

	rx_complete_callback = rx_parsing;

	// enable clock power, system configuration clock and GPIOC
	// common to all UARTs
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// enable the GPIO which is on the AHB bus
	RCC->AHBENR |= serial_port->MaskAHBENR;

	// set pin mode to alternate function for the specific GPIO pins
	serial_port->GPIO->MODER = serial_port->SerialPinModeValue;

	// enable high speed clock for specific GPIO pins
	serial_port->GPIO->OSPEEDR = serial_port->SerialPinSpeedValue;

	// set alternate function to enable USART to external pins
	serial_port->GPIO->AFR[0] |= serial_port->SerialPinAlternatePinValueLow;
	serial_port->GPIO->AFR[1] |= serial_port->SerialPinAlternatePinValueHigh;

	// enable the device based on the bits defined in the serial port definition
	RCC->APB1ENR |= serial_port->MaskAPB1ENR;
	RCC->APB2ENR |= serial_port->MaskAPB2ENR;

	// Get a pointer to the 16 bits of the BRR register that we want to change
	uint16_t *baud_rate_config = (uint16_t*)&serial_port->UART->BRR; // only 16 bits used!

	// Baud rate calculation from datasheet
	switch(baudRate){
	case BAUD_9600:
		// NEED TO FIX THIS !
		*baud_rate_config = 0x46;  // 115200 at 8MHz
		break;
	case BAUD_19200:
		// NEED TO FIX THIS !
		*baud_rate_config = 0x46;  // 115200 at 8MHz
		break;
	case BAUD_38400:
		// NEED TO FIX THIS !
		*baud_rate_config = 0x46;  // 115200 at 8MHz
		break;
	case BAUD_57600:
		// NEED TO FIX THIS !
		*baud_rate_config = 0x46;  // 115200 at 8MHz
		break;
	case BAUD_115200:
		*baud_rate_config = 0x46;  // 115200 at 8MHz
		break;
	}

	// enable serial port for tx and rx
	serial_port->UART->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

	//Defining the user defined terminating character on initialisation
	ter_char = terminator;
}

void SerialOutputChar(uint8_t data, SerialPort *serial_port) {
	while((serial_port->UART->ISR & USART_ISR_TXE) == 0){
	}
	serial_port->UART->TDR = data;
}

void SerialOutputString(uint8_t *pt, SerialPort *serial_port) {
	uint32_t counter = 0;
	while(*pt) {
		SerialOutputChar(*pt, serial_port);
		counter++;
		pt++;
	}
}

void USART1RX_enableInterrupts() {
	__disable_irq();
	// Generate an interrupt upon receiving data
	USART1->CR1 |= USART_CR1_RXNEIE_Msk;

	// Set priority and enable interrupts
	NVIC_SetPriority(USART1_IRQn, 1);
	NVIC_EnableIRQ(USART1_IRQn);

	__enable_irq();
}



#include <stdint.h>
#include "stm32f303xc.h"
#include <string.h>


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#define ALTFUNCTION 0xA00
#define RXTX 0x770000
#define HIGHSPEED 0xF00
#define BAUDRATE 0x46
#define BUFFER 10
#define LED_OUTPUT 0x5555
#define TERMINATOR '#'


void enableUSART1();
void enableLEDs();
void USART1_SendChar(unsigned char c);
void USART1_SendString(const char* str);


int main(void)
{
    enableUSART1();
    enableLEDs();


    // Buffer to store incoming characters
    unsigned char string[BUFFER];
    int i = 0;


    // Message to send
    const char* message = "this is a string";


    // Variables for timing the message sending
    volatile uint32_t counter = 0;
    const uint32_t send_interval = 1000000; // Arbitrary delay value


    for(;;)
    {
        // Increment counter for timing
        counter++;


        // Send the string periodically without blocking reception
        if (counter >= send_interval) {
            USART1_SendString(message);
            counter = 0; // Reset counter
        }


        // Check for overrun or frame errors
        if ((USART1->ISR & USART_ISR_FE_Msk) || (USART1->ISR & USART_ISR_ORE_Msk))
        {
            // Clear the error flags
            USART1->ICR |= USART_ICR_FECF | USART_ICR_ORECF;
            continue;
        }


        // If we have stored the maximum amount, reset buffer
        if (i >= BUFFER)
        {
            i = 0;
        }


        // Check if data is received
        if (USART1->ISR & USART_ISR_RXNE_Msk)
        {
            // Read data
            unsigned char data = (uint8_t) USART1->RDR;


            // Store the read data
            string[i] = data;
            i++;



            // Check if the received character is the terminator '#'
            if (data == TERMINATOR)
            {
                // Toggle LEDs
                uint8_t* lights = ((uint8_t*)&(GPIOE->ODR)) + 1;
                *lights = !(*lights);


                // Print buffer contents


				USART1_SendString("Buffer contents:");
				for(int j = 0; j < i; j++) {
					USART1_SendChar(string[j]);
				}
				USART1_SendChar('\r');
				USART1_SendChar('\n');


                // Reset buffer index
                i = 0;


                // Confirm # detected and LED toggle by sending a message
                USART1_SendString("# Character detected!");
            }
        }
    }
}


// Function to send a single character
void USART1_SendChar(unsigned char c)
{
    // Wait until the transmit data register is empty
    while(!(USART1->ISR & USART_ISR_TXE_Msk));


    // Write the character to the transmit data register
    USART1->TDR = c;
}


// Function to send a string
void USART1_SendString(const char* str)
{
    while(*str)
    {
        USART1_SendChar(*str++);
    }


    // Send carriage return and line feed for proper line ending in terminal
    USART1_SendChar('\r');
    USART1_SendChar('\n');
}


void enableUSART1()
{
    // Enable GPIO C and USART1's clocks
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN_Msk;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN_Msk;


    // Set GPIO C to use UART as alternate function
    GPIOC->MODER = ALTFUNCTION;
    GPIOC->AFR[0] = RXTX;
    GPIOC->OSPEEDR = HIGHSPEED;


    // Set the baud rate and ready USART 1 for both receive and transmit
    USART1->BRR = BAUDRATE; // Baud rate = 115200
    USART1->CR1 |= USART_CR1_RE_Msk;
    USART1->CR1 |= USART_CR1_TE_Msk;
    USART1->CR1 |= USART_CR1_UE_Msk;
}


void enableLEDs()
{
    // Enable clock for Port E (LEDs)
    RCC->AHBENR |= RCC_AHBENR_GPIOEEN;


    // Get the most significant 16 bits of port mode register as that is where the mode for the LEDs are defined
    uint16_t* portMode = ((uint16_t*)&(GPIOE->MODER))+1;


    // Set the mode of the port pins to output since they are LEDs
    *portMode = LED_OUTPUT;
}













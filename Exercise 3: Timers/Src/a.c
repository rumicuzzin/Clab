// a
/* Basic functionality: implement a timer software module that can trigger a callback
function (using function pointers) at a regular interval. The interval should be passed
as a parameter during the initialisation of the module.*/

#include "../headers/common.h"
// Global variable to store the callback function
typedef void (*callback_t)(void);
callback_t timer_callback = NULL;
uint8_t current_led = 0;
int32_t time_period_ms = 0;

// Enable the clocks for desired peripherals (GPIOA, C and E)
void enable_clocks() {
    // Enable the clock for the GPIO port of the LED
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;
    // Enable the peripheral clock for timer 2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM2EN;;
}

// Initialise the discovery board I/O (just outputs: inputs are selected by default)
void initialise_board() {
    // Get a pointer to the second half word of the MODER register (for outputs pe8-15)
    uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
    *led_output_registers = 0x5555;
    // Set all 8 LED's to output mode
}

// Initialize timer 2 with specified time period and callback function
void timer_init(uint32_t time_period_ms, callback_t cb) {
	// Disable the interrupts while messing around with the settings
	//  otherwise can lead to strange behaviour
	__disable_irq();


    // Store the callback function
    timer_callback = cb; // This stores the callback function to be used in the interrupt handler

    // Disable interrupts for the timer
    NVIC_DisableIRQ(TIM2_IRQn);
    // Clear any pending interrupt
    NVIC_ClearPendingIRQ(TIM2_IRQn);

	// TIM2 is a 32 bit timer
    // Set the timer prescaler
    // Goal is to trigger an interrupt based on the provided time_period_ms
    // time_period_ms = (PSC + 1) * (ARR + 1) / 8_000_000 * 1000

    // For a 1ms timer tick: 8MHz / 8000 = 1kHz timer clock
    TIM2->PSC = 7999;

    // Calculate the auto-reload value based on the desired time period
    // For example, if time_period_ms = 2000 (2 seconds), ARR = 1999
    TIM2->ARR = (time_period_ms - 1);

    // Disable Update Request Source (URS) bit
    // This prevents update events from counter initialization
    //TIM2->CR1 &= ~TIM_CR1_URS;

    // Generate an update event to load the new settings
    TIM2->EGR |= TIM_EGR_UG;
    // Clear the update flag that was set by the UG bit
    TIM2->SR &= ~TIM_SR_UIF;
    // Enable update interrupt for Timer 2
    TIM2->DIER |= TIM_DIER_UIE;

    // Configure and enable Timer 2 interrupt in NVIC
    NVIC_SetPriority(TIM2_IRQn, 1); // Set priority (0 is highest, 3 is lowest)
    NVIC_EnableIRQ(TIM2_IRQn);      // Enable the Timer 2 interrupt in NVIC

    // Re-enable all interrupts (now that we are finished)
    __enable_irq();
}

// Set LED function to be called by the callback
void set_led(void) {
    // When we've reached LED 8, it means all LEDs are lit, so reset and turn all off
    if (current_led >= 8) {
        // Turn all LEDs off by setting bits 24-31 (which reset pins 8-15)
    	GPIOE->BSRR = 0xFF000000;
        // Reset the counter to start over
        current_led = 0;
        return;
    }

    // Calculate which LED to turn on (PE8 through PE15)
    uint16_t led_pin = 1 << (8 + current_led);

    // Turn on the current LED (without turning off others)
    GPIOE->BSRR = led_pin;

    // Move to the next LED
    current_led++;
}

// Enable the timer to start counting
void enable_timer(void) {
    // Enable the Timer 2 counter
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Timer 2 Interrupt Service Routine
void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        // Clear the update interrupt flag
        TIM2->SR &= ~TIM_SR_UIF;

        // Call the callback function if it's not NULL
        if (timer_callback != NULL) {
            timer_callback();
        }
    }
}


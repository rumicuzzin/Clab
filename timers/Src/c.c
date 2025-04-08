#include "../inc/common.h"

int32_t delay = 0;
// Global variable for the one-shot callback
callback_t oneshot_callback = NULL;


void one_shot_trigger(uint32_t  delay_ms, callback_t cb_c) {
    // Store the callback function for later use
    oneshot_callback = cb_c;

    // Disable interrupts while configuring the timer
    __disable_irq();

    // Configure timer for one-shot mode
    // First, stop the timer if it's running
    TIM2->CR1 &= ~TIM_CR1_CEN;

    // Disable the timer interrupt NVIC before clearing flags & clear flags
    NVIC_DisableIRQ(TIM2_IRQn);
    NVIC_ClearPendingIRQ(TIM2_IRQn);


    // Set prescaler to create a 1ms time base (assuming 8MHz clock)
    TIM2->PSC = 7999;  // For 1ms ticks (8MHz / 8000 = 1kHz)
    // Set the auto-reload value based on the desired delay
    TIM2->ARR = delay_ms;

    // Generate an update event to load the new settings
    TIM2->EGR |= TIM_EGR_UG;
    // Clear the update flag that was set by the UG bit
    TIM2->SR &= ~TIM_SR_UIF;
    // Enable update interrupt for Timer 2
    TIM2->DIER |= TIM_DIER_UIE;

    // Set one-pulse mode (OPM=1) - this makes the timer stop after one update event
    TIM2->CR1 |= TIM_CR1_OPM;

    // Clear the uIF flag to not trigger an immediate event
    TIM2->SR &= ~TIM_SR_UIF;
    // Enable update interrupt
    TIM2->DIER |= TIM_DIER_UIE;

    // Configure and enable Timer 3 interrupt in NVIC
    NVIC_SetPriority(TIM2_IRQn, 3);  // Lower priority than TIM2
    NVIC_EnableIRQ(TIM2_IRQn);

    // Re-enable interrupts
    __enable_irq();

    // Start the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

void flash_led(void) {

	// Turn all LEDs off by setting bits 24-31 (which reset pins 8-15)
	GPIOE->BSRR = 0xFF000000;
	// Set LED1 mask
	uint16_t led_pin = 2 << 8;
	// Turn on LED1
	GPIOE->BSRR = led_pin;

}


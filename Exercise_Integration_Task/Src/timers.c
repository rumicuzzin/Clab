#include "../inc/common.h"

// Global variables
callback_t timer_callback = NULL;     // For repeating timer
callback_t oneshot_callback = NULL;   // For one-shot timer
uint32_t x = 0;                       // Value for timer period



// Enable all required peripheral clocks
void enable_clocks(void) {
    // Enable timer clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Add any other clock enables you need (like GPIO clocks)
    // For example: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; // For LED port
}


// Initialize repeating timer
void repeating_timer_init(uint32_t time_period_ms, callback_t cb) {
    // Disable the interrupts while configuring
    __disable_irq();

    // Store the callback function
    timer_callback = cb;

    // Disable interrupts for the timer
    NVIC_DisableIRQ(TIM2_IRQn);
    // Clear any pending interrupt
    NVIC_ClearPendingIRQ(TIM2_IRQn);

    // Set the timer prescaler
    // For a 1ms timer tick: 8MHz / 8000 = 1kHz timer clock
    TIM2->PSC = 7999;

    // Calculate the auto-reload value based on the desired time period
    TIM2->ARR = (time_period_ms - 1);

    // Make sure one-pulse mode is disabled for repeating operation
    TIM2->CR1 &= ~TIM_CR1_OPM;

    // Generate an update event to load the new settings
    TIM2->EGR |= TIM_EGR_UG;
    // Clear the update flag that was set by the UG bit
    TIM2->SR &= ~TIM_SR_UIF;
    // Enable update interrupt for Timer 2
    TIM2->DIER |= TIM_DIER_UIE;

    // Configure and enable Timer 2 interrupt in NVIC
    NVIC_SetPriority(TIM2_IRQn, 2); // Set priority (0 is highest)
    NVIC_EnableIRQ(TIM2_IRQn);      // Enable the Timer 2 interrupt in NVIC

    // Re-enable interrupts
    __enable_irq();

    // Start the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Function to change the period of the repeating timer
void set_new_period(uint32_t new_value) {
    // Stop the timer
    TIM2->CR1 &= ~TIM_CR1_CEN;

    // Set new period
    TIM2->ARR = new_value;

    // Reset the counter value to start fresh
    TIM2->CNT = 0;

    // Restart the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Getter function for x
int get_x(void) {
    return x;
}

// Setter function for x that also updates timer period
void set_x(uint32_t new_value) {
    x = new_value;
    set_new_period(new_value);
}

// One-shot timer function
void one_shot_trigger(uint32_t delay_ms, callback_t cb) {
    // Store the callback function for later use
    oneshot_callback = cb;

    // Disable interrupts while configuring the timer
    __disable_irq();

    // Stop the timer if it's running
    TIM2->CR1 &= ~TIM_CR1_CEN;

    // Disable and clear timer interrupt
    NVIC_DisableIRQ(TIM2_IRQn);
    NVIC_ClearPendingIRQ(TIM2_IRQn);

    // Configure timer
    TIM2->PSC = 7999;  // 1ms tick (8MHz / 8000 = 1kHz)
    TIM2->ARR = delay_ms;
    TIM2->CNT = 0;     // Reset counter

	// Generate an update event to load the new settings
	TIM2->EGR |= TIM_EGR_UG;
	// Clear the update flag that was set by the UG bit
	TIM2->SR &= ~TIM_SR_UIF;
	// Enable update interrupt for Timer 2
	TIM2->DIER |= TIM_DIER_UIE;

    // Set one-pulse mode (OPM=1) - timer stops after one update event
    TIM2->CR1 |= TIM_CR1_OPM;

    // Clear update flag
    TIM2->SR &= ~TIM_SR_UIF;

    // Enable update interrupt
    TIM2->DIER |= TIM_DIER_UIE;

    // Configure timer interrupt in NVIC
    NVIC_SetPriority(TIM2_IRQn, 3); // Lower priority
    NVIC_EnableIRQ(TIM2_IRQn);

    // Re-enable interrupts
    __enable_irq();

    // Start the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

// Timer 2 Interrupt Service Routine
void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        // Clear the update interrupt flag
        TIM2->SR &= ~TIM_SR_UIF;

        // Check if in one-shot mode
        if (TIM2->CR1 & TIM_CR1_OPM) {
            // Call one-shot callback if set
            if (oneshot_callback != NULL) {
                oneshot_callback();
            }
        } else {
            // Call repeating timer callback if set
            if (timer_callback != NULL) {
                timer_callback();
            }
        }
    }
}

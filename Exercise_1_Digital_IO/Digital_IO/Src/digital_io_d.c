
#include "../inc/digital_io_a.h"
#include "../inc/digital_io_b.h"
#include "../inc/digital_io_d.h"


static LedState_t led_move = LED_IDLE;

void new_callback_function(void){
// If there is no delay, act as normal
	if (led_move == LED_IDLE) {
		led_move = LED_MOVE_PENDING;

	}
}


// Timer IRQ handler
void TIM2_IRQHandler(void) {
    // Clear interrupt flag
    TIM2->SR &= ~TIM_SR_UIF;

    // Check if a button press has requested LED movement
    if (led_move == LED_MOVE_PENDING) {
        // Execute LED movement
        next_led();
        led_move = LED_IDLE;
    }
}


// Timer initialization
void initialise_delay(void) {
    // Enable clock for TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configure TIM2 for periodic checking (e.g., every 500ms)
    TIM2->PSC = 7999;          // in terms of 1 ms
    TIM2->ARR = 2999;          // Get a 3 second delay
    TIM2->DIER |= TIM_DIER_UIE;    // Enable update interrupt
    TIM2->CR1 |= TIM_CR1_CEN;      // Enable counter

    // Configure NVIC for TIM2
    NVIC_SetPriority(TIM2_IRQn, 1);
    NVIC_EnableIRQ(TIM2_IRQn);
}

// Function to enable or disable delay mode
void set_delay(int enable) {
    if (enable) {
        initialise_delay();
    } else {
        // Optionally disable timer if not needed
        TIM2->CR1 &= ~TIM_CR1_CEN;
    }
}

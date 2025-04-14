#include "digital_io_d.h"
#include "stm32f303xc.h"
#include <stddef.h>

/* Global variables */
static LedState_t led_move = LED_IDLE; // Current LED movement state
static uint8_t current_led = 0; // Track which LED is currently lit

void next_led(void) {
    // Turn off current LED
    DigitalIO_SetLED(current_led, 0);

    // Move to next LED
    current_led = (current_led + 1) % 8;

    // Turn on new current LED
    DigitalIO_SetLED(current_led, 1);
}


void delay_button_callback(void) {

    // If there is no pending move, request one
    if (led_move == LED_IDLE) {
        led_move = LED_MOVE_PENDING;
    }
}


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

void DigitalIO_InitDelay(uint16_t delay_ms) {
    // Enable clock for TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configure TIM2 for the specified delay
    TIM2->PSC = 7999;                  // 8MHz / 8000 = 1kHz (1ms tick)
    TIM2->ARR = delay_ms - 1;          // Set period to desired delay
    TIM2->CNT = 0;                     // Reset counter
    TIM2->DIER = TIM_DIER_UIE;         // Enable update interrupt
    TIM2->CR1 = TIM_CR1_CEN;           // Enable counter

    // Configure NVIC for TIM2
    NVIC_SetPriority(TIM2_IRQn, 1);
    NVIC_EnableIRQ(TIM2_IRQn);

    // Initialize with LED 0 on
    DigitalIO_SetLED(0, 1);
    current_led = 0;
}

void DigitalIO_SetDelay(int enable) {
    if (enable) {
        // Enable counter
        TIM2->CR1 |= TIM_CR1_CEN;
    } else {
        // Disable counter
        TIM2->CR1 &= ~TIM_CR1_CEN;
    }
}

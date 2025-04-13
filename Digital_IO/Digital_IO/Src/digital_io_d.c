// digital_io_d.c
#include "digital_io_d.h"
#include "stm32f303xc.h"

// Global variable for LED control
static uint8_t current_led = 0;

// Global flag to indicate button press
static volatile uint8_t button_was_pressed = 0;

// Button callback function - sets flag and returns immediately
void delay_button_callback(void) {
    // Just set a flag and return immediately
    button_was_pressed = 1;

    // Visual indication that button press was detected
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    uint8_t saved_state = *led_register;
    *led_register = 0xFF; // All on
    for(volatile uint32_t i = 0; i < 100000; i++); // Brief delay
    *led_register = saved_state; // Restore original state
}

// Timer interrupt handler
void TIM2_IRQHandler(void) {
    // Clear interrupt flag
    TIM2->SR &= ~TIM_SR_UIF;

    // Debug - Toggle LED 7 to indicate timer tick
    static uint8_t toggle_state = 0;
    toggle_state = !toggle_state;

    // Check for button press or automatic timing
    static int auto_counter = 0;
    uint8_t move_led = 0;  // Using uint8_t instead of bool

    // If button was pressed, move LED immediately and reset auto counter
    if (button_was_pressed) {
        button_was_pressed = 0;
        move_led = 1;  // Using 1 instead of true
        auto_counter = 0;  // Reset automatic counter
    }
    // Otherwise, check if it's time for automatic movement
    else if (++auto_counter >= 3) {
        move_led = 1;  // Using 1 instead of true
        auto_counter = 0;
    }

    // If we need to move the LED (from either source)
    if (move_led) {
        // Turn off current LED
        DigitalIO_SetLED(current_led, 0);

        // Move to next LED
        current_led = (current_led + 1) % 8;

        // Turn on new LED
        DigitalIO_SetLED(current_led, 1);
    }
}

// Initialize the timer delay mechanism
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

// Enable or disable the delay mechanism
void DigitalIO_SetDelay(int enable) {
    if (enable) {
        // Enable counter
        TIM2->CR1 |= TIM_CR1_CEN;
    } else {
        // Disable counter
        TIM2->CR1 &= ~TIM_CR1_CEN;
    }
}

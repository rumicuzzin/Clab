/**
 * @file digital_io_b.c
 * @brief Digital I/O implementation with button callback (Part B)
 */

#include "digital_io_b.h"
#include <stddef.h>

/* Callback variables */
ButtonCallback g_buttonCallback = NULL; // Button press callback function
volatile uint8_t g_part_b_active = 0; // Flag to indicate if Part B is active

/* LED state variable - available for all parts */
static uint8_t current_led = 0;

/**
 * @brief Initialize the Digital I/O module with callback
 */
void DigitalIO_InitWithCallback(ButtonCallback callback) {
    // Store the callback function
    g_buttonCallback = callback;

    // Set the active flag
    g_part_b_active = 1;

    // Call the basic initialization from Part A
    DigitalIO_Init();

    // Set up button interrupt
    // Disable interrupts while configuring
    __disable_irq();

    // Enable system configuration controller
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Connect PA0 to EXTI0
    SYSCFG->EXTICR[0] &= ~(0xF); // Clear EXTI0 bits
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; // PA[0] to EXTI0

    // Configure EXTI0 line for rising edge trigger (button press)
    EXTI->RTSR |= EXTI_RTSR_TR0; // Rising edge trigger
    EXTI->IMR |= EXTI_IMR_MR0; // Enable interrupt on line 0

    // Enable EXTI0 interrupt in NVIC
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);

    // Re-enable interrupts
    __enable_irq();
}

/**
 * @brief Set the button press callback function
 */
void DigitalIO_SetButtonCallback(ButtonCallback callback) {
    g_buttonCallback = callback;
}

/**
 * @brief Move to the next LED in sequence
 */
void DigitalIO_MoveLedForward(void) {
    // Turn off current LED
    DigitalIO_SetLED(current_led, 0);

    // Move to next LED
    current_led = (current_led + 1) % 8;

    // Turn on new current LED
    DigitalIO_SetLED(current_led, 1);
}

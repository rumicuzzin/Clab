/**
 * @file digital_io_c.c
 * @brief Digital I/O implementation with encapsulated LED state (Part C)
 */

#include "digital_io_c.h"
#include <stddef.h>

/* Private variables */
static uint8_t ledStates = 0; // Stores the current state of all LEDs
volatile uint8_t g_part_c_active = 0; // Flag to indicate if Part C is active

/**
 * @brief Initialize for Part C - using callback and tracking LED state
 */
void DigitalIO_InitStateTracking(ButtonCallback callback) {
    // Set the active flag
    g_part_c_active = 1;

    // Initialize with callback (uses Part B functionality)
    DigitalIO_InitWithCallback(callback);

    // Initialize LED state to 0 (all off)
    ledStates = 0;
}

/**
 * @brief Custom implementation of SetLED that tracks internal state
 * ONLY USED for Part C demo
 */
void DigitalIO_C_SetLED(uint8_t ledNumber, uint8_t state) {
    // Validate LED number (0-7)
    if (ledNumber > 7)
        return;

    // Update LED state in our internal variable
    if (state)
        ledStates |= (1 << ledNumber); // Set bit
    else
        ledStates &= ~(1 << ledNumber); // Clear bit

    // Update the physical LED register
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    *led_register = ledStates;
}

/**
 * @brief Custom implementation of SetLEDPattern that tracks internal state
 * This is used only for Part C demos
 */
void DigitalIO_C_SetLEDPattern(uint8_t pattern) {
    // Update our internal record of all LED states
    ledStates = pattern;

    // Update the hardware register directly
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    *led_register = pattern;
}

/**
 * @brief Get the state of a specific LED
 */
uint8_t DigitalIO_GetLEDState(uint8_t ledNumber) {
    // Validate LED number (0-7)
    if (ledNumber > 7)
        return 0;

    // Return the state from our internal variable
    return (ledStates & (1 << ledNumber)) ? 1 : 0;
}

/**
 * @brief Get the current pattern of all LEDs
 */
uint8_t DigitalIO_GetLEDPattern(void) {
    return ledStates;
}

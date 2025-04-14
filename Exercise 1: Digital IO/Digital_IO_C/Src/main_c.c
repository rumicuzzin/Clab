/**
 * @file main_c.c
 * @brief Demo for Part C: Encapsulated LED state
 */

#include <stdint.h>
#include "stm32f303xc.h"
#include "digital_io_c.h"

#if !defined(SOFT_FP) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// First callback function - shifts the pattern left
void chase_led(void) {
    // Get current LED pattern from the module
    uint8_t current_pattern = DigitalIO_GetLEDPattern();

    // Shift left by 1
    current_pattern <<= 1;

    // If all LEDs are off, turn on the first one
    if (current_pattern == 0) {
        current_pattern = 1;
    }

    // Update all LEDs at once
    DigitalIO_SetLEDPattern(current_pattern);
}

// Second callback function - toggles every other LED
void toggle_pattern(void) {
    // Get current pattern
    uint8_t current_pattern = DigitalIO_GetLEDPattern();

    // If pattern is 0x55 or 0xAA, flip it
    // Otherwise set to 0x55
    if (current_pattern == 0x55) {
        DigitalIO_SetLEDPattern(0xAA);
    } else if (current_pattern == 0xAA) {
        DigitalIO_SetLEDPattern(0x55);
    } else {
        DigitalIO_SetLEDPattern(0x55);
    }
}

int main(void)
{
    // Initialize with first callback
    DigitalIO_Init(chase_led);

    // Turn on first LED initially
    DigitalIO_SetLED(0, 1);

    uint32_t counter = 0;

    /* Loop forever */
    for(;;) {
        // Demonstrate state retrieval every second
        if (counter % 1000000 == 0) {
            // Get the state of LED 3
            uint8_t led3_state = DigitalIO_GetLEDState(3);

            // Mirror LED 3's state to LED 7 (to demonstrate getters/setters)
            // If LED 3 is on, also turn on LED 7
            if (led3_state) {
                DigitalIO_SetLED(7, 1);
            } else {
                DigitalIO_SetLED(7, 0);
            }
        }

        // Count to ~5 seconds then change the callback
        counter++;
        if (counter == 5000000) {
            // After ~5 seconds, change to the second callback
            DigitalIO_SetButtonCallback(toggle_pattern);

            // Get current pattern and invert it to demonstrate pattern retrieval
            uint8_t current_pattern = DigitalIO_GetLEDPattern();
            DigitalIO_SetLEDPattern(~current_pattern);

            for(volatile uint32_t i = 0; i < 500000; i++);

            // Reset counter
            counter = 0;
        }
    }
}

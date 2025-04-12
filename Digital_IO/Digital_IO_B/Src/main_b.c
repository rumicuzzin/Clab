/**
 * @file main_b.c
 * @brief Demo for Part B: Button callback functionality
 */

#include <stdint.h>
#include "stm32f303xc.h"
#include "digital_io_b.h"

#if !defined(SOFT_FP) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// Global variable to track current LED
uint8_t current_led = 0;

// Callback function - moves to next LED
void next_led(void) {
    // Turn off current LED
    DigitalIO_SetLED(current_led, 0);

    // Move to next LED
    current_led = (current_led + 1) % 8;

    // Turn on new current LED
    DigitalIO_SetLED(current_led, 1);
}

// Alternate callback - toggles all LEDs
void toggle_all_leds(void) {
    static uint8_t all_on = 0;

    if (all_on) {
        // Turn all LEDs off
        DigitalIO_SetLEDPattern(0);
        all_on = 0;
    } else {
        // Turn all LEDs on
        DigitalIO_SetLEDPattern(0xFF);
        all_on = 1;
    }
}

int main(void)
{
    // Initialize with first callback
    DigitalIO_Init(next_led);

    // Turn on LD3 (first LED) initially
    DigitalIO_SetLED(0, 1);
    current_led = 0;

    uint32_t counter = 0;
    uint8_t callback_switched = 0;

    /* Loop forever */
    for(;;) {
        // Count to ~5 seconds then change the callback
        counter++;
        if (counter > 5000000 && !callback_switched) {
            // Change to the second callback
            DigitalIO_SetButtonCallback(toggle_all_leds);

            // Flash LEDs to indicate callback changed
            DigitalIO_SetLEDPattern(0xFF);
            for(volatile uint32_t i = 0; i < 500000; i++);
            DigitalIO_SetLEDPattern(0x00);
            for(volatile uint32_t i = 0; i < 500000; i++);
            DigitalIO_SetLEDPattern(0xFF);
            for(volatile uint32_t i = 0; i < 500000; i++);
            DigitalIO_SetLEDPattern(0x00);

            callback_switched = 1;
        }
    }
}

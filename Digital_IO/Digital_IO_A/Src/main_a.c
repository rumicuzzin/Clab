/**
 * @file main_a.c
 * @brief Demo for Part A: Basic digital I/O functionality
 */

#include <stdint.h>
#include "stm32f303xc.h"
#include "digital_io_a.h"

#if !defined(SOFT_FP) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    // Initialize digital I/O module
    DigitalIO_Init();

    // Turn on LD3 (first LED) initially
    DigitalIO_SetLED(0, 1);

    uint8_t current_led = 0;

    /* Loop forever */
    for(;;) {
        // Check if button is pressed
        if (DigitalIO_ReadButton()) {
            // When button is pressed, move to next LED

            // Turn off current LED
            DigitalIO_SetLED(current_led, 0);

            // Move to next LED (0-7 representing LD3-LD10)
            current_led = (current_led + 1) % 8;

            // Turn on new current LED
            DigitalIO_SetLED(current_led, 1);

            // Simple debounce delay
            for(volatile uint32_t i = 0; i < 300000; i++);

            // Wait for button release
            while(DigitalIO_ReadButton());

            // Additional debounce delay after release
            for(volatile uint32_t i = 0; i < 100000; i++);
        }
    }
}

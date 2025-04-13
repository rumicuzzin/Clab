/**
 * @file IRQHandler.c
 * @brief Common interrupt handlers for all parts
 */

#include "stm32f303xc.h"
#include "digital_io_b.h"
#include <stddef.h>

/* External references to callback functions and active flags */
extern ButtonCallback g_buttonCallback;
extern volatile uint8_t g_part_b_active;
extern volatile uint8_t g_part_c_active;

/**
 * @brief EXTI0 interrupt handler for button press
 * This common handler checks which part is active and calls
 * the appropriate callback function.
 */
void EXTI0_IRQHandler(void) {
    // Check if EXTI0 interrupt occurred
    if (EXTI->PR & EXTI_PR_PR0) {
        // Flash all LEDs briefly for debugging (can be removed for final version)
        uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
        uint8_t old_value = *led_register;

        *led_register = 0xFF;  // All LEDs on
        for(volatile uint32_t i = 0; i < 50000; i++);
        *led_register = 0x00;  // All LEDs off
        for(volatile uint32_t i = 0; i < 50000; i++);

        // Restore previous LED state
        *led_register = old_value;

        // Call the callback function if registered
        if (g_buttonCallback != NULL) {
            g_buttonCallback();
        }

        // Clear the interrupt flag
        EXTI->PR |= EXTI_PR_PR0;
    }
}

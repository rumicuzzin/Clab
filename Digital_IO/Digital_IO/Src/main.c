/**
 * @file main.c
 * @brief Main program for MTRX2700 Digital I/O Lab
 *
 * To demonstrate different parts, uncomment ONE of the DEMO_PART_X defines
 */

#include <stdint.h>
#include "stm32f303xc.h"

#if !defined(SOFT_FP) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* Uncomment ONE of these to select which part to demonstrate */
//#define DEMO_PART_A    /* Basic functionality */
//#define DEMO_PART_B    /* Button callback */
//#define DEMO_PART_C    /* LED state encapsulation */
#define DEMO_PART_D

/*********************************************
 * PART A: Basic Digital I/O functionality
 * Only includes Part A header
 *********************************************/
#ifdef DEMO_PART_A
#include "digital_io_a.h"

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

#endif /* DEMO_PART_A */

/*********************************************
 * PART B: Button Callback
 * Includes Part B header (which includes Part A)
 *********************************************/
#ifdef DEMO_PART_B
#include "digital_io_b.h"

// Global variable to track current LED
static uint8_t current_led = 0;

// Callback function - moves to next LED when button is pressed
void moveLedForward(void) {
    // Turn off current LED
    DigitalIO_SetLED(current_led, 0);

    // Move to next LED
    current_led = (current_led + 1) % 8;

    // Turn on new current LED
    DigitalIO_SetLED(current_led, 1);
}

int main(void)
{
    // Initialize with the callback function
    DigitalIO_InitWithCallback(moveLedForward);

    // Turn on LD3 (first LED) initially
    DigitalIO_SetLED(0, 1);
    current_led = 0;

    /* Loop forever */
    for(;;) {
        // Everything is handled by the interrupt and callback
    }
}

#endif /* DEMO_PART_B */

/*********************************************
 * PART C: LED State Encapsulation
 * Includes Part C header (which includes Parts A & B)
 *********************************************/
#ifdef DEMO_PART_C
#include "digital_io_c.h"

// Callback function - moves to next LED when button is pressed
void chaseLed(void) {
    // Get current LED pattern from the module
    uint8_t current_pattern = DigitalIO_GetLEDPattern();

    // Shift left by 1
    current_pattern <<= 1;

    // If all LEDs are off, turn on the first one
    if (current_pattern == 0) {
        current_pattern = 1;
    }

    // Update all LEDs at once
    DigitalIO_C_SetLEDPattern(current_pattern);
}

// Function to monitor LED states and demonstrate getters
void monitorLed6(void) {
    // Check if LD6 (LED index 3) is on
    uint8_t ld6_state = DigitalIO_GetLEDState(3);

    // Mirror LD6 to LD10 (LED index 7) to demonstrate getters/setters
    DigitalIO_C_SetLED(7, ld6_state);
}

int main(void)
{
    // Initialize with callback and state tracking
    DigitalIO_InitStateTracking(chaseLed);

    // Turn on LD3 (first LED) initially
    DigitalIO_C_SetLED(0, 1);

    /* Loop forever */
    for(;;) {
        // Demonstrate state retrieval by monitoring LD6 and mirroring to LD10
        monitorLed6();

        // Simple delay
        for(volatile uint32_t i = 0; i < 10000; i++);
    }
}

#endif /* DEMO_PART_C */
/*********************************************
 * PART D: Speed Restriction
 * Includes Part D header (which includes Parts A, B & C)
 *********************************************/
#ifdef DEMO_PART_D
#include "digital_io_d.h"
#include "stm32f303xc.h"

int main(void) {
    // Init GPIOs
    DigitalIO_Init();

    // Register the button callback
    DigitalIO_SetButtonCallback(delay_button_callback);  // <<< ADD THIS

    // Init timer with 3-second tick (3 ticks = 9s)
    DigitalIO_InitDelay(3000);

    // EXTI setup (already working in your IRQHandler.c)
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;
    EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->IMR |= EXTI_IMR_MR0;
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);

    for(;;) {
        // Nothing in loop — everything handled by ISRs
    }
}


#endif

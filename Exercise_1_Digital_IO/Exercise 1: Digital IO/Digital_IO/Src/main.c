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
//define DEMO_PART_C    /* LED state encapsulation */
#define DEMO_PART_D

/*********************************************
 * PART A: Basic Digital I/O functionality
 *********************************************/
#ifdef DEMO_PART_A
#include "digital_io_a.h"

int main(void)
{
    // Initialize digital I/O module
    DigitalIO_Init();

    // Start LED sequence with first LED on
    DigitalIO_SetLED(0, 1);

    // Run the button polling loop
    DigitalIO_RunButtonPoll();

    // This point is never reached
    return 0;
}
#endif /* DEMO_PART_A */

/*********************************************
 * PART B: Button Callback
 *********************************************/
#ifdef DEMO_PART_B
#include "digital_io_b.h"

int main(void)
{
    // Initialize with callback and start LED sequence
    DigitalIO_InitWithCallback(DigitalIO_MoveLedForward);

    // Turn on LD3 (first LED) initially
    DigitalIO_SetLED(0, 1);

    // Main loop (empty as everything is handled by interrupts)
    for(;;) {
        // Everything is handled by the interrupt and callback
    }
}
#endif /* DEMO_PART_B */
/*********************************************
 * PART C: LED State Encapsulation
 *********************************************/
#ifdef DEMO_PART_C
#include "digital_io_c.h"

int main(void)
{
    // Initialize with callback and state tracking
    DigitalIO_InitStateTracking();

    // Turn on LD3 (first LED) initially
    DigitalIO_C_SetLED(0, 1);

    // Run the monitoring demo loop
    DigitalIO_RunMonitoringDemo();

    // This point is never reached
    return 0;
}
#endif /* DEMO_PART_C */
/*********************************************
 * PART D: Speed Restriction
 *********************************************/
#ifdef DEMO_PART_D
#include "digital_io_d.h"


int main(void) {
    // Initialize the digital I/O
    DigitalIO_Init();

    // EXPLICIT: Initialize button with callback
    DigitalIO_InitWithCallback(delay_button_callback);

    // Initialize delay mechanism (3 second delay)
    DigitalIO_InitDelay(3000);

    // Main loop
    for(;;) {
        // Everything is handled by the interrupt and callback
    }
}
#endif

/**
 * @file digital_io_b.h
 * @brief Digital I/O interface with button callback (Part B)
 */

#ifndef DIGITAL_IO_B_H
#define DIGITAL_IO_B_H

#include <stdint.h>
#include "stm32f303xc.h"

/**
 * @brief Function pointer type for button callback
 *
 * This function is called when the user button is pressed
 */
typedef void (*ButtonCallback)(void);

// Get function
uint8_t get_led_state();
// Set function
void set_led_state(uint8_t new_val);
/**
 * @brief Initialize the Digital I/O module
 *
 * Configures the LEDs (PE8-PE15) and the User button (PA0) with interrupt
 *
 * @param callback Function to call when button is pressed (can be NULL)
 */
void DigitalIO_Init(ButtonCallback callback);

/**
 * @brief Set the button press callback function
 *
 * @param callback Function to call when button is pressed (can be NULL)
 */
void DigitalIO_SetButtonCallback(ButtonCallback callback);


// Function that gets passed on interupt
void next_led(void);

// Main function
void main_b(void);

#endif /* DIGITAL_IO_B_H */

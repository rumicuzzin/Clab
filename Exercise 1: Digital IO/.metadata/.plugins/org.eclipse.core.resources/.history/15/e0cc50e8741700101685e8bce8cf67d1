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

/**
 * @brief Set the state of a specific LED
 *
 * @param ledNumber LED number (0-7) corresponding to LD3-LD10
 * @param state 0 to turn off, non-zero to turn on
 */
void DigitalIO_SetLED(uint8_t ledNumber, uint8_t state);

/**
 * @brief Set all LEDs according to a pattern
 *
 * @param pattern 8-bit pattern where each bit represents an LED
 */
void DigitalIO_SetLEDPattern(uint8_t pattern);

#endif /* DIGITAL_IO_B_H */

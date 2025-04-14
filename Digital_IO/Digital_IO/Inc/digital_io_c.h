/**
 * @file digital_io_c.h
 * @brief Digital I/O interface with encapsulated LED state (Part C)
 *
 * Builds on parts A and B by adding LED state encapsulation with getters
 */

#ifndef DIGITAL_IO_C_H
#define DIGITAL_IO_C_H

#include "digital_io_b.h"

/**
 * @brief Initialize with callback and state tracking (Part C)
 *
 * @param callback Function to call when button is pressed
 */
void DigitalIO_InitStateTracking(ButtonCallback callback);

/**
 * @brief Set the state of a specific LED with state tracking (Part C)
 *
 * @param ledNumber LED number (0-7) corresponding to LD3-LD10
 * @param state 0 to turn off, non-zero to turn on
 */
void DigitalIO_C_SetLED(uint8_t ledNumber, uint8_t state);

/**
 * @brief Set all LEDs according to a pattern with state tracking (Part C)
 *
 * @param pattern 8-bit pattern where each bit represents an LED
 */
void DigitalIO_C_SetLEDPattern(uint8_t pattern);

/**
 * @brief Get the state of a specific LED
 *
 * @param ledNumber LED number (0-7) corresponding to LD3-LD10
 * @return Current state of the LED (0 = off, 1 = on)
 */
uint8_t DigitalIO_GetLEDState(uint8_t ledNumber);

/**
 * @brief Get the current pattern of all LEDs
 *
 * @return 8-bit pattern representing the state of all LEDs
 */
uint8_t DigitalIO_GetLEDPattern(void);

#endif /* DIGITAL_IO_C_H */

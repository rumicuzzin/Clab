/**
 * @file digital_io_a.h
 * @brief Basic Digital I/O interface for STM32F3 Discovery board (Part A)
 */

#ifndef DIGITAL_IO_A_H
#define DIGITAL_IO_A_H

#include <stdint.h>
#include "stm32f303xc.h"

/**
 * @brief Initialize the Digital I/O module (Part A)
 *
 * Configures the LEDs (PE8-PE15) and the User button (PA0)
 */
void DigitalIO_Init(void);

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

/**
 * @brief Read the current state of the user button
 *
 * @return 1 if button is pressed, 0 if not pressed
 */
uint8_t DigitalIO_ReadButton(void);

#endif /* DIGITAL_IO_A_H */

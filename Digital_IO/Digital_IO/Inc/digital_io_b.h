/**
 * @file digital_io_b.h
 * @brief Digital I/O interface with button callback (Part B)
 *
 * Builds on part A by adding button callback functionality
 */

#ifndef DIGITAL_IO_B_H
#define DIGITAL_IO_B_H

#include "digital_io_a.h"

/**
 * @brief Function pointer type for button callback
 *
 * This function is called when the user button is pressed
 */
typedef void (*ButtonCallback)(void);

/**
 * @brief Initialize the Digital I/O module with button callback (Part B)
 *
 * Configures the LEDs (PE8-PE15) and the User button (PA0) with interrupt
 *
 * @param callback Function to call when button is pressed (can be NULL)
 */
void DigitalIO_InitWithCallback(ButtonCallback callback);

/**
 * @brief Set the button press callback function
 *
 * @param callback Function to call when button is pressed (can be NULL)
 */
void DigitalIO_SetButtonCallback(ButtonCallback callback);

#endif /* DIGITAL_IO_B_H */

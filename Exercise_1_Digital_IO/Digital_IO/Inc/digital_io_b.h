/**
 * @file digital_io_b.h
 * @brief Digital I/O interface with button callback (Part B)
 */

#ifndef DIGITAL_IO_B_H
#define DIGITAL_IO_B_H

#include "digital_io_a.h"

/**
 * @brief Function pointer type for button callback
 */
typedef void (*ButtonCallback)(void);

/**
 * @brief Initialize the Digital I/O module with button callback (Part B)
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

/**
 * @brief Move to the next LED in sequence
 *
 * This function turns off the current LED, advances to the next one,
 * and turns it on.
 */
void DigitalIO_MoveLedForward(void);

#endif /* DIGITAL_IO_B_H */

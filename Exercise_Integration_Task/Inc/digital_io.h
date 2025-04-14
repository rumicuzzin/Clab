/*
 * digital_io.h
 *
 *  Created on: Apr 14, 2025
 *      Author: willrumi
 */

#ifndef DIGITAL_IO_H_
#define DIGITAL_IO_H_

typedef void (*ButtonCallback)(void);

uint8_t get_led_state(void);


void set_led_state(uint8_t new_val);

// Flashed LEDS on
void flash_led(void);

/// turns leds on and off
void set_led(void);

void DigitalIO_SetButtonCallback(ButtonCallback callback);

void DigitalIO_SetLED(uint8_t ledNumber, uint8_t state);
//
//void DigitalIO_SetLEDsFromBinary(uint8_t* binary_string);
//
//void DigitalIO_Init_a(void);

// Activate LED function
void update_leds(uint32_t binary_value);

#endif /* DIGITAL_IO_H_ */

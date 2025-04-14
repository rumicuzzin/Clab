#ifndef DIGITAL_IO_D_H
#define DIGITAL_IO_D_H

#include "digital_io_c.h"
#include <stdint.h>

// LED states for the delay mechanism
typedef enum {
    LED_IDLE,
    LED_MOVE_PENDING
} LedState_t;

// Button callback for delayed LED movement
void delay_button_callback(void);

// Function to move to next LED in the sequence
void next_led(void);

// Initialize the timer for delayed LED movement
void DigitalIO_InitDelay(uint16_t delay_ms);

// Enable or disable the delay mechanism
void DigitalIO_SetDelay(int enable);

#endif // DIGITAL_IO_D_H

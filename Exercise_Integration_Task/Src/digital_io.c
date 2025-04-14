#include <stddef.h>
#include "../inc/common.h"

/* Private variables */
static ButtonCallback buttonCallback = NULL; // Button press callback function
static uint8_t led_state = 0;


// Get function
uint8_t get_led_state(){
	return led_state;
}

// Set function
void set_led_state(uint8_t new_val){
	led_state = new_val;
}

// Flash LED function (common callback for both timer modes)
void flash_led(void) {
    // Turn all LEDs off by setting bits 24-31 (which reset pins 8-15)
    GPIOE->BSRR = 0xFF000000;
    // Set LED1 mask
    uint16_t led_pin = 0xFF << 8;
    // Turn on all Led's
    GPIOE->BSRR = led_pin;
}


// Set LED function to be called by the callback
void set_led(void) {
    // When we've reached LED 8, it means all LEDs are lit, so reset and turn all off
    if (get_led_state() >= 8) {
        // Turn all LEDs off by setting bits 24-31 (which reset pins 8-15)
    	GPIOE->BSRR = 0xFF000000;
        // Reset the counter to start over
        set_led_state(0);
        return;
    }

    // Calculate which LED to turn on (PE8 through PE15)
    uint16_t led_pin = 1 << (8 + get_led_state());

    // Turn on the current LED (without turning off others)
    GPIOE->BSRR = led_pin;

    // Move to the next LED
    set_led_state(get_led_state() +1);
}

void DigitalIO_SetButtonCallback(ButtonCallback callback) {
    buttonCallback = callback;
}

// LED set function from part 1
void DigitalIO_SetLED(uint8_t ledNumber, uint8_t state) {
    // Validate LED number (0-7)
    if (ledNumber > 7)
        return;

    // Get pointer to LED register
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;

    if (state)
    	GPIOE->ODR |= (1 << (ledNumber + 8));  // Set bit
    else
        *led_register &= ~(1 << ledNumber); // Clear bit
}



// Activate LED function
void update_leds(uint32_t binary_value) {
    // Convert the binary value to an 8-bit value for the LEDs
    uint8_t led_value = (uint8_t)(binary_value & 0xFF);

    // Update the LED state using the setter
    set_led_state(led_value);

    // Set each individual LED based on the bits in the value
    for (uint8_t i = 0; i < 8; i++) {
        // Check if bit i is set (1) or clear (0)
        uint8_t bit_state = (led_value >> i) & 0x01;

        // Update the physical LED
        DigitalIO_SetLED(i, bit_state);
    }
}







#include "digital_io_a.h"

/**
 * @brief Initialize the Digital I/O module
 */
void DigitalIO_Init(void) {
    // Enable clocks for GPIOA (button) and GPIOE (LEDs)
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;

    // Configure PE8-PE15 (LEDs) as outputs
    uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
    *led_output_registers = 0x5555; // Set as outputs (01 pattern for each pin)

    // Configure PA0 (User button) as input (default state)

    // Configure with pull-down (button connects to VDD when pressed)
    GPIOA->PUPDR &= ~(0x3);
    GPIOA->PUPDR |= 0x2; // Pull-down (10 pattern)

    // Turn off all LEDs initially
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    *led_register = 0;
}

/**
 * @brief Set the state of a specific LED
 */
void DigitalIO_SetLED(uint8_t ledNumber, uint8_t state) {
    // Validate LED number (0-7)
    if (ledNumber > 7)
        return;

    // Get pointer to LED register
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;

    if (state)
        *led_register |= (1 << ledNumber);  // Set bit
    else
        *led_register &= ~(1 << ledNumber); // Clear bit
}

/**
 * @brief Set all LEDs according to a pattern
 */
void DigitalIO_SetLEDPattern(uint8_t pattern) {
    // Update the hardware register directly
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    *led_register = pattern;
}

/**
 * @brief Read the current state of the user button
 */
uint8_t DigitalIO_ReadButton(void) {
    // Read button state from PA0
    return (GPIOA->IDR & GPIO_IDR_0) ? 1 : 0;
}

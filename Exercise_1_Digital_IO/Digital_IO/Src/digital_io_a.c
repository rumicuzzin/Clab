/**
 * @file digital_io_a.c
 * @brief Basic Digital I/O implementation for STM32F3 Discovery (Part A)
 */

#include "digital_io_a.h"

/**
 * @brief Initialize the Digital I/O module
 *
 * Configures the LEDs (PE8-PE15) and the User button (PA0)
 */
void DigitalIO_Init_a(void) {
    // Enable clocks for GPIOA (button) and GPIOE (LEDs)
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;

    // Configure PE8-PE15 (LEDs) as outputs
    uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
    *led_output_registers = 0x5555; // Set as outputs (01 pattern for each pin)

    // Configure PA0 (User button) as input (default state)
    // No need to modify GPIOA->MODER since input is 00 (default)

    // Configure with pull-down (button connects to VDD when pressed)
    GPIOA->PUPDR &= ~(0x3);
    GPIOA->PUPDR |= 0x2; // Pull-down (10 pattern)

    // Turn off all LEDs initially
    uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    *led_register = 0;
}

/**
 * @brief Set the state of a specific LED
 *
 * @param ledNumber LED number (0-7) corresponding to LD3-LD10
 * @param state 0 to turn off, non-zero to turn on
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
 * @brief Read the current state of the user button
 *
 * @return 1 if button is pressed, 0 if not pressed
 */
uint8_t DigitalIO_ReadButton_a(void) {
    // Read button state from PA0
    return (GPIOA->IDR & GPIO_IDR_0) ? 1 : 0;
}


// main function for a
int main_a(void)
{
    // Initialize digital I/O module
    DigitalIO_Init_a();

    // Turn on LD3 (first LED) initially
    DigitalIO_SetLED(0, 1);

    uint8_t current_led_a = 0;

    /* Loop forever */
    for(;;) {
        // Check if button is pressed
        if (DigitalIO_ReadButton_a()) {
            // When button is pressed, move to next LED

            // Turn off current LED
            DigitalIO_SetLED(current_led_a, 0);

            // Move to next LED (0-7 representing LD3-LD10)
            current_led_a = (current_led_a + 1) % 8;

            // Turn on new current LED
            DigitalIO_SetLED(current_led_a, 1);

            // Simple debounce delay
            for(volatile uint32_t i = 0; i < 300000; i++);

            // Wait for button release
            while(DigitalIO_ReadButton_a());

            // Additional debounce delay after release
            for(volatile uint32_t i = 0; i < 100000; i++);
        }
    }
}

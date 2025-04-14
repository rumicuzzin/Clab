/**
 * @file digital_io_b.c
 * @brief Digital I/O implementation with button callback (Part B)
 */

#include "digital_io_b.h"
#include <stddef.h>

/* Private variables */
static ButtonCallback buttonCallback = NULL; // Button press callback function

/**
 * @brief Initialize the Digital I/O module
 */
void DigitalIO_Init(ButtonCallback callback) {
    // Store the callback function
    buttonCallback = callback;

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

    // Set up button interrupt
    // Disable interrupts while configuring
    __disable_irq();

    // Enable system configuration controller
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Connect PA0 to EXTI0
    SYSCFG->EXTICR[0] &= ~(0xF); // Clear EXTI0 bits
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; // PA[0] to EXTI0

    // Configure EXTI0 line for rising edge trigger (button press)
    EXTI->RTSR |= EXTI_RTSR_TR0; // Rising edge trigger
    EXTI->IMR |= EXTI_IMR_MR0; // Enable interrupt on line 0

    // Enable EXTI0 interrupt in NVIC
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);

    // Re-enable interrupts
    __enable_irq();
}

/**
 * @brief Set the button press callback function
 */
void DigitalIO_SetButtonCallback(ButtonCallback callback) {
    buttonCallback = callback;
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
 * @brief EXTI0 interrupt handler for button press
 *
 * This function must be defined in the global scope as it's an interrupt handler
 */
void EXTI0_IRQHandler(void) {
    // Check if EXTI0 interrupt occurred
    if (EXTI->PR & EXTI_PR_PR0) {
        // Call the callback function if registered
        if (buttonCallback != NULL) {
            buttonCallback();
        }

        // Clear the interrupt flag
        EXTI->PR |= EXTI_PR_PR0;
    }
}

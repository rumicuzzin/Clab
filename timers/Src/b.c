// b
/* Implement a function that can reset the timer with a new period. The period should
not be accessible outside the module scope, use get/set functions to allow outside
modules to change the period. */

#include "../headers/common.h"


static int x = 999; // Private variable
volatile uint8_t button_pressed = 0;

// Prototype function
void set_new_period(uint32_t new_value);

// Getter function to access x from other files
int get_x(void) {
    return x;
}

// Setter function to modify x from other files
void set_x(uint32_t new_value) {
    x = new_value;
    set_new_period(new_value);
}

//Stop the timer to reset the period and then start again
void set_new_period(uint32_t new_value){

	// Stop the timer
	TIM2->CR1 &= ~TIM_CR1_CEN;

	// Set new period
	TIM2->ARR = new_value;  // For 500ms (with prescaler of 7999) sets to half second

	//reset the counter value to start fresh
	TIM2->CNT = 0;

	// Restart the timer
	TIM2->CR1 |= TIM_CR1_CEN;
}

/* Configure GPIO and EXTI for button interrupt */
void GPIO_Button_Init(void)
{
  /* Enable clock for GPIOA and SYSCFG */
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;  // Enable GPIOA clock
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Enable SYSCFG clock

  /* Configure PA0 as input with pull-down */
  GPIOA->MODER &= ~(GPIO_MODER_MODER0); // Input mode (00)
  GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR0); // Clear pull-up/down
  GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;  // Set pull-down (10)

  /* Connect EXTI Line0 to PA0 */
  SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI0); // Clear EXTI line configuration
  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; // PA0 as EXTI source

  /* Configure EXTI Line0 */
  EXTI->IMR |= EXTI_IMR_MR0;    // Enable interrupt on EXTI line 0
  EXTI->RTSR |= EXTI_RTSR_TR0;  // Enable rising trigger
  EXTI->FTSR &= ~EXTI_FTSR_TR0; // Disable falling trigger

  /* Set NVIC priority and enable interrupt */
  NVIC_SetPriority(EXTI0_IRQn, 1); // Set priority
  NVIC_EnableIRQ(EXTI0_IRQn);      // Enable EXTI0 interrupt
}

/* EXTI Line0 interrupt handler */
void EXTI0_IRQHandler(void)
{
  if(EXTI->PR & EXTI_PR_PR0) // Check if EXTI0 interrupt triggered
  {
    /* Clear the EXTI pending bit */
    EXTI->PR = EXTI_PR_PR0;

    /* Set the button_pressed flag to 1 */
    button_pressed += 1;
  }
}


// b
/* Implement a function that can reset the timer with a new period. The period should
not be accessible outside the module scope, use get/set functions to allow outside
modules to change the period. */

#include "../headers/common.h"


static int x = 999; // Private variable

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

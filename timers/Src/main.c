#include <stdint.h>
#include "stm32f303xc.h"
#include "a.h"



int main(void)
{
	enable_clocks();
	initialise_board();

	// set the interrupt handling function
	on_button_press = &chase_led;

	// enable the interrupt for the button
	enable_interrupt();

    /* Loop forever */
	for(;;) {}
}

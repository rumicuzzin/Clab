#include "../inc/digital_io_a.h"
#include "../inc/digital_io_b.h"
//#include "../inc/digital_io_c.h"
#include "../inc/digital_io_d.h"

int main(void){

	// Part A
	// Basic input output polling -> press button -> action LED
	//main_a();

	// Part B
	// This passed through a function pointer of a function  callback
	DigitalIO_Init(next_led);


	// Part D
	// Turn delay on

	// How this works
	/* The button press interupt is already initialised from part B
	 * The interupt handler now has a new callback function as defined below
	 * This then checks if we have set for a delay, if on, the state goes into pending
	 * Timer was initialised in set_delay(), every 3 secs, timer triggers and interrupt
	 * to check if the state is pending, if the state is pending, it will call next_led()
	 * Resulting in a delayed LED switch
	 */
	DigitalIO_SetButtonCallback(new_callback_function);
	set_delay(1);


	while(1){
		if(get_led_state() == 4){
		    // Turn off current LED
		    DigitalIO_SetLED(get_led_state(), 0);

		    // Set new LED state
		    set_led_state(6);  // Setting directly to 6 for clarity

		    // Turn on new LED
		    DigitalIO_SetLED(get_led_state(), 1);
		}

	}
}

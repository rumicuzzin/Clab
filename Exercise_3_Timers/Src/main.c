#include "headers/common.h"

extern int32_t time_period_ms;
extern uint16_t current_led;
extern int32_t delay;
extern uint8_t button_pressed;
uint8_t press_counter = 0;

// Example main function showing how to use the timer module
int main(void) {

	// A
    // Initialize system
    enable_clocks();
    initialise_board();
    time_period_ms = 2000;
    timer_callback = &set_led;
    timer_init(time_period_ms, timer_callback);
    // Start the timer
    enable_timer();
    GPIO_Button_Init();

    // C


    // Main loop
    while (1) {


    	if (button_pressed) {
			// Increment counter when button is pressed
			press_counter++;

			// Call different functions based on press count
			if (press_counter == 1) {
					set_x(get_x());
			}
			else if (press_counter == 2) {
				delay = 3000;
				timer_callback = &flash_led;
				one_shot_trigger(delay, timer_callback);
				// Reset counter after second press
				press_counter = 0;
			}
				// Clear the flag after handling
			button_pressed = 0;
		}
    }

 };


#include "headers/common.h"

extern int32_t time_period_ms;
extern uint16_t current_led;
extern int32_t delay;

// Example main function showing how to use the timer module
int main(void) {

	// A
    // Initialize system
    enable_clocks();
    initialise_board();
    time_period_ms = 2000;
    timer_callback = &set_led;
    // Initialize timer with 2000ms (2 second) interval and set_led callback
    timer_init(time_period_ms, timer_callback);
    // Start the timer
    enable_timer();

    // B
//    set_x(get_x());

    // C
    delay = 3000;
    timer_callback = &flash_led;
    one_shot_trigger(delay, timer_callback);

    // Main loop
    while (1) {

    }
};

/*
 * timer.h
 *
 *  Created on: Apr 14, 2025
 *      Author: willrumi
 */

#ifndef TIMERS_H_
#define TIMERS_H_
#include <stdint.h>


void enable_clocks();
typedef void (*callback_t)(void);

void one_shot_trigger(uint32_t  delay_ms, callback_t cb_c);

// Getter function to access x from other files
int get_x(void);

// Setter function to modify x from other files
void set_x(uint32_t new_value);

//Stop the timer to reset the period and then start again
void set_new_period(uint32_t new_value);

void repeating_timer_init(uint32_t time_period_ms, callback_t cb);
void enable_timer(void);

#endif /* TIMERS_H_ */

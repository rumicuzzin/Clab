/*
 * a.h
 *
 *  Created on: Apr 6, 2025
 *      Author: willrumi
 */

#ifndef A_H_
#define A_H_

typedef void (*callback_t)(void);
extern callback_t timer_callback;
void enable_clocks(void);
void initialise_board(void);
void timer_init(uint32_t time_period_ms, callback_t cb);
void set_led(void);
void enable_timer(void);
int main_a(void);

#endif /* A_H_ */

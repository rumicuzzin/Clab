/*
 * a.h
 *
 *  Created on: Apr 8, 2025
 *      Author: willrumi
 */

#ifndef A_H_
#define A_H_

extern void (*on_button_press)(void);

void EXTI0_IRQHandler(void);
// enable the clocks for desired peripherals (GPIOA, C and E)
void enable_clocks();
// initialise the discovery board I/O (just outputs: inputs are selected by default)
void initialise_board();

void enable_interrupt();


void chase_led();



#endif /* A_H_ */

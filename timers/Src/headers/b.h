/*
 * b.h
 *
 *  Created on: Apr 7, 2025
 *      Author: willrumi
 */

#ifndef HEADERS_B_H_
#define HEADERS_B_H_

// Prototype function
void set_new_period(uint32_t new_value);

// Getter function to access x from other files
int get_x(void);

// Setter function to modify x from other files
void set_x(uint32_t);

//Stop the timer to reset the period and then start again
void set_new_period(uint32_t new_value);

#endif /* HEADERS_B_H_ */

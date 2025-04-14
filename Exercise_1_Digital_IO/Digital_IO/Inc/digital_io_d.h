

#ifndef DIGITAL_IO_D_H_
#define DIGITAL_IO_D_H_

// Create a state machine to determine whether there is a delay or not
typedef enum {
    LED_IDLE,
    LED_MOVE_PENDING
} LedState_t;

void new_callback_function(void);

void initialise_delay(void);

void set_delay(int enable);


#endif /* DIGITAL_IO_D_H_ */

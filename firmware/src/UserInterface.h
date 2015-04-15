#ifndef GMK_USER_INTERFACE_H_
#define GMK_USER_INTERFACE_H_

#include <avr/io.h>

typedef enum Event {
	BUTTON_0_PRESSED = (1 << 0),
	BUTTON_1_PRESSED = (1 << 1),
	BUTTON_2_PRESSED = (1 << 2),
} Event_t;
	

void Print(uint8_t value);

void PrintError(uint8_t value);

void InitUserInterface();

Event_t ProcessInterface();

#endif //GMK_USER_INTERFACE_H_



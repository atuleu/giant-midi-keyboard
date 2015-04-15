#ifndef GMK_USER_INTERFACE_H_
#define GMK_USER_INTERFACE_H_

#include <avr/io.h>

void Print(uint8_t value);

void PrintError(uint8_t value);

void InitUserInterface();

void ProcessInterface();

#endif //GMK_USER_INTERFACE_H_



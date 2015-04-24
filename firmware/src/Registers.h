#ifndef GMK_REGISTERS_H_ 
#define GMK_REGISTERS_H_

#include <communication/communication.h>

void InitRegisters();

extern uint16_t Registers[GMK_USBIF_NUMBER_OF_REGISTERS];


void UpdateEEPROM();




#endif //GMK_DEVICE_PARAMETERS_H_



#ifndef GMK_REGISTERS_H_ 
#define GMK_REGISTERS_H_

#include <communication/communication.h>

void InitRegisters();

uint16_t GetRegister(GmkUsbIFRegister_e address);
void SetRegister(GmkUsbIFRegister_e address);

void UpdateEEPROM();




#endif //GMK_DEVICE_PARAMETERS_H_



#ifndef GMK_USB_H_
#define GMK_USB_H_


//#include "LUFAConfig.h"
#include <LUFA/Drivers/USB/USB.h>
#include "Descriptor.h"

#include "stdint.h"

#include "UserInterface.h"


void InitUSB();
void ProcessUSB();

void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);

#endif //GMK_USB_H_


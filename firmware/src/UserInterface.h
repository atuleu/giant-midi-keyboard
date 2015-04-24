#ifndef GMK_USER_INTERFACE_H_
#define GMK_USER_INTERFACE_H_

#include <avr/io.h>

#define BI_BUTTON_0 0
#define BI_BUTTON_1 1
#define BI_BUTTON_2 2
#define BI_BUTTON_RELEASED 3

typedef enum DeviceError {
	GMK_ERR_NO_ERROR                    = 0,
	GMK_ERR_NO_USB_CONNECTION           = 1,
	GMK_ERR_USB_CONFIGURATION           = 2,
	GMK_ERR_INVALID_HOST_VENDOR_REQUEST = 3,
} DeviceError_e;

typedef enum Event {
	BUTTON_0_PRESSED  = _BV(BI_BUTTON_0),
	BUTTON_1_PRESSED  = _BV(BI_BUTTON_1),
	BUTTON_2_PRESSED  = _BV(BI_BUTTON_2),
	BUTTON_0_RELEASED = _BV(BI_BUTTON_0 + BI_BUTTON_RELEASED),
	BUTTON_1_RELEASED = _BV(BI_BUTTON_1 + BI_BUTTON_RELEASED),
	BUTTON_2_RELEASED = _BV(BI_BUTTON_2 + BI_BUTTON_RELEASED),
} Event_t;
	

void Print(uint8_t value);

void PrintError(DeviceError_e value);

void InitUserInterface();

Event_t ProcessInterface();

#endif //GMK_USER_INTERFACE_H_



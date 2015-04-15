#include "UserInterface.h"

#include "Systime.h"

#define LOOP_IN_MS 250

typedef enum DisplayState {
	PRINT_LSB = 0,
	BLACK_1   = 1,
	PRINT_MSB = 2,
	BLACK_2   = 3,
	NUM_STATES = 4,
	CHANGED = 5
} DisplayState_e;

typedef struct UIData {

	uint8_t error;

	uint8_t value;

	Systime_t loopTime;
	
	DisplayState_e displayState;

} UIData_t;

UIData_t s_UI;


void InitUserInterface() {
	s_UI.error = 0;
	s_UI.value = 0;
	s_UI.loopTime = 0;
	s_UI.displayState = PRINT_LSB;

	//Init LED output;
	// 0 is A10 is PB6
	// 1 is A2  is PF5
	// 2 is A9  is PB5
	// 3 is A3  is PF4
	// 4 is A8  is PB4
	DDRB |= _BV(4) | _BV(5) | _BV(6);
	DDRF |= _BV(4) | _BV(5);
}

#define SET_LED(port,pin,value,bit) do{\
	if ( (value) & ( 1 << bit) ) { \
		PORT ## port |= _BV(pin); \
	} else { \
		PORT ## port &= ~_BV(pin); \
	} \
}while(0)

void PrintLSB(uint8_t value) {
	SET_LED(B,6,value,0);
	SET_LED(F,5,value,1);
	SET_LED(B,5,value,2);
	SET_LED(F,4,value,3);
	SET_LED(B,4,value,4);
}


void Print(uint8_t value) {
	s_UI.value = value & 0x1f;
	s_UI.displayState = CHANGED;
}

#define PrintErrorLSB(err) PrintLSB( (err) | 0x10);


void PrintError(uint8_t error) {
	if(s_UI.error) {
		return;
	}

	s_UI.error = error;
	s_UI.displayState = PRINT_LSB;
	PrintErrorLSB(error);
	s_UI.loopTime = GetSystime() + LOOP_IN_MS;

}



void ProcessInterface() {
	if (s_UI.error == 0 ) {
		if (s_UI.displayState == CHANGED) {
			PrintLSB(s_UI.value);
			s_UI.displayState = PRINT_LSB;
		}
		return;
	}

	if ( (GetSystime() - s_UI.loopTime) > LOOP_IN_MS ) {
		s_UI.displayState += 1;
		if (s_UI.displayState > 3) {
			s_UI.displayState = 0;
		}
		switch(s_UI.displayState) {
		case PRINT_LSB :
			PrintErrorLSB(s_UI.error & 0x0f);
			break;
		case BLACK_1:
		case BLACK_2:
			PrintLSB(0x10);
			break;
		case  PRINT_MSB:
			PrintErrorLSB( (s_UI.error & 0xf0) >> 4);
			break;
		}

		s_UI.loopTime += LOOP_IN_MS;
	}
	
}


#include "UserInterface.h"

#include "Systime.h"

#define DISPLAY_LOOP_MS 250
#define BUTTON_ON_THRESHOLD 40



typedef enum DisplayState {
	PRINT_LSB = 0,
	BLACK_1   = 1,
	PRINT_MSB = 2,
	BLACK_2   = 3,
	NUM_STATES = 4,
	CHANGED = 5
} DisplayState_e;

typedef struct ButtonData {
	uint8_t state;
	Systime_t pushedOnDate;
} ButtonData_t;

typedef struct UIData {

	uint8_t error;

	uint8_t value;

	Systime_t displayLoopTime;
	
	DisplayState_e displayState;
	ButtonData_t buttons[3];

	Event_t lastEvents;
	Event_t currentEvents;

} UIData_t;

UIData_t s_UI;


void InitUserInterface() {
	s_UI.error = 0;
	s_UI.value = 0;
	s_UI.displayLoopTime = 0;
	s_UI.displayState = PRINT_LSB;
	s_UI.lastEvents = 0x0;
	s_UI.currentEvents = 0x0;
	for(unsigned int i = 0 ; i < 3; ++i) {
		s_UI.buttons[i].state = 0x00;
	}
	//Init LED output;
	// 0 is A10 is PB6
	// 1 is A2  is PF5
	// 2 is A9  is PB5
	// 3 is A3  is PF4
	// 4 is A8  is PB4
	DDRB |= _BV(4) | _BV(5) | _BV(6);
	DDRF |= _BV(4) | _BV(5);

	DDRF &= ~(_BV(0) | _BV(1));
	PORTF &= ~(_BV(0) | _BV(1));
	DDRE &= ~_BV(6);
	PORTE &= ~_BV(6);
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


void PrintError(uint8_t error) {
	if(s_UI.error) {
		return;
	}

	s_UI.error = error;
	s_UI.displayState = PRINT_LSB;
	PrintLSB(error & 0x0f);
	s_UI.displayLoopTime = GetSystime() + DISPLAY_LOOP_MS;

}



Event_t ProcessInterface() {
	Systime_t currentTime = GetSystime();

	Event_t pressed = 0x00;
	Event_t toReturn = 0x00;
	// I0 : A5 : PF0
	// I1 : D7 : PE6  
	// I2 : A4 : PF1
	uint8_t pf = PINF;
	uint8_t pe = PINE;
	
	if ( (pf & _BV(0)) == 0x00 ) {
		pressed |= BUTTON_0_PRESSED;
	}	
	
	if ( (pe & _BV(6)) == 0x00 ) {
		pressed |= BUTTON_1_PRESSED;
	}	

	
	if ( (pf & _BV(1)) == 0x00 ) {
		pressed |= BUTTON_2_PRESSED;
	}

	for (unsigned int i = 0; i < 3 ; ++i ) {
		if ( (pressed & (1 << i)) == 0 ) {
			s_UI.buttons[i].state = 0x0;
			continue;
		}

		if (s_UI.buttons[i].state == 0x00 ) {
			s_UI.buttons[i].pushedOnDate = currentTime;
			s_UI.buttons[i].state = 0x01;
			continue;
		}

		if (s_UI.buttons[i].state == 0x01 && 
		    (currentTime - s_UI.buttons[i].pushedOnDate) > BUTTON_ON_THRESHOLD ) {
			s_UI.buttons[i].state = 0x02;
			toReturn |= (1 << i);
		}
	}


	if (s_UI.error == 0 ) {
		if (s_UI.displayState == CHANGED) {
			PrintLSB(s_UI.value);
			s_UI.displayState = PRINT_LSB;
		}
		return toReturn;
	}

	if ( (currentTime - s_UI.displayLoopTime) > DISPLAY_LOOP_MS ) {
		s_UI.displayState += 1;
		if (s_UI.displayState > 3) {
			s_UI.displayState = 0;
		}
		switch(s_UI.displayState) {
		case PRINT_LSB :
			PrintLSB(s_UI.error & 0x0f);
			break;
		case BLACK_1:
			PrintLSB(0x00);
			break;
		case BLACK_2:
			PrintLSB(0x10);
			break;
		case  PRINT_MSB:
			PrintLSB( ((s_UI.error & 0xf0) >> 4) | 0x10);
			break;
		}

		s_UI.displayLoopTime += DISPLAY_LOOP_MS;
	}

	return toReturn;
}


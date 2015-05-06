#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "Systime.h"
#include "UserInterface.h"
#include "USB.h"
#include "KeyReader.h"
#include "Registers.h"

/* SetupHardware is setting up all global register */

void SetupHardware () {
	MCUSR &= ~(1 << WDRF);
	wdt_disable(); //disbale it
	
	//extracted from Caterina Bootloaer
	

	//no prescale of F_CPU
	clock_prescale_set(clock_div_1);

	//rest of the init here
	InitUserInterface();
	InitUSB();

	sei();
	InitRegisters();
	
	InitSystime();

	InitKeyReader();
}

#define LOOP_IN_MS 1000

int main (void) {
	SetupHardware();

	StartKeyReader();
	while(1) {		
		Event_t evs = ProcessInterface();
		ProcessKeyReader();
		ProcessUSB();


		if(evs & BUTTON_1_PRESSED) {
			DecrementOctave();
		}
		if(evs & BUTTON_2_PRESSED ) {
			IncrementOctave();
		}


	}
}

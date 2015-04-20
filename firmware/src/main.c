#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "Systime.h"
#include "UserInterface.h"
#include "USB.h"
#include "KeyReader.h"

/* SetupHardware is setting up all global register */

void SetupHardware () {
	MCUSR &= ~(1 << WDRF);
	wdt_disable(); //disbale it
	
	//extracted from Caterina Bootloaer
	

	//no prescale of F_CPU
	clock_prescale_set(clock_div_1);

	//rest of the init here
	InitUserInterface();
	USB_Init();
	PrintError(0x01);

	sei();

	InitSystime();

	InitKeyReader();
}

#define LOOP_IN_MS 1000

int main (void) {
	SetupHardware();

	StartKeyReader();
	while(1) {		
		Event_t evs = ProcessInterface();
		ProcessUSB(evs);
		MIDI_EventPacket_t * midiEvent = ReadNextKeyEvent();
		if ( midiEvent == NULL) {
			continue;
		}
		
		if ( midiEvent->Data1 & 0xf0 == MIDI_COMMAND_NOTE_ON) {
			//Event is a note ON, we display 5 MSB of note's velocity
			Print(midiEvent->Data3);
		}
	}
}

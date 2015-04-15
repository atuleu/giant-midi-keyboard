#include "Systime.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile Systime_t s_Systime;

ISR(TIMER0_COMPA_vect) {
	s_Systime += 1;
}

void InitSystime() {
   
	// Enables interupt output compare
	TIMSK0 |= _BV(OCIE0A);
	
	TCCR0A |= _BV(WGM01); // CTC mode, reset TCNT0 on OCR0A value

	OCR0A = 249; // Compares every 1ms at 16MHz / 64 clock.

	TCNT0 = 0; //starts at 0
	
	s_Systime = 0;

	// clock is F_CPU / 64
	TCCR0B |= (_BV(CS01) | _BV(CS00) );

	//enables interrupt
	sei();
}


Systime_t GetSystime() {

	Systime_t curSystime;
	uint8_t sSREG = SREG;
	cli();


	curSystime = s_Systime;
	
	SREG = sSREG;

	return curSystime;

}

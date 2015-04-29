#include "KeyReader.h"

#include <avr/io.h>

#include <communication/communication.h>
#include "Systime.h"

#define KEY_DATA_SIZE 4
#define KEY_DATA_MASK (KEY_DATA_SIZE - 1)

#define EVENTS_RB_SIZE 16
#define EVENTS_RB_MASK (EVENTS_RB_SIZE - 1)

typedef struct EventRingBufer {
	MIDI_EventPacket_t events[EVENTS_RB_SIZE];
	uint8_t tail,head,size;
} EventRingBufer_t;

#define RBE_SIZE(rbe) rbe.size

#define RBE_HEAD(rbe) rbe.events[rbe.head]

#define RBE_TAIL(rbe) rbe.events[rbe.tail]

#define RBE_IS_EMPTY(rbe) (rbe.size == 0)

#define RBE_IS_FULL(rbe) ( rbe.size == EVENTS_RB_SIZE )

#define RBE_INCREMENT_TAIL(rbe) do { \
	rbe.tail = (rbe.tail + 1) & EVENTS_RB_MASK; \
	rbe.size += 1; \
}while(0)

#define RBE_INCREMENT_HEAD(rbe) do { \
	rbe.head = (rbe.head + 1) & EVENTS_RB_MASK; \
	rbe.size -= 1; \
}while(0)


#define RBE_INIT(rbe) do { \
	 rbe.tail = 0; \
	 rbe.head = 0; \
	 rbe.size = 0; \
}while(0)


#define MAX_OCTAVE (NUM_KEYS - 1)


typedef void(*SelectorFPtr)();

typedef struct KeyData {
	// read ring buffer
	uint8_t  readCount;
	uint8_t  processCount;
	uint8_t  pressCount;
	uint8_t  lastVelocity;
	uint16_t values[KEY_DATA_SIZE];
	
	//data to send via SPI
	uint8_t bytes[3];
	SelectorFPtr selectChip;
} KeyData_t;


typedef enum Keys {
	// On Chip 0
	C_1        = 0,//0,
	C_SHARP_1  = 4,//1,
	D_1        = 8,//2,
	D_SHARP_1  = 12,//3,
	E_1        = 16,//4,
	F_1        = 19,//5,
	F_SHARP_1  = 21,//6,
	G_1        = 23,//7,
	// On Chip 2
	G_SHARP_1  = 1,//8,
	A_1        = 5,//9,
	A_SHARP_1  = 9,//10,
	B_1        = 13,//11,
	//On Chip 3
	C_2        = 2,//12,
	C_SHARP_2  = 6,//13,
	D_2        = 10,//14,
	D_SHARP_2  = 14,//15,
	E_2        = 17,//16,
	F_2        = 20,//17,
	F_SHARP_2  = 22,//18,
	G_2        = 24,//19,
	//On chip 4
	G_SHARP_2  = 3,//20,
	A_2        = 7,//21,
	A_SHARP_2  = 11,//22,
	B_2        = 15,//23,
	C_3        = 18,//24,
	
	NUM_KEYS   = 25,//25
} Keys_e;

typedef struct KeyReader {
	uint8_t keyReadIndex;
	uint8_t byteReadIndex;

	// we "ring buffer" the read. We keep the total amount of key read
	// (in a byte),m and the number processed. Therefore we can safely
	// delay process of 255 key before problem arise (i.e. we should
	// stop read key). Since we read 25 key in 2ms, it will take 20ms
	// for that condition to be raised. And it could only arised if
	// there is a buffer overflow of event that delay the storage of
	// new event. However every 5ms the Events should be polled by the
	// Host.  In case an overflow happen, it delay the processing of
	// the values. But since they are buffered, it is likely we do not
	// miss any event. We should just not consider in the processing
	// that just only one value have been added, but several.
	uint8_t readCount;
	uint8_t processCount;
	uint8_t processCountIndex; // == processCount % NUM_KEYS

	KeyData_t keys[NUM_KEYS];
	uint8_t octave;
	EventRingBufer_t events;
} KeyReader_t;

KeyReader_t s_KR;


void SelectChip0() {
	PORTD &= ~_BV(2);
}

void SelectChip1() {
	PORTD &= ~_BV(1);
}

void SelectChip2() {
	PORTD &= ~_BV(6);
}

void SelectChip3() {
	PORTB &= ~_BV(7);
}


void UnselectAllChip() {
	PORTD |= _BV(1) | _BV(2) | _BV(6);
	PORTB |= _BV(7);
}

void InitChip(const Keys_e * keysFromChipIndex, SelectorFPtr selector) {
	for ( unsigned int chipIndex = 0; chipIndex < 8; ++chipIndex) {
		uint8_t i = keysFromChipIndex[chipIndex];
		if ( i >= NUM_KEYS ) {
			continue;
		}

		s_KR.keys[i].readCount = 0;
		s_KR.keys[i].processCount = 0;
		s_KR.keys[i].pressCount = 0;
		s_KR.keys[i].lastVelocity = 0;		
		s_KR.keys[i].selectChip = selector;
		s_KR.keys[i].bytes[0] = 0x01;
		s_KR.keys[i].bytes[1] = 0x80 | ((chipIndex & 0x07 ) << 4);
		s_KR.keys[i].bytes[2] = 0x00;
				
	}

}

void InitKeyReader() {
	// === Init SS pins ===
	// CS0: 0  : PD2	
	// CS1: 2  : PD1
	// CS2: 12 : PD6
	// CS3: 11 : PB7
	DDRD |= _BV(1) | _BV(2) | _BV(6);
	DDRB |= _BV(7);
	UnselectAllChip(); // unselect all chips


	//Init data structure
	Keys_e keyFromChipIndex0[8] = {	C_1, C_SHARP_1, D_1, D_SHARP_1,
		E_1, F_1, F_SHARP_1,G_1 };
	Keys_e keyFromChipIndex1[8] = {	NUM_KEYS, NUM_KEYS, NUM_KEYS, NUM_KEYS,	
	B_1, A_SHARP_1, A_1,G_SHARP_1 };
	Keys_e keyFromChipIndex2[8] = {	C_2, C_SHARP_2, D_2, D_SHARP_2,
		E_2, F_2, F_SHARP_2,G_2 };
	Keys_e keyFromChipIndex3[8] = {	NUM_KEYS, NUM_KEYS, NUM_KEYS, C_3,
		B_2, A_SHARP_2, A_2,G_SHARP_2 };

	InitChip(keyFromChipIndex0,&SelectChip0);
	InitChip(keyFromChipIndex1,&SelectChip1);
	InitChip(keyFromChipIndex2,&SelectChip2);
	InitChip(keyFromChipIndex3,&SelectChip3);

	s_KR.keyReadIndex = 0x0;
	s_KR.byteReadIndex = 0x0;
	s_KR.octave = 0x00;
	s_KR.readCount = 0;
	s_KR.processCount = 0;

	//inits events ringbuffer
	RBE_INIT(s_KR.events);

	
	// Sets MOSI and SCK as output
	DDRB |= _BV(1) | _BV(2) | _BV(0);
	

	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = _BV(SPE) | _BV(MSTR)| _BV(SPR0);
   
};

void StartKeyReader() {
	//start to read first byte
	UnselectAllChip();
	SelectChip0();
	PORTB |= _BV(0);
	SPDR = s_KR.keys[0].bytes[0];
}


#include "UserInterface.h"

void ProcessSPI() {
	if (! (SPSR & _BV(SPIF) ) ){
		return ;
	}
	
	uint16_t data = SPDR;

#define keyIdx() s_KR.keyReadIndex
#define valueIdx(i) (s_KR.keys[i].readCount & KEY_DATA_MASK )
	//put the data at the right place
	if (s_KR.byteReadIndex == 1) {
		s_KR.keys[keyIdx()].values[valueIdx(keyIdx())] = (data & 0x03) << 8;
	} else if (s_KR.byteReadIndex == 2) {
		s_KR.keys[keyIdx()].values[valueIdx(keyIdx())] |= data & 0xff;
		++s_KR.keys[keyIdx()].readCount;
	}

	//increment the key / byte to pull
	++s_KR.byteReadIndex;
	if (s_KR.byteReadIndex == 3) {
		//we need to increment key
		// key update should be notified
		s_KR.readCount += 1;

		s_KR.byteReadIndex = 0;
		s_KR.keyReadIndex += 1;
		if (keyIdx() >= NUM_KEYS ) {
			//we turn arroudn all keys;
			keyIdx() = 0;
		}
		
		// we select a new chip
		UnselectAllChip();
		(s_KR.keys[keyIdx()].selectChip)();

	}

	//start to pull out a new byte
	SPDR = s_KR.keys[keyIdx()].bytes[s_KR.byteReadIndex];

#undef keyIdx
#undef valueIdx
}

void ProcessKey(Keys_e  k) {
	RBE_TAIL(s_KR.events).Event = MIDI_EVENT(0,MIDI_COMMAND_NOTE_ON);
	RBE_TAIL(s_KR.events).Data1 = MIDI_COMMAND_NOTE_ON | MIDI_CHANNEL(1);
	RBE_TAIL(s_KR.events).Data2 = k; // Pitch	
	RBE_TAIL(s_KR.events).Data3 = s_KR.keys[k].values[0] >> 5; //Velocity
	
	RBE_INCREMENT_TAIL(s_KR.events);
}

void ProcessKeys() {
	while(!RBE_IS_FULL(s_KR.events) && (s_KR.readCount - s_KR.processCount) > 0 ) {		
		ProcessKey(s_KR.processCountIndex);
		++s_KR.processCount;
		++s_KR.processCountIndex;
		if (s_KR.processCountIndex == NUM_KEYS ) {
			s_KR.processCountIndex = 0;
		}
	}
}


void ProcessKeyReader() {
	ProcessSPI();
	ProcessKeys();
}


MIDI_EventPacket_t * NextKeyEvent() {
	if (RBE_IS_EMPTY(s_KR.events) ) {
		return NULL;
	}
	return &(RBE_HEAD(s_KR.events));
}

void ReleaseEvent() {
	if(RBE_IS_EMPTY(s_KR.events) ) {
		return;
	}
	RBE_INCREMENT_HEAD(s_KR.events);
}



void IncrementOctave() {
	if (s_KR.octave == MAX_OCTAVE) {
		return;
	}
	++s_KR.octave;
}

void DecrementOctave() {
	if(s_KR.octave == 0) {
		return;
	}
	--s_KR.octave;
}

void FillCellReport(CellReport_t * res) {
	if (res == NULL ) {
		return;
	}

	res->systime = GetSystime();

	for(uint8_t i = 0; i < NUM_KEYS; ++i ) {
		res->cells[i].pressCount = s_KR.keys[i].pressCount;
		res->cells[i].lastVelocity = s_KR.keys[i].lastVelocity;
		
		res->cells[i].value = s_KR.keys[i].values[(s_KR.keys[i].readCount) & KEY_DATA_MASK];
	}

}

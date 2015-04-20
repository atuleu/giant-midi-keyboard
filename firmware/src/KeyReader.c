#include "KeyReader.h"


#define KEY_DATA_SIZE 4
#define KEY_DATA_MASK (KEY_DATA_SIZE - 1)


typedef void(*SelectorFPtr)();

typedef struct KeyData {
	// read ring buffer
	uint8_t  readCount;
	uint8_t  processCount;
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

	KeyData_t keys[NUM_KEYS];
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
	

	//Init structure
	Keys_e keyFromChipIndex0[8] = {	C_1, C_SHARP_1, D_1, D_SHARP_1,
		E_1, F_1, F_SHARP_1,G_1 };
	Keys_e keyFromChipIndex1[8] = {	NUM_KEYS, NUM_KEYS, NUM_KEYS, NUM_KEYS,
		B_1, A_SHARP_1, A_1,G_SHARP_1 };
	Keys_e keyFromChipIndex2[8] = {	C_2, C_SHARP_1, D_2, D_SHARP_2,
		E_2, F_2, F_SHARP_2,G_2 };
	Keys_e keyFromChipIndex3[8] = {	NUM_KEYS, NUM_KEYS, NUM_KEYS, C_3,
		B_2, A_SHARP_2, A_2,G_SHARP_2 };

	InitChip(keyFromChipIndex0,&SelectChip0);
	InitChip(keyFromChipIndex1,&SelectChip1);
	InitChip(keyFromChipIndex2,&SelectChip2);
	InitChip(keyFromChipIndex3,&SelectChip3);

	s_KR.keyReadIndex = 0x0;
	s_KR.byteReadIndex = 0x0;
	
}

MIDI_EventPacket_t * ReadNextKeyEvent() {
}

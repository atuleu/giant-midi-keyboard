#include "Registers.h"

#include <avr/eeprom.h> 


uint16_t Registers[GMK_USBIF_NUMBER_OF_REGISTERS];


void InitRegisters() {
	for ( uint8_t i = 0 ; i < GMK_USBIF_NUMBER_OF_REGISTERS;  ++i ) {
		uint16_t * address = (uint16_t *) (2 * i + 2);
		Registers[i] = eeprom_read_word(address);

		if ( Registers[i] != 0xffff && Registers[i] != 0x0000) {
			continue;
		}

		switch ( i % GMK_CELL_NUM_PARAMS ) {
		case GMK_CELL_LOW_THRESHOLD:
			Registers[i] = 1;
			break;
		case GMK_CELL_HIGH_THRESHOLD:
			Registers[i] = 1000;
			break;
		};


	}
}
		

void UpdateEEPROM() {
	for ( uint8_t i = 0 ; i < GMK_USBIF_NUMBER_OF_REGISTERS;  ++i ) {
		uint16_t * address = (uint16_t *) (2 * i + 2);
		uint16_t eepromValue =  eeprom_read_word(address);

		if ( Registers[i] == eepromValue ) {
			//no need to write.
			continue;
		}
		
		eeprom_write_word(address,Registers[i]);
	}
}

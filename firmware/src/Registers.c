#include "Registers.h"

#include <avr/eeprom.h> 

typedef RegisterData {
	uint16_t value;
} RegisterData_t;

 RegisterData_t Registers[GMK_USBIF_NUMBER_OF_REGISTERS];


void InitRegisters() {
	for ( uint8_t i = 0 ; i < GMK_USBIF_NUMBER_OF_REGISTERS;  ++i ) {
		uint16_t * address = (uint16_t *) (2 * i + 2);
		Registers[i] = eeprom_read_word(address);
	}
}
		

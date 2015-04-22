#ifndef GMK_KEYREADER_H_
#define GMK_KEYREADER_H_

#include <LUFA/Drivers/USB/USB.h>


void InitKeyReader();

void StartKeyReader();

MIDI_EventPacket_t * ReadNextKeyEvent();


void IncrementOctave();
void DecrementOctave();




#endif //GMK_KEYREADER_H_



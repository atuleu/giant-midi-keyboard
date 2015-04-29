#ifndef GMK_KEYREADER_H_
#define GMK_KEYREADER_H_

#include <LUFA/Drivers/USB/USB.h>

typedef struct CellStatus CellStatus_t;

void InitKeyReader();

void StartKeyReader();

void ProcessKeyReader();

MIDI_EventPacket_t * NextKeyEvent();
void ReleaseEvent();

void IncrementOctave();
void DecrementOctave();

void FillCellStatus(uint8_t key, CellStatus_t * res);



#endif //GMK_KEYREADER_H_



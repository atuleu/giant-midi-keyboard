#ifndef GMK_KEYREADER_H_
#define GMK_KEYREADER_H_

#include <LUFA/Drivers/USB/USB.h>

typedef struct CellReport CellReport_t;

void InitKeyReader();

void StartKeyReader();

void ProcessKeyReader();

MIDI_EventPacket_t * NextKeyEvent();
void ReleaseEvent();

void IncrementOctave();
void DecrementOctave();

void FillCellReport(CellReport_t * res);



#endif //GMK_KEYREADER_H_



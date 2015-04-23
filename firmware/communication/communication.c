#include "communication.h"

#ifndef NULL
#define NULL ( (void*) 0)
#endif

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

GmkUSBIFInstructionMetadata_t IMetaData[GMK_USBIF_INST_NUMBER] = { 
	{ REQ_VENDOR_IN , 2 * GMK_USBIF_NUMBER_OF_REGISTERS , NULL }, // READ_ALL_PARAMS
	{ REQ_VENDOR_OUT , 0 , NULL }, // SET_PARAM
	{ REQ_VENDOR_OUT , 0 , NULL }, // SAVE_IN_EEPROM
	{ REQ_VENDOR_IN , 2 * 25 , NULL } // FETCH_CELL_VALUES
};

#ifdef __cplusplus
}
#endif //__cplusplus

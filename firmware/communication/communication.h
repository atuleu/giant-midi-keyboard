#ifndef GSK_COMMUNICATION_H_
#define GSK_COMMUNICATION_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

typedef enum { 
	GMK_USBIF_ERR_NO_ERROR   = 0,
	GMK_USBIF_ERR_MAX_ERRORS
} GmkUsbIFError_e;


typedef enum {
	GMK_CELL_LOW_THRESHOLD  = 0,
	GMK_CELL_HIGH_THRESHOLD = 1,
	GMK_CELL_NUM_PARAMS     = 2
} GmkUsbIFCellParam_e;

typedef enum {
	GMK_CELL_C_1 = 0,
	GMK_CELL_C_SHARP_1 = GMK_CELL_C_1       + GMK_CELL_NUM_PARAMS,  // 0x02
	GMK_CELL_D_1       = GMK_CELL_C_SHARP_1 + GMK_CELL_NUM_PARAMS,  // 0x04
	GMK_CELL_D_SHARP_1 = GMK_CELL_D_1       + GMK_CELL_NUM_PARAMS,  // 0x06
	GMK_CELL_E_1       = GMK_CELL_D_SHARP_1 + GMK_CELL_NUM_PARAMS,  // 0x08
	GMK_CELL_F_1       = GMK_CELL_E_1       + GMK_CELL_NUM_PARAMS,  // 0x0a
	GMK_CELL_F_SHARP_1 = GMK_CELL_F_1       + GMK_CELL_NUM_PARAMS,  // 0x0c
	GMK_CELL_G_1       = GMK_CELL_F_SHARP_1 + GMK_CELL_NUM_PARAMS,  // 0x0e
	GMK_CELL_G_SHARP_1 = GMK_CELL_G_1       + GMK_CELL_NUM_PARAMS,  // 0x10
	GMK_CELL_A_1       = GMK_CELL_G_SHARP_1 + GMK_CELL_NUM_PARAMS,  // 0x12
	GMK_CELL_A_SHARP_1 = GMK_CELL_A_1       + GMK_CELL_NUM_PARAMS,  // 0x14
	GMK_CELL_B_1       = GMK_CELL_A_SHARP_1 + GMK_CELL_NUM_PARAMS,  // 0x16
	GMK_CELL_C_2       = GMK_CELL_B_1       + GMK_CELL_NUM_PARAMS,  // 0x18
	GMK_CELL_C_SHARP_2 = GMK_CELL_C_2       + GMK_CELL_NUM_PARAMS,  // 0x1a
	GMK_CELL_D_2       = GMK_CELL_C_SHARP_2 + GMK_CELL_NUM_PARAMS,  // 0x1c
	GMK_CELL_D_SHARP_2 = GMK_CELL_D_2       + GMK_CELL_NUM_PARAMS,  // 0x1e
	GMK_CELL_E_2       = GMK_CELL_D_SHARP_2 + GMK_CELL_NUM_PARAMS,  // 0x20
	GMK_CELL_F_2       = GMK_CELL_E_2       + GMK_CELL_NUM_PARAMS,  // 0x22
	GMK_CELL_F_SHARP_2 = GMK_CELL_F_2       + GMK_CELL_NUM_PARAMS,  // 0x24
	GMK_CELL_G_2       = GMK_CELL_F_SHARP_2 + GMK_CELL_NUM_PARAMS,  // 0x26
	GMK_CELL_G_SHARP_2 = GMK_CELL_G_2       + GMK_CELL_NUM_PARAMS,  // 0x28
	GMK_CELL_A_2       = GMK_CELL_G_SHARP_2 + GMK_CELL_NUM_PARAMS,  // 0x2a
	GMK_CELL_A_SHARP_2 = GMK_CELL_A_2       + GMK_CELL_NUM_PARAMS,  // 0x2c
	GMK_CELL_B_2       = GMK_CELL_A_SHARP_2 + GMK_CELL_NUM_PARAMS,  // 0x2e
	GMK_CELL_C_3       = GMK_CELL_B_2       + GMK_CELL_NUM_PARAMS,  // 0x30

	GMK_USBIF_NUMBER_OF_REGISTERS = GMK_CELL_C_3 + GMK_CELL_NUM_PARAMS
} GmkUsbIFRegister_e;



typedef enum {
	GMK_USBIF_INST_READ_ALL_REGISTER = 0,
	GMK_USBIF_INST_SET_REGISTER      = 1,
	GMK_USBIF_INST_SAVE_EEPROM       = 2,
	GMK_USBIF_INST_FETCH_CELL_STATUS = 3,
	GMK_USBIF_INST_NUMBER
} GmkUsbIFInstruction_e;


typedef struct {
	const uint8_t bmRequestType;
	const uint16_t wLength;
	void * userData;
} GmkUSBIFInstructionMetadata_t;


typedef struct CellStatus {
	uint16_t systime;
	uint16_t value;
	uint8_t  pressCount;
	uint8_t  lastVelocity;
} CellStatus_t;
		

extern GmkUSBIFInstructionMetadata_t IMetaData[GMK_USBIF_INST_NUMBER];

#ifdef __cplusplus
} // extern "C"
#endif //__cplusplus

#ifdef REQDIR_DEVICETOHOST
#define REQ_VENDOR_IN ( REQDIR_DEVICETOHOST | REQTYPE_VENDOR | REQREC_DEVICE )
#define REQ_VENDOR_OUT ( REQDIR_HOSTTODEVICE | REQTYPE_VENDOR | REQREC_DEVICE )
#else 
#define REQ_VENDOR_IN ( ( 1 << 7 ) | ( 2 << 5 ) | ( 0 << 0 ) )
#define REQ_VENDOR_OUT ( (  0 << 7 ) | ( 2 << 5 ) | ( 0 << 0 ) )
#endif 

#define IS_REQ_VENDOR(req) ( ( (req) & 0x7f ) == REQ_VENDOR_OUT )

#endif //GSK_COMMUNICATION_H_



#include "USB.h"

#include <communication/communication.h>

#include "Registers.h"
#include "KeyReader.h"

void ReadCallback(uint16_t index, uint16_t value);
void SetRegisterCallback(uint16_t index, uint16_t value);
void SaveInEEPROMCallback(uint16_t index, uint16_t value);
void FetchCellStatusCallback(uint16_t index, uint16_t value);

typedef void(*RequestCallback)(uint16_t,uint16_t);

void InitUSB() {
	USB_Init();

	//set ups the callback here
	IMetaData[GMK_USBIF_INST_READ_REGISTER].userData = &ReadCallback;
	IMetaData[GMK_USBIF_INST_SET_REGISTER].userData  = &SetRegisterCallback;
	IMetaData[GMK_USBIF_INST_SAVE_EEPROM].userData   = &SaveInEEPROMCallback;
	IMetaData[GMK_USBIF_INST_FETCH_CELL_STATUS].userData = &FetchCellStatusCallback;
	
	PrintError(GMK_ERR_NO_USB_CONNECTION);
}

void ProcessUSB() {
	//certainly we need to fetch the device status or events to report a note.

	if (USB_DeviceState != DEVICE_STATE_Configured ) {
		USB_USBTask();
		return;
	}

	Endpoint_SelectEndpoint(MIDI_STREAM_IN_EPADDR);
	
	if ( Endpoint_IsINReady() ) {
		
		MIDI_EventPacket_t * event = NextKeyEvent();
		bool clearIn = false;
		while( event != NULL && Endpoint_IsReadWriteAllowed() ) {
			Endpoint_Write_Stream_LE(event, sizeof(MIDI_EventPacket_t), NULL);
			ReleaseEvent();
			clearIn = true;
		}
		// One could do : write data, and continue until
		// IsReadWriteAllowed does not allow to write stuff, or cannot
		// write event to the endpoint.
			


		/* Send the data in the endpoint to the host */
		if (clearIn) {
			Endpoint_ClearIN();
		}

	}

	
	/* Check if a MIDI command has been received */
	if (Endpoint_IsOUTReceived()) {
		MIDI_EventPacket_t MIDIEvent;
		
		/* Read the MIDI event packet from the endpoint */
		Endpoint_Read_Stream_LE(&MIDIEvent, sizeof(MIDIEvent), NULL);

		/* Check to see if the sent command is a note on message with a non-zero velocity */
		if ((MIDIEvent.Event == MIDI_EVENT(0, MIDI_COMMAND_NOTE_ON)) && 
		    (MIDIEvent.Data3 > 0)) {
		} else {
		}

		/* If the endpoint is now empty, clear the bank */
		if (!(Endpoint_BytesInEndpoint())) {
			/* Clear the endpoint ready for new packet */
			Endpoint_ClearOUT();
		}
	}


	USB_USBTask();
}

void EVENT_USB_Device_Connect() {
	PrintError(GMK_ERR_NO_ERROR);
}

void EVENT_USB_Device_Disconnect() {
	PrintError(GMK_ERR_NO_USB_CONNECTION);
}
	

void EVENT_USB_Device_ConfigurationChanged() {
	bool configSuccess = true;

	configSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_IN_EPADDR,EP_TYPE_BULK,MIDI_STREAM_EPSIZE,1);
	configSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_OUT_EPADDR,EP_TYPE_BULK,MIDI_STREAM_EPSIZE,1);
	if(configSuccess == false) {
		PrintError(GMK_ERR_USB_CONFIGURATION);
	}
	//TODO ? Report
}


void EVENT_USB_Device_ControlRequest() {
	uint8_t req = USB_ControlRequest.bRequest;
	if ( IS_REQ_VENDOR(USB_ControlRequest.bmRequestType) ) {
		RequestCallback cbk = NULL;
		if (USB_ControlRequest.bRequest < GMK_USBIF_INST_NUMBER ) {
			cbk = IMetaData[USB_ControlRequest.bRequest].userData;
		}
		
		if (cbk == NULL) {
			// invalid request, we just send back the packet, and print
			// error.
			PrintError(GMK_ERR_INVALID_HOST_VENDOR_REQUEST);
			Endpoint_ClearOUT();
			Endpoint_ClearStatusStage();
			return;
		}

		cbk(USB_ControlRequest.wIndex,USB_ControlRequest.wValue);

		return;
	}
}


void ReadCallback(uint16_t index,uint16_t value) {
	Endpoint_ClearSETUP();

	if (index < GMK_USBIF_NUMBER_OF_REGISTERS ) {
		Endpoint_Write_Control_Stream_LE(&(Registers[index]),2);
	} else {
		uint16_t invalid = 0xaaaa;
		Endpoint_Write_Control_Stream_LE(&invalid,2);
	}

	Endpoint_ClearOUT();
}

void SetRegisterCallback(uint16_t index, uint16_t value) {
	
	Endpoint_ClearSETUP();
	if (index < GMK_USBIF_NUMBER_OF_REGISTERS ) {
		Registers[index] = value;
	}

	Endpoint_ClearStatusStage();
}


void SaveInEEPROMCallback(uint16_t index, uint16_t value) {
	Endpoint_ClearSETUP();
	
	UpdateEEPROM();

	Endpoint_ClearStatusStage();
}


void FetchCellStatusCallback(uint16_t index, uint16_t value) {
	Endpoint_ClearSETUP();
	
	CellStatus_t status;
	FillCellStatus(index,&status);

	Endpoint_ClearSETUP();
	Endpoint_Write_Control_Stream_LE(&status,sizeof(status));

	Endpoint_ClearOUT();
}

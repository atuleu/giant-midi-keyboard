#include "USB.h"



void InitUSB() {
	USB_Init();
	PrintError(0x01);
	// Certainly other things to do
}


void ProcessUSB(Event_t e) {
	//certainly we need to fetch the device status or events to report a note.

	if (USB_DeviceState != DEVICE_STATE_Configured ) {
		return;
	}

	Endpoint_SelectEndpoint(MIDI_STREAM_IN_EPADDR);
	
	if ( Endpoint_IsINReady()) {
		//TODO :  parse inputs and send note on / note off		
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
	PrintError(0);
	Print(1);
	//TODO : report ?
}

void EVENT_USB_Device_Disconnect() {
	PrintError(1);
}
	

void EVENT_USB_Device_ConfigurationChanged() {
	bool configSuccess = true;

	configSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_IN_EPADDR,EP_TYPE_BULK,MIDI_STREAM_EPSIZE,1);
	configSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_OUT_EPADDR,EP_TYPE_BULK,MIDI_STREAM_EPSIZE,1);
	if(configSuccess == false) {
		PrintError(0x02);
	} else {
		Print(2);
	}
	
	//TODO ? Report
}

#define REQ_VENDOR_OUT ( (  0 << 7 ) | ( 2 << 5 ) | ( 0 << 0 ) )

#define IS_REQ_VENDOR(req) ( ( (req) & 0x7f ) == REQ_VENDOR_OUT )

void EVENT_USB_Device_ControlRequest() {
	uint8_t req = USB_ControlRequest.bRequest;
	if ( IS_REQ_VENDOR(USB_ControlRequest.bmRequestType) ) {
		//TODO: process it
		return;
	}
	// otherwise we just forget it.
}

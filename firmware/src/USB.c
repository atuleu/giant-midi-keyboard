#include "USB.h"





void ProcessUSB(Event_t e) {
	//certainly we need to fetch the device status or events to report a note.

	if (USB_DeviceState != DEVICE_STATE_Configured ) {
		USB_USBTask();
		return;
	}

	Endpoint_SelectEndpoint(MIDI_STREAM_IN_EPADDR);
	
	if ( Endpoint_IsINReady() && e != 0) {

		uint8_t MIDICommand = 0;
		uint8_t MIDIPitch;

		switch(e) {
		case BUTTON_0_PRESSED :
			MIDICommand = MIDI_COMMAND_NOTE_ON;
			MIDIPitch = 0x3c;
			break;
		case BUTTON_1_PRESSED :
			MIDICommand = MIDI_COMMAND_NOTE_ON;
			MIDIPitch = 0x3d;
			break;
		case BUTTON_2_PRESSED :
			MIDICommand = MIDI_COMMAND_NOTE_ON;
			MIDIPitch = 0x3e;
			break;
		case BUTTON_0_RELEASED :
			MIDICommand = MIDI_COMMAND_NOTE_OFF;
			MIDIPitch = 0x3c;
			break;
		case BUTTON_1_RELEASED :
			MIDICommand = MIDI_COMMAND_NOTE_OFF;
			MIDIPitch = 0x3d;
			break;
		case BUTTON_2_RELEASED :
			MIDICommand = MIDI_COMMAND_NOTE_OFF;
			MIDIPitch = 0x3e;
			break;
		}

		MIDI_EventPacket_t MIDIEvent = {
			.Event = MIDI_EVENT(0,MIDICommand),
			.Data1 = MIDICommand | MIDI_CHANNEL(1),
			.Data2 = MIDIPitch,
			.Data3 = 127,
		};
			
		Endpoint_Write_Stream_LE(&MIDIEvent, sizeof(MIDIEvent), NULL);

		/* Send the data in the endpoint to the host */
		Endpoint_ClearIN();

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

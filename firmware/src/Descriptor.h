/*
             LUFA Library
     Copyright (C) Dean Camera, 2014.
  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2014  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.
  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#ifndef GMK_USB_DESCRIPTOR_H_
#define GMK_USB_DESCRIPTOR_H_


//#include "LUFAConfig.h"
#include <LUFA/Drivers/USB/USB.h>

// Address of the endpoint used for device-to-host transfers
#define MIDI_STREAM_IN_EPADDR  (ENDPOINT_DIR_IN  | 1)
// Address of the endpoint used for host-to-device transfers
#define MIDI_STREAM_OUT_EPADDR (ENDPOINT_DIR_OUT | 2)
// Endpoint size of the audio isochronous streaming
#define MIDI_STREAM_EPSIZE 64


typedef struct {
	USB_Descriptor_Configuration_Header_t     Config;

	// MIDI Audio Control Interface
	USB_Descriptor_Interface_t                Audio_ControlInterface;
	USB_Audio_Descriptor_Interface_AC_t       Audio_ControlInterface_SPC;

	// MIDI Audio Streaming Interface
	USB_Descriptor_Interface_t                Audio_StreamInterface;
	USB_MIDI_Descriptor_AudioInterface_AS_t   Audio_StreamInterface_SPC;
	USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Emb;
	USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Ext;
	USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Emb;
	USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Ext;
	USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_In_Jack_Endpoint;
	USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_In_Jack_Endpoint_SPC;
	USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_Out_Jack_Endpoint;
	USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_Out_Jack_Endpoint_SPC;
} USB_Descriptor_Configuration_t;

enum InterfaceDescriptors_t {
	IF_ID_AudioControl = 0, 
	IF_ID_AudioStream  = 1, 
};

enum StringDescriptors_t {
	STR_ID_Language     = 0, 
	STR_ID_Manufacturer = 1, 
	STR_ID_Product      = 2, 
};

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress) 
	ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);



#endif //GMK_USB_DESCRIPTOR_H_

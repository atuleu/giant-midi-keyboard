set(SRC_FILES main.c 
              Systime.c
              UserInterface.c
              Descriptor.c
              USB.c
              KeyReader.c
              ../communication/communication.c
              Registers.c
              )

set(HDR_FILES Systime.h
	          UserInterface.h
	          Descriptor.h
	          USB.h
	          KeyReader.h
              ../communication/communication.h
              Registers.h
	          )

set(LUFA_ROOT ${PROJECT_SOURCE_DIR}/LUFA)
set(LUFA_CORE_ROOT ${LUFA_ROOT}/LUFA/Drivers/USB/Core)


add_definitions("-std=c99" "-DF_USB=16000000L")


set(ARCH AVR8)

add_definitions("-D USB_DEVICE_ONLY"
	"-D DEVICE_STATE_AS_GPIOR=0"
	"-D ORDERED_EP_CONFIG"
	"-D FIXED_CONTROL_ENDPOINT_SIZE=8"
	"-D FIXED_NUM_CONFIGURATIONS=1"
	"-D USE_RAM_DESCRIPTORS"
	"-D USE_STATIC_OPTIONS=\"(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)\""
	"-D NO_INTERNAL_SERIAL"
	"-D NO_DEVICE_SELF_POWER"
	"-D NO_DEVICE_REMOTE_WAKEUP"
	"-D NO_SOF_EVENTS")

set(LUFA_CORE_SRCS ConfigDescriptors.c 
                   DeviceStandardReq.c
                   Events.c
                   USBTask.c
                   ${ARCH}/Device_${ARCH}.c
                   ${ARCH}/Endpoint_${ARCH}.c
                   ${ARCH}/EndpointStream_${ARCH}.c
                   ${ARCH}/USBController_${ARCH}.c
                   ${ARCH}/USBInterrupt_${ARCH}.c)

set(LUFA_CORE_HDRS LUFA/USB/USB.h)

foreach(f ${LUFA_CORE_SRCS})
		list(APPEND LUFA_CORE_SRCS_EXPANDED ${LUFA_CORE_ROOT}/${f})
endforeach(f ${LUFA_CORE_SRCS})

add_avr_library(lufa-core-device
                MCU atmega32u4
                MCU_SPEED 16000000L
                SRCS ${LUFA_CORE_SRCS_EXPANDED})


include_directories(${LUFA_ROOT} ${PROJECT_SOURCE_DIR})

add_avr_executable(giant-MIDI-keyboard 
	MCU atmega32u4
	MCU_SPEED 16000000L
	SRCS ${SRC_FILES}
	HDRS ${HDR_FILES}
	PROGRAMMER arduinoisp
	UPLOADTOOL_OPTIONS -C ${PROJECT_SOURCE_DIR}/avrdude.conf)

avr_target_link_libraries(giant-MIDI-keyboard lufa-core-device)

add_custom_target(upload
	DEPENDS upload_giant-MIDI-keyboard)
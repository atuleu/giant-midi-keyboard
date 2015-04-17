set(SRC_FILES main.c 
              Systime.c
              UserInterface.c
              Descriptor.c
              USB.c
              )

set(HDR_FILES Systime.h
	          UserInterface.h
	          Descriptor.h
	          USB.h
	          )

set(LUFA_ROOT ${PROJECT_SOURCE_DIR}/LUFA)
set(LUFA_CORE_ROOT ${LUFA_ROOT}/LUFA/Drivers/USB/Core)


add_definitions("-std=c99" "-DF_USB=16000000L")


set(ARCH AVR8)

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


include_directories(${LUFA_ROOT})

add_avr_executable(giant-MIDI-keyboard 
	MCU atmega32u4
	MCU_SPEED 16000000L
	SRCS ${SRC_FILES}
	HDRS ${HDR_FILES}
	PROGRAMMER dragon_isp)

avr_target_link_libraries(giant-MIDI-keyboard lufa-core-device)

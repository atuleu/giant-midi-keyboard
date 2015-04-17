set(SRC_FILES main.c 
              Systime.c
              UserInterface.c
              )

set(HDR_FILES Systime.h
	          UserInterface.h)

add_definitions("-std=c99" "-DF_USB=16000000L")

set(ARCH AVR8)

add_avr_executable(giant-MIDI-keyboard 
	MCU atmega32u4
	MCU_SPEED 16000000L
	SRCS ${SRC_FILES}
	HDRS ${HDR_FILES}
	PROGRAMMER dragon_isp)


set(SRC_FILES main.c 
              Systime.c
              UserInterface.c
              )

set(HDR_FILES Systime.h
	          UserInterface.h)

add_definitions("-std=c99" "-DF_USB=16000000")


set(ARCH AVR8)

generate_avr_firmware(giant-MIDI-keyboard 
                      BOARD micro
                      SRCS ${SRC_FILES}
                      HDRS ${HDR_FILES}
                      PORT ${ARDUINO_SERIAL_PORT}
                      SERIAL ${ARDUINO_SERIAL_EXEC} ${ARDUINO_SERIAL_PORT}  -b 9600 -l )


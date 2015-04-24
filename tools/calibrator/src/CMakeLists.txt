set(COMMON_COMMUNICATION_ROOT ${PROJECT_SOURCE_DIR}/../../firmware)

set(SRCS main.cpp
	     ${COMMON_COMMUNICATION_ROOT}/communication/communication.c)
set(HDRS )



include_directories(${COMMON_COMMUNICATION_ROOT} ${DEPS_INCLUDE_DIRS})

add_executable(giant-midi-keyboard-calibrator ${SRCS} ${HDRS})

target_link_libraries(giant-midi-keyboard-calibrator ${DEPS_LIBRARIES})
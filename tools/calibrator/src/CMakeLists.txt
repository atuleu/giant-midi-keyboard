set(COMMON_COMMUNICATION_ROOT ${PROJECT_SOURCE_DIR}/../../firmware)

set(SRCS main.cpp
	     ${COMMON_COMMUNICATION_ROOT}/communication/communication.c
	     MainWindow.cpp
	     )

set(HDRS MainWindow.h
	     )

set(UI_RAW_FILES MainWindow.ui)

set(TO_MOC_FILES MainWindow.h)

if(UI_RAW_FILES)
	qt4_wrap_ui(UI_FILES ${UI_RAW_FILES})
endif(UI_RAW_FILES)

if(TO_MOC_FILES)
	qt4_wrap_cpp(MOC_FILES ${TO_MOC_FILES})
endif(TO_MOC_FILES)

include(${QT_USE_FILE})

include_directories(${COMMON_COMMUNICATION_ROOT} ${DEPS_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(giant-midi-keyboard-calibrator ${SRCS} ${HDRS} ${UI_FILES} ${MOC_FILES})

target_link_libraries(giant-midi-keyboard-calibrator ${DEPS_LIBRARIES} ${QT_LIBRARIES})
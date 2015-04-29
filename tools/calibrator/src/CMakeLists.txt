set(COMMON_COMMUNICATION_ROOT ${PROJECT_SOURCE_DIR}/../../firmware)

set(SRCS main.cpp
	     ${COMMON_COMMUNICATION_ROOT}/communication/communication.c
	     MainWindow.cpp
	     lusb.cpp
	     GMKDevice.cpp
	     Oscilloscope.cpp
	     )

set(HDRS MainWindow.h
         lusb.h
         GMKDevice.h
         common.h
         Oscilloscope.h
	     )

set(UI_RAW_FILES MainWindow.ui Oscilloscope.ui)

set(TO_MOC_FILES MainWindow.h Oscilloscope.h)

if(UI_RAW_FILES)
	qt4_wrap_ui(UI_FILES ${UI_RAW_FILES})
endif(UI_RAW_FILES)

if(TO_MOC_FILES)
	qt4_wrap_cpp(MOC_FILES ${TO_MOC_FILES})
endif(TO_MOC_FILES)


set(TS_BASEFILES calibrator_fr)

set(RCC_RAW_FILES )


# generates the translation ressources automatically
# first we generate all in a string
set(QRC_TS_CONTENT "<!DOCTYPE RCC><RCC version=\"1.0\">\n  <qresource prefix=\"/ts\">\n")
foreach(ts_base ${TS_BASEFILES})
	list(APPEND TS_FILES ${ts_base}.ts)
	set(QRC_TS_CONTENT "${QRC_TS_CONTENT}    <file>${ts_base}.qm</file>\n")
endforeach(ts_base ${TS_BASEFILES})
set(QRC_TS_CONTENT "${QRC_TS_CONTENT}  </qresource>\n</RCC>")

set(QRC_TS_FILE ${CMAKE_CURRENT_BINARY_DIR}/ts.qrc)
configure_file(ts.qrc.in ${QRC_TS_FILE} @ONLY)

list(APPEND RCC_RAW_FILES ${QRC_TS_FILE})

if(TS_FILES)
	if(UPDATE_TRANSLATIONS)
	message(STATUS "coucou: ${TS_FILES}")
		qt4_create_translation(QM_FILES ${SRCS} ${UI_RAW_FILES} ${TS_FILES})
	else(UPDATE_TRANSLATIONS)
		qt4_add_translation(QM_FILES ${TS_FILES})
	endif(UPDATE_TRANSLATIONS)
	add_custom_target (translations DEPENDS ${QM_FILES})
endif(TS_FILES)

if(RCC_RAW_FILES)
	qt4_add_resources(RCC_FILES ${RCC_RAW_FILES})
endif(RCC_RAW_FILES)


include(${QT_USE_FILE})

include_directories(${COMMON_COMMUNICATION_ROOT} 
                    ${DEPS_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR} 
                    ${QWT_INCLUDE_DIRS})

add_executable(giant-midi-keyboard-calibrator ${SRCS} 
	                                          ${HDRS} 
	                                          ${UI_FILES} 
	                                          ${MOC_FILES}
	                                          ${QM_FILES}
	                                          ${RCC_FILES})

target_link_libraries(giant-midi-keyboard-calibrator ${DEPS_LIBRARIES} ${QT_LIBRARIES} ${QWT_LIBRARIES})
##########################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
##########################################################################

##########################################################################
# The toolchain requires some variables set.
#
# AVR_MCU (default: atmega8)
#     the type of AVR the application is built for
# AVR_L_FUSE (NO DEFAULT)
#     the LOW fuse value for the MCU used
# AVR_H_FUSE (NO DEFAULT)
#     the HIGH fuse value for the MCU used
# AVR_UPLOADTOOL (default: avrdude)
#     the application used to upload to the MCU
#     NOTE: The toolchain is currently quite specific about
#           the commands used, so it needs tweaking.
# AVR_UPLOADTOOL_PORT (default: usb)
#     the port used for the upload tool, e.g. usb
# AVR_PROGRAMMER (default: avrispmkII)
#     the programmer hardware used, e.g. avrispmkII
##########################################################################

##########################################################################
# options
##########################################################################

SET(CMAKE_SYSTEM_NAME Avr)
SET(CMAKE_SYSTEM_PROCESSOR avr)
SET(CMAKE_CROSSCOMPILING 1)


if(EXISTS  ${CMAKE_CURRENT_LIST_DIR}/Platform/Avr.cmake)
	set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
endif(EXISTS  ${CMAKE_CURRENT_LIST_DIR}/Platform/Avr.cmake)


##########################################################################
# executables in use
##########################################################################
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE_TOOL avr-size)
find_program(AVR_OBJDUMP avr-objdump)

set(REQUIRED_TOOLS AVR_CC AVR_CXX AVR_OBJCOPY AVR_SIZE_TOOL AVR_OBJDUMP)
foreach(t ${REQUIRED_TOOLS})
	if(NOT ${f})
		message(FATAL_ERROR "Could not find required tool: ${t}")
	endif(NOT ${f})
endforeach(t ${REQUIRED_TOOLS})

##########################################################################
# toolchain starts with defining mandatory variables
##########################################################################
set(CMAKE_SYSTEM_NAME Avr)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

##########################################################################
# some necessary tools and variables for AVR builds, which may not
# defined yet
# - AVR_UPLOADTOOL
# - AVR_UPLOADTOOL_PORT
# - AVR_PROGRAMMER
# - AVR_MCU
# - AVR_SIZE_ARGS
##########################################################################

if(NOT AVR_DEFAULT_UPLOADTOOL)
	find_program(AVR_DEFAULT_UPLOADTOOL avrdude)
	if(NOT AVR_DEFAULT_UPLOADTOOL)
		message(FATAL_ERROR "Could not find a default upload tool avrdude")
	endif(NOT AVR_DEFAULT_UPLOADTOOL)
endif(NOT AVR_DEFAULT_UPLOADTOOL)
set(AVR_DEFAULT_UPLOADTOOL_PORT usb
    CACHE STRING "Set default upload tool port: usb")
set(AVR_DEFAULT_PROGRAMMER avrispmkII
	CACHE STRING "Set default programmer hardware model: avrspimkII")


##########################################################################
# check build types:
# - Debug
# - Release
# - RelWithDebInfo
#
# Release is chosen, because of some optimized functions in the
# AVR toolchain, e.g. _delay_ms().
##########################################################################
if(NOT ((CMAKE_BUILD_TYPE MATCHES Release) OR
			(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo) OR
			(CMAKE_BUILD_TYPE MATCHES Debug) OR
			(CMAKE_BUILD_TYPE MATCHES MinSizeRel)))
	set(CMAKE_BUILD_TYPE Release
		CACHE STRING "Choose cmake build type: Debug Release RelWithDebInfo MinSizeRel"
		FORCE)
endif(NOT ((CMAKE_BUILD_TYPE MATCHES Release) OR
		(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo) OR
		(CMAKE_BUILD_TYPE MATCHES Debug) OR
		(CMAKE_BUILD_TYPE MATCHES MinSizeRel)))

##########################################################################

if(DEFINED ENV{AVR_FIND_ROOT_PATH})
	set(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
else(DEFINED ENV{AVR_FIND_ROOT_PATH})
	if(EXISTS "/opt/local/avr")
		set(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
	elseif(EXISTS "/usr/avr")
		set(CMAKE_FIND_ROOT_PATH "/usr/avr")
	elseif(EXISTS "/usr/lib/avr")
		set(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
	else(EXISTS "/opt/local/avr")
		message(FATAL_ERROR "Please set AVR_FIND_ROOT_PATH in your environment.")
	endif(EXISTS "/opt/local/avr")
endif(DEFINED ENV{AVR_FIND_ROOT_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# not added automatically, since CMAKE_SYSTEM_NAME is "generic"
#set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
#set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

if(CMAKE_BUILD_TYPE MATCHES Release)
	set(CMAKE_C_FLAGS_RELEASE "-Os")
	set(CMAKE_CXX_FLAGS_RELEASE "-Os")
endif(CMAKE_BUILD_TYPE MATCHES Release)

if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(CMAKE_C_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -save-temps -g -gdwarf-3 -gstrict-dwarf")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

include(CMakeParseArguments)

function(add_avr_definitions MCU_SPEED)
	add_definitions("-DF_CPU=${MCU_SPEED}"
	                "-fpack-struct"
	                "-fshort-enums"
	                "-mcall-prologues"
	                "-ffunction-sections"
	                "-fdata-sections")
endfunction(add_avr_definitions MCU_SPEED)

##########################################################################
# add_avr_executable
# - IN_VAR: EXECUTABLE_NAME
#
# Creates targets and dependencies for AVR toolchain, building an
# executable. Calls add_executable with ELF file as target name, so
# any link dependencies need to be using that target, e.g. for
# target_link_libraries(<EXECUTABLE_NAME>-${AVR_MCU}.elf ...).
##########################################################################
function(add_avr_executable EXECUTABLE_NAME)
	set(options WITHOUT_MCU HAS_EXTENDED_FUSE)
	set(oneValueArgs MCU MCU_SPEED UPLOADTOOL PORT PROGRAMMER H_FUSE L_FUSE E_FUSE)
	set(multiValueArgs SRCS HDRS CFLAGS UPLOADTOOL_OPTIONS)
	cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	if(NOT ARGS_MCU)
		message(FATAL_ERROR "target MCU is required")
	endif(NOT ARGS_MCU)

	if(NOT ARGS_MCU_SPEED)
		message(FATAL_ERROR "target MCU_SPEED is required")
	endif(NOT ARGS_MCU_SPEED)


	if(NOT ARGS_UPLOADTOOL)
		set(ARGS_UPLOADTOOL ${AVR_DEFAULT_UPLOADTOOL})
	endif(NOT ARGS_UPLOADTOOL)


	if(NOT ARGS_UPLOADTOOL_PORT)
		set(ARGS_UPLOADTOOL_PORT ${AVR_DEFAULT_UPLOADTOOL_PORT})
	endif(NOT ARGS_UPLOADTOOL_PORT)

	if(NOT ARGS_PORT)
		set(ARGS_PORT ${AVR_DEFAULT_PORT})
	endif(NOT ARGS_PORT)

	if(NOT ARGS_PROGRAMMER)
		set(ARGS_PROGRAMMER ${AVR_DEFAULT_PROGRAMMER})
	endif(NOT ARGS_PROGRAMMER)

	if(NOT ARGS_SRCS)
		message(FATAL_ERROR "You must provide at least one source file")
	endif(NOT ARGS_SRCS)

	if(ARGS_WITHOUT_MCU)
		set(MCU_TYPE_FOR_FILENAME "")
	else(ARGS_WITHOUT_MCU)
		set(MCU_TYPE_FOR_FILENAME "-${ARGS_MCU}")
	endif(ARGS_WITHOUT_MCU)

	#default avr-size args
	if(NOT AVR_SIZE_ARGS)
		if(APPLE)
			set(AVR_SIZE_ARGS -B)
		else(APPLE)
			set(AVR_SIZE_ARGS -C;--mcu=${ARGS_MCU})
		endif(APPLE)
	endif(NOT AVR_SIZE_ARGS)


	add_avr_definitions(${ARGS_MCU_SPEED})
	# set file names
	set(elf_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.elf)
	set(hex_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.hex)
	set(map_file ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}.map)
	set(eeprom_image ${EXECUTABLE_NAME}${MCU_TYPE_FOR_FILENAME}-eeprom.hex)

	# elf file
	add_executable(${elf_file} EXCLUDE_FROM_ALL ${ARGS_SRCS} ${ARGS_HDRS})
	
	set_target_properties(${elf_file}
		                  PROPERTIES COMPILE_FLAGS "-mmcu=${ARGS_MCU}" ${ARGS_CFLAGS}
		                             LINK_FLAGS "-mmcu=${ARGS_MCU} -Wl,--gc-sections -mrelax -Wl,-Map,${map_file}")

	
	add_custom_command(OUTPUT ${hex_file}
	                   COMMAND ${AVR_OBJCOPY} -j .text -j .data -O ihex ${elf_file} ${hex_file}
	                   COMMAND ${AVR_SIZE_TOOL} ${AVR_SIZE_ARGS} ${elf_file}
	                   DEPENDS ${elf_file})

	add_custom_command(OUTPUT ${eeprom_image}
	                   COMMAND ${AVR_OBJCOPY} -j .eeprom --set-section-flags=.eeprom=alloc,load
	                   	--change-section-lma .eeprom=0 --no-change-warnings
	                   	-O ihex ${elf_file} ${eeprom_image}
	                   DEPENDS ${elf_file})

	add_custom_target(${EXECUTABLE_NAME}
	                  ALL
	                  DEPENDS ${hex_file} 
	                          ${eeprom_image})

	set_target_properties(${EXECUTABLE_NAME}
	                      PROPERTIES OUTPUT_NAME "${elf_file}")

	# clean
	get_directory_property(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
	set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${map_file}")

	# upload - with avrdude
	add_custom_target(upload_${EXECUTABLE_NAME}
	                  ${ARGS_UPLOADTOOL} -p ${ARGS_MCU} -c ${ARGS_PROGRAMMER} ${ARGS_UPLOADTOOL_OPTIONS}
	                  	-U flash:w:${hex_file}
	                  	-P ${ARGS_UPLOADTOOL_PORT}
	                DEPENDS ${hex_file}
	                COMMENT "Uploading ${hex_file} to ${ARGS_MCU} using ${ARGS_PROGRAMMER}")

	# upload eeprom only - with avrdude
	# see also bug http://savannah.nongnu.org/bugs/?40142
	add_custom_target(upload_eeprom
	                  ${ARGS_UPLOADTOOL} -p ${ARGS_MCU} -c ${ARGS_PROGRAMMER} ${ARGS_UPLOADTOOL_OPTIONS}
	                  	-U eeprom:w:${eeprom_image}
	                  	-P ${ARGS_UPLOADTOOL_PORT}
	                  DEPENDS ${eeprom_image}
	                  COMMENT "Uploading ${eeprom_image} to ${ARGS_MCU} using ${ARGS_PROGRAMMER}")

	# get status
	add_custom_target(get_status
	                  ${ARGS_UPLOADTOOL} -p ${ARGS_MCU} -c ${ARGS_PROGRAMMER} -P ${ARGS_UPLOADTOOL_PORT} -n -v
	                  COMMENT "Get status from ${ARGS_MCU}")

	if(ARGS_HAS_EXTENDED_FUSE)
		set(FUSE_R_ARGS "-U efuse:r:-:b -U hfuse:r:-:b -U lfuse:r:-:b")
	else(ARGS_HAS_EXTENDED_FUSE)
		set(FUSE_R_ARGS "-U hfuse:r:-:b -U lfuse:r:-:b")
	endif(ARGS_HAS_EXTENDED_FUSE)

	# get fuses
	add_custom_target(get_fuses
	                  ${ARGS_UPLOADTOOL} -p ${ARGS_MCU} -c ${ARGS_PROGRAMMER} -P ${ARGS_UPLOADTOOL_PORT} -n
	                  ${FUSE_R_ARGS}
	                  COMMENT "Get fuses from ${ARGS_MCU}")


	if(ARGS_L_FUSE OR ARGS_H_FUSE OR ARGS_E_FUSE)
		if(ARGS_HAS_EXTENDED_FUSE)
			if(ARGS_L_FUSE AND ARGS_H_FUSE AND ARGS_E_FUSE)
				set(FUSE_W_ARGS "-U efuse:w:${ARGS_E_FUSE}:m -U hfuse:w:${ARGS_H_FUSE}:m -U lfuse:w:${ARGS_L_FUSE}:m")
			else(ARGS_L_FUSE AND ARGS_H_FUSE AND ARGS_E_FUSE)
				message(FATAL_ERROR "Need to set all fuse")
			endif(ARGS_L_FUSE AND ARGS_H_FUSE AND ARGS_E_FUSE)
		else(ARGS_HAS_EXTENDED_FUSE)
			if(ARGS_L_FUSE AND ARGS_H_FUSE)
				set(FUSE_W_ARGS "-U hfuse:w:${ARGS_H_FUSE}:m -U lfuse:w:${ARGS_L_FUSE}:m")
			else(ARGS_L_FUSE AND ARGS_H_FUSE)
				message(FATAL_ERROR "Need to set all fuse")
			endif(ARGS_L_FUSE AND ARGS_H_FUSE)
		endif(ARGS_HAS_EXTENDED_FUSE)
	endif(ARGS_L_FUSE OR ARGS_H_FUSE OR ARGS_E_FUSE)

	if(FUSE_W_ARGS)
		# set fuses
		add_custom_target(set_fuses
			${ARGS_UPLOADTOOL} -p ${ARGS_MCU} -c ${ARGS_PROGRAMMER} -P ${ARGS_UPLOADTOOL_PORT}
			${FUSE_W_ARGS}
			COMMENT "Setup: High Fuse: ${AVR_H_FUSE} Low Fuse: ${AVR_L_FUSE}")
	endif(FUSE_W_ARGS)
	# get oscillator calibration
	add_custom_target(get_calibration
		${ARGS_UPLOADTOOL} -p ${ARGS_MCU} -c ${ARGS_PROGRAMMER} -P ${ARGS_UPLOADTOOL_PORT}
		-U calibration:r:${ARGS_MCU}_calib.tmp:r
		COMMENT "Write calibration status of internal oscillator to ${ARGS_MCU}_calib.tmp.")

	# set oscillator calibration
	add_custom_target(set_calibration
		${ARGS_UPLOADTOOL} -p ${ARGS_MCU} -c ${ARGS_PROGRAMMER} -P ${ARGS_UPLOADTOOL_PORT}
		-U calibration:w:${ARGS_MCU}_calib.hex
		COMMENT "Program calibration status of internal oscillator from ${ARGS_MCU}_calib.hex.")

	# disassemble
	add_custom_target(disassemble_${EXECUTABLE_NAME}
		${AVR_OBJDUMP} -h -S ${elf_file} > ${EXECUTABLE_NAME}.lst
		DEPENDS ${elf_file})

endfunction(add_avr_executable)

##########################################################################
# add_avr_library
# - IN_VAR: LIBRARY_NAME
#
# Calls add_library with an optionally concatenated name
# <LIBRARY_NAME>${MCU_TYPE_FOR_FILENAME}.
# This needs to be used for linking against the library, e.g. calling
# target_link_libraries(...).
##########################################################################
function(add_avr_library LIBRARY_NAME)
	set(options WITHOUT_MCU)
	set(oneValueArgs MCU MCU_SPEED)
	set(multiValueArgs SRCS HDRS CFLAGS)
	cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	if(NOT ARGS_MCU)
		message(FATAL_ERROR "target MCU is required")
	endif(NOT ARGS_MCU)

	if(NOT ARGS_MCU_SPEED)
		message(FATAL_ERROR "target MCU_SPEED is required")
	endif(NOT ARGS_MCU_SPEED)

	if(NOT ARGS_SRCS)
		message(FATAL_ERROR "You must provide at least one source file")
	endif(NOT ARGS_SRCS)

	set(lib_file ${LIBRARY_NAME}-${ARGS_MCU})

	add_library(${lib_file} STATIC ${ARGS_SRCS} ${ARGS_HDRS})

	add_avr_definitions(${ARGS_MCU_SPEED})

	set_target_properties(${lib_file}
	                      PROPERTIES COMPILE_FLAGS "-mmcu=${ARGS_MCU}" ${ARGS_CFLAGS}
	                      OUTPUT_NAME "${lib_file}")

	if(NOT TARGET ${LIBRARY_NAME})
		add_custom_target(${LIBRARY_NAME}
			ALL
			DEPENDS ${lib_file})

		set_target_properties(${LIBRARY_NAME}
			PROPERTIES
			OUTPUT_NAME "${lib_file}")
	endif(NOT TARGET ${LIBRARY_NAME})

endfunction(add_avr_library)

##########################################################################
# avr_target_link_libraries
# - IN_VAR: EXECUTABLE_TARGET
# - ARGN  : targets and files to link to
#
# Calls target_link_libraries with AVR target names (concatenation,
# extensions and so on.
##########################################################################
function(avr_target_link_libraries EXECUTABLE_TARGET)
	if(NOT ARGN)
		message(FATAL_ERROR "Nothing to link to ${EXECUTABLE_TARGET}.")
	endif(NOT ARGN)

	get_target_property(TARGET_LIST ${EXECUTABLE_TARGET} OUTPUT_NAME)

	foreach(TGT ${ARGN})
		if(TARGET ${TGT})
			get_target_property(ARG_NAME ${TGT} OUTPUT_NAME)
			list(APPEND TARGET_LIST ${ARG_NAME})
		else(TARGET ${TGT})
			list(APPEND NON_TARGET_LIST ${TGT})
		endif(TARGET ${TGT})
	endforeach(TGT ${ARGN})

	target_link_libraries(${TARGET_LIST} ${NON_TARGET_LIST})
endfunction(avr_target_link_libraries EXECUTABLE_TARGET)

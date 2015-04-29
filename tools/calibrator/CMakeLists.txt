project(GiantMIDIKeyboardCalibrator C CXX)

cmake_minimum_required(VERSION 2.8)


find_package(PkgConfig REQUIRED)

find_package(Qt REQUIRED COMPONENTS Core Gui)

find_library(QWT_LIBRARIES qwt )
find_path(QWT_INCLUDE_DIRS qwt_plot.h PATH_SUFFIXES qwt)

if(NOT QWT_LIBRARIES OR NOT QWT_INCLUDE_DIRS)
	message(FATAL_ERROR "Could not found Qwt")
else(NOT QWT_LIBRARIES OR NOT QWT_INCLUDE_DIRS)
	message(STATUS "Found Qwt: ${QWT_INCLUDE_DIRS}")
endif(NOT QWT_LIBRARIES OR NOT QWT_INCLUDE_DIRS)

pkg_check_modules(DEPS libusb-1.0 libglog REQUIRED)

add_definitions("--std=c++11")

option (UPDATE_TRANSLATIONS "Update source translation translations/*.ts")

# prevent the generated files from being deleted during make clean
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM true)


add_subdirectory(src)

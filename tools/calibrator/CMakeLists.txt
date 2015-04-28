project(GiantMIDIKeyboardCalibrator C CXX)

cmake_minimum_required(VERSION 2.8)


find_package(PkgConfig REQUIRED)

find_package(Qt REQUIRED COMPONENTS Core Gui)

find_library(QWT_LIBRARIES qwt )

if(NOT QWT_LIBRARIES)
	message(FATAL_ERROR "Could not found Qwt")
endif(NOT QWT_LIBRARIES)

pkg_check_modules(DEPS libusb-1.0 libglog REQUIRED)

add_definitions("--std=c++11")


add_subdirectory(src)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/avr-toolchain.cmake)

project(GiantMIDIKeyboardFw C CXX)

cmake_minimum_required(VERSION 2.8)

add_subdirectory(src)
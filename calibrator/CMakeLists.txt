project(GiantMIDIKeyboard C CXX)

cmake_minimum_required(VERSION 2.8)


find_package(PkgConfig REQUIRED)

pkg_check_modules(DEPS libusb-1.0 libglog REQUIRED)

add_definitions("--std=c++11")

add_subdirectory(src)

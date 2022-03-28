cmake_minimum_required(VERSION 3.21)
project(morse)

set(CMAKE_CXX_STANDARD 14)

add_executable(morse main.cpp morse/morse.cpp morse/morse.hpp oscillator/SineOscillator.cpp oscillator/SineOscillator.h)

cmake_minimum_required(VERSION 3.5)
project(Compilador)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Token.cpp Token.h Tag.cpp Tag.h Lexico.cpp Lexico.h)
add_executable(Compilador ${SOURCE_FILES})
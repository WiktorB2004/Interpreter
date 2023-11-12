# Minimum required version of CMake
cmake_minimum_required(VERSION 3.27)
# Project name
project(WLang_Interpreter)
set(CMAKE_C_COMPILER gcc)
# Add the executable
add_executable(interpreter main.c)
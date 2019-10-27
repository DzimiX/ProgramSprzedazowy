cmake_minimum_required(VERSION 3.15)
project(ProgramSprzedazowy)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp lib/sqlite3.c)

add_executable(ProgramSprzedazowy ${SOURCE_FILES})
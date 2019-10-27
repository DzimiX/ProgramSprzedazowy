cmake_minimum_required(VERSION 3.15)
project(ProgramSprzedazowy)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp lib/sqlite3.c)


#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBS OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(ProgramSprzedazowy ${SOURCE_FILES})
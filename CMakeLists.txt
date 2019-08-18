cmake_minimum_required(VERSION 3.13)
project(ezdnd)

set(CMAKE_CXX_STANDARD 17)

set(LIB_DIR lib)
include_directories(${LIB_DIR}/Catch)

set(SRC_DIR src)
include_directories(src)

set(SRC_FILES main.cpp ${SRC_DIR}/Character/character.hpp ${SRC_DIR}/Character/weapons.hpp ${SRC_DIR}/Core/dice.hpp)
add_executable(ezdnd ${SRC_FILES})

set(TST_DIR test)
set(TST_FILES ${TST_DIR}/coreTest.cpp)
add_executable(ezdnd_test ${TST_FILES})
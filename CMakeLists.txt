cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(ezdnd CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_DIR lib)
include_directories(${LIB_DIR}/Catch)

set(SRC_DIR src)
include_directories(${SRC_DIR})

find_package(Poco 1.8.0 REQUIRED COMPONENTS Foundation Net)

set(SRC_FILES main.cpp ${SRC_DIR}/Character/character.hpp ${SRC_DIR}/Character/weapons.hpp ${SRC_DIR}/Core/dice.hpp ${SRC_DIR}/Character/armor.hpp ${SRC_DIR}/Core/board.hpp ${SRC_DIR}/Core/network.hpp)
add_executable(ezdnd ${SRC_FILES})
target_link_libraries(ezdnd PUBLIC Poco::Foundation Poco::Net stdc++fs)

set(TST_DIR test)
set(TST_FILES ${TST_DIR}/coreTest.cpp)
add_executable(ezdnd_test ${TST_FILES})
cmake_minimum_required(VERSION 3.13)
project(ezdnd)

set(CMAKE_CXX_STANDARD 17)

add_executable(ezdnd main.cpp Character/character.hpp Core/dice.hpp)
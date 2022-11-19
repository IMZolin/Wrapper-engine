cmake_minimum_required(VERSION 3.23)
project(Wrapper_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wrapper_engine main.cpp Wrapper.h Engine.h)

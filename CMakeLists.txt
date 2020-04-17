cmake_minimum_required(VERSION 3.10)
project(polynomial_tranhd98)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(polynomial_tranhd98
    polynomial.cpp
    polynomial.h
    unit-test.cpp)

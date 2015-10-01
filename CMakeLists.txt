cmake_minimum_required(VERSION 3.3)
project(Parallel_LDAP_Data_Processing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Parallel_LDAP_Data_Processing ${SOURCE_FILES})
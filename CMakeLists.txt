cmake_minimum_required(VERSION 3.15)
project(sCrapper C)

set(CMAKE_C_STANDARD 99)

add_executable(sCrapper main.c)

include_directories(include/curl)

find_library(CURL curl lib)

target_link_libraries(sCrapper LINK_PUBLIC ${CURL})

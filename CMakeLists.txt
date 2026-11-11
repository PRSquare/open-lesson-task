cmake_minimum_required(VERSION 3.23)
project(OpenLesson LANGUAGES CXX)

set(STD "23" CACHE STRING "C++ Standard (14, 17, 20, 23)")
set_property(CACHE STD PROPERTY STRINGS 14 17 20 23)

if(NOT STD MATCHES "^(14|17|20|23)$")
    message(FATAL_ERROR "STD must be 14, 17, 20 or 23, got '${STD}'")
endif()

add_executable(build main.cpp)

set_target_properties(build PROPERTIES
    CXX_STANDARD ${STD}
    CXX_STANDARD_REQUIRED ON
)

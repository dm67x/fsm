cmake_minimum_required(VERSION 3.12)

project(fsm 
    LANGUAGES CXX
    VERSION "0.1"
    DESCRIPTION "Finite state machine"
    HOMEPAGE_URL "")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fsm "src/main.cpp")

target_compile_options(fsm PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /Wall>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>
)
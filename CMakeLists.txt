#
# Created by jul3x on 09.07.20.
#

cmake_minimum_required(VERSION 3.6)
project(Fractalizer)

set(CMAKE_CXX_STANDARD 17)

# Change this if you're working on Windows to your SFML and TGUI path.
set(SFML_ROOT "C:/SFML-2.5.1")
set(TGUI_ROOT "C:/TGUI-0.8")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio)
find_package(TGUI 0.8 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${SFML_INCLUDE_DIR} ${TGUI_INCLUDE_DIR})

# Exec
set(EXECUTABLE_NAME "Fractalizer")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build")

file(GLOB_RECURSE SRC "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${SRC})

target_link_libraries(${EXECUTABLE_NAME} pthread
        ${SFML_GRAPHICS_LIBRARY_RELEASE}
        ${SFML_WINDOW_LIBRARY_RELEASE}
        ${SFML_SYSTEM_LIBRARY_RELEASE}
        ${SFML_AUDIO_LIBRARY_RELEASE})


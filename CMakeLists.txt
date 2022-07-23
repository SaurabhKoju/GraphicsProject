cmake_minimum_required (VERSION 3.5)
set(PROJECT_NAME RUBIKS)
project(RUBIKS)

set (CMAKE_BUID_TYPE Debug)

set (source_dir "${PROJECT_SOURCE_DIR}/GraphicsProject/")
file (GLOB source_files "${source_dir}/*.cpp")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system")
add_executable(${PROJECT_NAME} ${source_files})




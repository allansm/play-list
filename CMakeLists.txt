cmake_minimum_required (VERSION 2.8.11)

project (play-list)

find_package(SDL2 REQUIRED)

if(SDL2_FOUND)
	message("sdl2 found")
endif()

include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(music OBJECT src/music.cpp)

add_executable(test test.cpp)

target_link_libraries(music ${SDL2_LIBRARIES} SDL2_mixer)
target_link_libraries(test music path)

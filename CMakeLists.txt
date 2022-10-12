cmake_minimum_required (VERSION 2.8.11)

project (play-list)

find_package(SDL2 REQUIRED)

find_library(SDL2_MIXER
	NAMES SDL2_mixer
	REQUIRED
)

if(SDL2_FOUND)
	message("-- SDL2 FOUND")
endif()

if(SDL2_MIXER)
	message("-- SDL2_MIXER FOUND")
endif()

include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(music OBJECT src/music.cpp)
add_library(playlist OBJECT src/playlist.cpp)

add_executable(play-list src/play-list.cpp)

target_link_libraries(music ${SDL2_LIBRARIES} ${SDL2_MIXER})
target_link_libraries(play-list music playlist path)

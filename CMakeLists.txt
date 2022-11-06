cmake_minimum_required (VERSION 2.8.11)

project (play-list)

find_package(SDL2)
find_library(SDL2_MIXER NAMES SDL2_mixer)

if((NOT SDL2_FOUND) OR (NOT SDL2_MIXER))
	execute_process(COMMAND git submodule update --init --recursive)
endif()

if(NOT SDL2_FOUND)
	add_subdirectory(SDL)
else()
	message("-- SDL2 FOUND")
endif()

if(NOT SDL2_MIXER)
	add_subdirectory(SDL_mixer)
else()
	message("-- SDL2_MIXER FOUND")
endif()

include_directories(include)
include_directories(SDL/include)
include_directories(SDL_mixer/include)

add_library(music OBJECT src/music.cpp)
add_library(playlist OBJECT src/playlist.cpp)
add_library(norepeat OBJECT src/norepeat.cpp)

add_executable(play-list src/play-list.cpp)

target_link_libraries(music SDL2::SDL2 SDL2_mixer)
target_link_libraries(play-list music playlist path norepeat)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/play-list
	PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ WORLD_EXECUTE WORLD_WRITE WORLD_READ
       	DESTINATION bin)


cmake_minimum_required (VERSION 2.8.11)

project (play-list)

add_subdirectory(SDL)
add_subdirectory(SDL_mixer)

include_directories(include)
include_directories(SDL/include)
include_directories(SDL_mixer/include)

add_library(music OBJECT src/music.cpp)
add_library(playlist OBJECT src/playlist.cpp)

add_executable(play-list src/play-list.cpp)

target_link_libraries(music SDL2::SDL2 SDL2_mixer)
target_link_libraries(play-list music playlist path)

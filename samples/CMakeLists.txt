cmake_minimum_required(VERSION 3.5)

project(find_steam_game C)

INCLUDE_DIRECTORIES(..)

################################
# Add definitions

if(MSVC)
	add_definitions(-W4 -WX -wd"4996")
else()
	add_definitions(-fsigned-char -Wall -W -Wshadow -Wpointer-arith -Wcast-qual -Winline -Werror)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wstrict-prototypes")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

################################
# Add targets
add_executable(simple simple.c)

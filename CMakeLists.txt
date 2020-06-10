cmake_minimum_required(VERSION 3.1)

project(foxminesweeper)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Compiler Options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

include_directories( /usr/include/fox-1.6 )

add_executable(foxminesweeper
	MainWindow.h
	MainWindow.cpp
	main.cpp
	icons.h
	Board.cpp
	Board.h
	Tile.cpp
	Tile.h
)
target_link_libraries(foxminesweeper FOX-1.6)

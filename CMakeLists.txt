cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Minesweeper")

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
##set(SFML_DIR "C:/Users/jacob/OneDrive/School & Education/UF Online/COP3503 - Programming Fundamentals 2/Projects/Project - 03/SFML-2.5.1/lib/cmake/SFML")
set(SFML_DIR "C:/Users/jacob/OneDrive/School & Education/UF Online/COP3503 - Programming Fundamentals 2/Projects/Project - 03/Source/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(Minesweeper main.cpp Config.cpp Config.h Tile.cpp Tile.h TextureManager.cpp TextureManager.h Random.cpp Random.h Board.cpp Board.h)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)
cmake_minimum_required(VERSION 3.20)

project(bombergwen LANGUAGES CXX)

# Forcer clang

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(../thirdparty)
include_directories(../include)
include_directories(../include/utility)
include_directories(../include/display)
include_directories(../include/assets)
include_directories(../include/io)
include_directories(../include/game)

add_executable(${PROJECT_NAME} 
    ../src/utility/bomber_logger.cpp
    ../src/io/bomber_graphics.cpp
    ../src/io/bomber_graphics_gameshell.cpp
    ../src/io/bomber_input.cpp
    ../src/display/sprites.cpp
    ../src/display/levels.cpp
    ../src/assets/map_parser.cpp
    ../src/assets/ase_parser.cpp
    ../src/assets/game_assets.cpp
    ../src/game/game_entity.cpp
    ../src/game/game_engine.cpp
    ../src/game/world.cpp
    ../src/game/hero.cpp
    ../src/gameshell.cpp
)

target_include_directories(bombergwen PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(bombergwen PRIVATE ${SDL2_LIBRARIES} SDL2_image)

set(CMAKE_C_FLAGS "--target=arm-linux-gnueabihf")
set(CMAKE_CXX_FLAGS "--target=arm-linux-gnueabihf")

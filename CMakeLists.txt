cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

# set(PROJECT_NAME)
project(Stellar_Calculator VERSION 1.0)

set(SOURCES
src/main.cpp
src/mainWindow.h
src/mainWindow.cpp
src/camera.h
src/camera.cpp
src/IOHandler.h
src/IOHandler.cpp
src/gameObject.h
)

add_executable(Stellar_Calculator ${SOURCES})
find_package(SDL2 REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
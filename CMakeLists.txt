cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

# set(PROJECT_NAME)
project(Stellar_Calculator VERSION 1.0)

set(SOURCES
src/main.cpp
src/genericUIElements/mainWindow.h
src/genericUIElements/mainWindow.cpp
src/genericUIElements/pane.h
src/genericUIElements/pane.cpp
src/genericUIElements/button.h
src/genericUIElements/button.cpp
src/genericUIElements/container.h
src/genericUIElements/container.cpp
src/IOHandler.h
src/IOHandler.cpp
)

add_executable(Stellar_Calculator ${SOURCES})
find_package(SDL2 REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
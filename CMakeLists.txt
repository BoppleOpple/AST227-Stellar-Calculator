cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH /opt/homebrew)

set(PROJECT_NAME Stellar_Calculator)
project(${PROJECT_NAME} VERSION 1.0)

set(SOURCES
src/main.cpp
src/UIElements/mainWindow.h
src/UIElements/mainWindow.cpp
src/UIElements/EMGraph.h
src/UIElements/EMGraph.cpp
src/UIElements/MenuBar.h
src/UIElements/MenuBar.cpp
src/UIElements/generic/pane.h
src/UIElements/generic/pane.cpp
src/UIElements/generic/button.h
src/UIElements/generic/button.cpp
src/UIElements/generic/container.h
src/UIElements/generic/container.cpp
src/UIElements/generic/textPane.h
src/UIElements/generic/textPane.cpp
src/calculations.h
src/calculations.cpp
src/IOHandler.h
src/IOHandler.cpp
)

add_executable(Stellar_Calculator ${SOURCES})
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} SDL2_ttf::SDL2_ttf)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf)


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
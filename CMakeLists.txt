CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

SET (CMAKE_CXX_STANDARD 14)

IF (NOT_CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF()

PROJECT(NukeOut)

SET(dot_VERSION_MAJOR 1)
SET(dot_VERSION_MINOR 0)

CONFIGURE_FILE(
	"${PROJECT_SOURCE_DIR}/Include/Config.h.in"
	"${PROJECT_SOURCE_DIR}/Include/Config.h"
)
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

SET(EXECUTABLE_NAME "NukeOut")
ADD_EXECUTABLE(${EXECUTABLE_NAME} Source/Main.cpp Source/Application.cpp Source/Game.cpp Source/JumpGame.cpp Source/TextGame.cpp Source/Menu.cpp Source/Level.cpp Source/Entity_Brick.cpp Source/Entity_Wall.cpp Source/Entity_Paddle.cpp Source/Entity_Ball.cpp Source/Entity_Background.cpp Source/TextureManager.cpp Source/MathHelper.cpp)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake_Modules" ${CMAKE_MODULE_PATH})

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

ADD_CUSTOM_COMMAND(TARGET ${EXECUTABLE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/Assets Assets)
		
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)
IF (SFML_FOUND)
	INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
ENDIF()
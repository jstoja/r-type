CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT ("R-Type")


#
# Variable
#

#SET (EXECUTABLE_OUTPUT_PATH CMAKE_CURRENT_LIST_FILE)

# Custom CMake modules
SET (
    CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/CMakeModules ${CMAKE_MODULE_PATH}
)

#
# Dependencies
#

# Find SFML
FIND_PACKAGE (SFML 2 REQUIRED window graphics)

# Find OpenGL
FIND_PACKAGE (OpenGL REQUIRED)

# Find Glew
FIND_PACKAGE (GLEW REQUIRED)

#
# Include Directories
#

INCLUDE_DIRECTORIES (
	Commons/src
    ${SFML_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

#
# Sources
#

# Commons
FILE (
    GLOB_RECURSE
    COMMONS_SOURCE
    Commons/src/*
)

# Server
FILE (
    GLOB_RECURSE
    SERVER_SOURCE
    Server/src/*
)

# Client
FILE (
    GLOB_RECURSE
    CLIENT_SOURCE
    Client/src/*
)

#
# Exec
#

# Client
ADD_EXECUTABLE(
    Client
    ${COMMONS_SOURCE}
    ${CLIENT_SOURCE}
)

# Server
ADD_EXECUTABLE(
    Server
    ${COMMONS_SOURCE}
    ${SERVER_SOURCE}
)

#
# Library linking
#

TARGET_LINK_LIBRARIES (
    Client
    ${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

IF(WIN32)
	FILE (
		GLOB_RECURSE
		LIBLIST
		${SFML_ROOT}/bin/*.dll
		${GLEW_ROOT}/bin/*.dll
	)


	FOREACH(lib ${LIBLIST})
		IF(EXISTS ${lib})
			MESSAGE(STATUS ${lib})
			add_custom_command(TARGET Client COMMAND ${CMAKE_COMMAND} -E copy ${lib} ${CMAKE_BINARY_DIR})
		ENDIF()
	ENDFOREACH(lib)
ENDIF(WIN32)
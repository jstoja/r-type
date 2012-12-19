CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT ("R-Type")

#
# Variable
#

SET (RTYPE_BUNDLE_PATH ${CMAKE_SOURCE_DIR}/Bin)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RTYPE_BUNDLE_PATH})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RTYPE_BUNDLE_PATH})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RTYPE_BUNDLE_PATH})

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

iF(UNIX)
    TARGET_LINK_LIBRARIES (Client pthread)
    TARGET_LINK_LIBRARIES (Server pthread)
ENDIF(UNIX)

#
# Copy resources to bundle directory (post build)
#

ADD_CUSTOM_COMMAND (
    TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/Resources"
        $<TARGET_FILE_DIR:Server>/Resources)

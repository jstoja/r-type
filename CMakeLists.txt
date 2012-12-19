CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT ("R-Type")

#
# Variables
#

SET (RTYPE_BUNDLES_PATH ${CMAKE_SOURCE_DIR}/Bin)
SET (RTYPE_CLIENT_BUNDLE_PATH ${RTYPE_BUNDLES_PATH}/Client)
SET (RTYPE_SERVER_BUNDLE_PATH ${RTYPE_BUNDLES_PATH}/Server)

#
# Custom CMake modules
#

SET (
    CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/CMakeModules ${CMAKE_MODULE_PATH}
)

#
# Dependencies
#

# Find SFML
FIND_PACKAGE (SFML 2 REQUIRED window graphics audio)

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

FILE (
    GLOB_RECURSE
    CLIENT_RESOURCES
    Client/Resources/*
)

#
# Exec
#

# Client
ADD_EXECUTABLE(
    Client
    MACOSX_BUNDLE
    ${COMMONS_SOURCE}
    ${CLIENT_SOURCE}
    ${CLIENT_RESOURCES}
)

SET_SOURCE_FILES_PROPERTIES (
  ${CLIENT_RESOURCES}
  PROPERTIES
  MACOSX_PACKAGE_LOCATION Resources
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

iF (UNIX)
    TARGET_LINK_LIBRARIES (Client pthread)
    TARGET_LINK_LIBRARIES (Server pthread)
ENDIF(UNIX)

#
# Setup bundles
#

# Client bundle

SET_PROPERTY (
    TARGET Client
    PROPERTY RUNTIME_OUTPUT_DIRECTORY ${RTYPE_CLIENT_BUNDLE_PATH}
)

SET_PROPERTY (
    TARGET Client
    PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RTYPE_CLIENT_BUNDLE_PATH}
)

SET_PROPERTY (
    TARGET Client
    PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RTYPE_CLIENT_BUNDLE_PATH}
)

IF (APPLE)
# Mac Bundle (.app)

SET_PROPERTY (
    TARGET Client
    PROPERTY MACOSX_BUNDLE_ICON_FILE icon.icns
)

ELSE ()

# Copy resources to bundle directory

ADD_CUSTOM_COMMAND (
    TARGET Client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/Client/Resources"
        ${RTYPE_CLIENT_BUNDLE_PATH}/Resources)
        
ENDIF ()

# Server bundle

SET_PROPERTY (
    TARGET Server
    PROPERTY RUNTIME_OUTPUT_DIRECTORY ${RTYPE_SERVER_BUNDLE_PATH}
)

SET_PROPERTY (
    TARGET Server
    PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RTYPE_SERVER_BUNDLE_PATH}
)

SET_PROPERTY (
    TARGET Server
    PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RTYPE_SERVER_BUNDLE_PATH}
)

# 
# Copy resources to bundle directory
# 

ADD_CUSTOM_COMMAND (
    TARGET Server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/Server/Resources"
        ${RTYPE_SERVER_BUNDLE_PATH}/Resources
)

#
# Setup building of tests
#

FILE (
    GLOB
    TESTS_FILES
    ${CMAKE_SOURCE_DIR}/Tests/*.cpp
)

SET (RTYPE_TESTS_PATH ${RTYPE_BUNDLES_PATH}/Tests)

FOREACH (TEST_FILE ${TESTS_FILES})
    # Get test file name without extension
    GET_FILENAME_COMPONENT (
        TEST_NAME
        ${TEST_FILE}
        NAME_WE
    )

    SET (TEST_NAME Test_${TEST_NAME})

    # Create test binary
    ADD_EXECUTABLE (
        ${TEST_NAME}
        ${TEST_FILE}
    )
    
    # Add dependency to all used libraries
    TARGET_LINK_LIBRARIES (
        ${TEST_NAME}
        ${SFML_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
    )
    
    # Put binaries in a Tests directory
    SET_PROPERTY (
        TARGET ${TEST_NAME}
        PROPERTY RUNTIME_OUTPUT_DIRECTORY RTYPE_TESTS_PATH
    )

    SET_PROPERTY (
        TARGET ${TEST_NAME}
        PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RTYPE_TESTS_PATH}
    )

    SET_PROPERTY (
        TARGET ${TEST_NAME}
        PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RTYPE_TESTS_PATH}
    )
ENDFOREACH ()
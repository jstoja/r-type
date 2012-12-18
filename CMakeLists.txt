CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT ("R-Type")


#
# Variable
#

SET (EXECUTABLE_OUTPUT_PATH ..)

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
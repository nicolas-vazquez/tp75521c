project(Server)
cmake_minimum_required(VERSION 2.8)

# The version number.
set (SERVER_VERSION_MAJOR 1)
set (SERVER_VERSION_MINOR 0)


#Include source files
file( GLOB MONGOOSE_FILES src/mongoose/*)

set(SRC_FILES ${MONGOOSE_FILES})

# add the executable
add_executable(server src/main.cpp ${SRC_FILES})


#Include headers
include_directories(${PROJECT_BINARY_DIR})

install(TARGETS server DESTINATION bin)

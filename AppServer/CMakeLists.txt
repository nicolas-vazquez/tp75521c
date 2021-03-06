# If not required version present, finalize execution
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# Set project name and path
set(PROJECT_NAME "appServer")
project(${PROJECT_NAME} C CXX)

message("-- Setting gcc options")
find_package(Boost REQUIRED COMPONENTS random chrono system thread regex filesystem)

# This should prevent linking against the system provided 0.9.8y
set(_OPENSSL_VERSION "")
find_package(OpenSSL 1.0.0 REQUIRED)

# - use ISO C++11 required for RocksDB
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -lz -lrt -pthread -std=c++11 -g -fno-strict-aliasing")
set(WARNINGS "-Wall -Wextra -Wunused-parameter -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winit-self -Winvalid-pch -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wredundant-decls -Wunreachable-code")
set(LD_FLAGS "${LD_FLAGS} -Wl,-z,defs")

set(ROOT_PATH "${${PROJECT_NAME}_SOURCE_DIR}")
# Libs headers folder
set(LIBS_PATH "${ROOT_PATH}/lib")
# SRC folder
set(SRC_PATH "${ROOT_PATH}/src")
set(ROCKSDB_INCLUDE_DIRS "/usr/include/")
set(CPPUNIT_ROOT_DIR "${LIBS_PATH}/cppunit/")

# Tests SRC folder
set(TEST_PATH "${ROOT_PATH}/test/")

set(Casablanca_INCLUDE_DIRS ${LIBS_PATH}/casablanca)

set(Casablanca_LIBRARY ${LIB}cpprest)
set(Casablanca_LIBRARIES ${Casablanca_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_ATOMIC_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
        ${Boost_RANDOM_LIBRARY}
        ${Boost_REGEX_LIBRARY}
        ${Boost_FRAMEWORK}
        ${CMAKE_THREAD_LIBS_INIT}
        ${OPENSSL_LIBRARIES})

# Nombres de las librerías a usar en el proyecto
set(LIBS_NAMES rocksdb z snappy bz2 jsoncpp mongoose cppunit ${Casablanca_LIBRARIES})

# Chequeo la existencia de todas las librerias agregadas
message(STATUS "*** Check for libs existence ***")

foreach (LIB ${LIBS_NAMES})
    find_library(LIB{LIB} NAMES ${LIB})
    if (LIB{LIB}) #False si es 0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, vacio, o si termina en "-NOTFOUND". Caso contrario es TRUE.
        message(STATUS "Lib |${LIB}| found!")
    else (LIB${LIB})
        message(FATAL_ERROR "|${LIB}| lib not found.")
    endif (LIB{LIB})
endforeach (LIB ${LIBS_NAMES})

set(MONGOOSE_CPP "${LIBS_PATH}/mongoose")

set(MONGOOSE_SOURCES
        ${MONGOOSE_SOURCES}
        ${MONGOOSE_CPP}/Utils.cpp
        ${MONGOOSE_CPP}/Controller.cpp
        ${MONGOOSE_CPP}/Mutex.cpp
        ${MONGOOSE_CPP}/mongoose.c
        ${MONGOOSE_CPP}/Request.cpp
        ${MONGOOSE_CPP}/Response.cpp
        ${MONGOOSE_CPP}/Server.cpp
        ${MONGOOSE_CPP}/Session.cpp
        ${MONGOOSE_CPP}/Sessions.cpp
        ${MONGOOSE_CPP}/StreamResponse.cpp
        ${MONGOOSE_CPP}/UploadFile.cpp
        ${MONGOOSE_CPP}/WebController.cpp
        ${MONGOOSE_CPP}/JsonResponse.cpp
        ${MONGOOSE_CPP}/JsonController.cpp
        ${MONGOOSE_CPP}/WebSocket.cpp
        ${MONGOOSE_CPP}/WebSockets.cpp)


include_directories(src)
include_directories(${LIBS_PATH})
include_directories("${MONGOOSE_CPP}")
include_directories("${CPPUNIT_ROOT_DIR}")
include_directories("${ROCKSDB_INCLUDE_DIRS}")
include_directories("${Casablanca_INCLUDE_DIRS}")
include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})


# Compiling executable
message(STATUS "*** Generating executable ***")

# Tests
enable_testing()
add_subdirectory(${TEST_PATH})
add_subdirectory("${PROJECT_SOURCE_DIR}/src/db")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/utils")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/model")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/controllers")


add_executable(${PROJECT_NAME} ${SRC_PATH}/main.cpp ${MONGOOSE_SOURCES})
target_link_libraries(${PROJECT_NAME} mongoose db model controllers utils ${Casablanca_LIBRARIES})




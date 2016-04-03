# If not required version present, finalize execution
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Set project name and path
set(PROJECT_NAME "appServer")
project(${PROJECT_NAME} C CXX)


set(ROOT_PATH "${${PROJECT_NAME}_SOURCE_DIR}")
# Libs headers folder
set(LIBS_PATH "${ROOT_PATH}/lib")
# Src folder
set(SRC_PATH "${ROOT_PATH}/src")

# use ISO C++11 required for RocksDB.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 ")


# Nombres de las librerías a usar en el proyecto
set(LIBS_NAMES rocksdb z snappy bz2 jsoncpp mongoose)

# Chequeo la existencia de todas las librerias agregadas
message(STATUS "*** Check for libs existence ***")

foreach (LIB ${LIBS_NAMES})
    find_library(LIB{LIB} NAMES ${LIB})
    if (LIB{LIB}) #False si es 0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, vacio, o si termina en "-NOTFOUND". Caso contrario es TRUE.
        message(STATUS "Lib |${LIB}| found at |${LIB${LIB}}|")
    else (LIB${LIB})
        message(FATAL_ERROR "|${LIB}| lib not found.")
    endif (LIB{LIB})
endforeach (LIB ${LIBS_NAMES})

set(MONGOOSE_CPP "${PROJECT_SOURCE_DIR}/lib/mongoose")

set(SOURCES
        ${SOURCES}
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

include_directories("${MONGOOSE_CPP}")

# Compiling executable
message(STATUS "*** Generating executable ***")
add_executable(${PROJECT_NAME}
        ${SOURCES}
        src/main.cpp src/controllers/AccountController.cpp src/controllers/AccountController.h
        src/controllers/BaseController.cpp
        src/controllers/BaseController.h
        src/errors/Error.h
        src/errors/EmptyParamError.h
        src/errors/BadJsonError.h src/domain/Entity.cpp src/domain/Entity.h src/domain/User.cpp src/domain/User.h)

#Include library path for compiler
include_directories(${LIBS_PATH})
target_link_libraries(${PROJECT_NAME} ${LIBS_NAMES})


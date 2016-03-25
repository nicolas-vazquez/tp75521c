cmake_minimum_required (VERSION 2.6)
project (appServer)
find_package (Threads)

SET (CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/lib/modules/")
set (SOURCES src/mongoose/mongoose.c)
set(LIBS_ROOT_DIR "${PROJECT_SOURCE_DIR}/lib/")


set (MONGOOSE_CPP "${PROJECT_SOURCE_DIR}/src/mongoose")
set(JSONCPP_ROOT_DIR "${PROJECT_SOURCE_DIR}/src/json")


find_package(JsonCpp)
add_subdirectory(${JSONCPP_ROOT_DIR})
include_directories(${JSONCPP_INCLUDE_DIRS})


include_directories ("${PROJECT_SOURCE_DIR}")



set (SOURCES
    ${SOURCES}
    ${MONGOOSE_CPP}/Utils.cpp
    ${MONGOOSE_CPP}/Controller.cpp
    ${MONGOOSE_CPP}/Mutex.cpp
    ${MONGOOSE_CPP}/Server.cpp
    ${MONGOOSE_CPP}/Session.cpp
    ${MONGOOSE_CPP}/Sessions.cpp
    ${MONGOOSE_CPP}/StreamResponse.cpp
    ${MONGOOSE_CPP}/UploadFile.cpp
    ${MONGOOSE_CPP}/WebController.cpp
    ${MONGOOSE_CPP}/Request.cpp
    ${MONGOOSE_CPP}/Response.cpp
    ${MONGOOSE_CPP}/JsonResponse.cpp
    ${MONGOOSE_CPP}/JsonController.cpp)

include_directories ("${MONGOOSE_CPP}")

# Adding dl
if (NOT WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} dl)
endif (NOT WIN32)

# Adding sockets for Win32
if (WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} ws2_32)
endif (WIN32)

# Compiling library
add_library (appServer ${SOURCES})
target_link_libraries (appServer ${EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# Compiling executable
add_executable (main src/main.cpp)
target_link_libraries (main appServer)

        

# install
set (INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")
configure_file(MongooseConfig.cmake.in MongooseConfig.cmake @ONLY)

install (FILES src/mongoose/mongoose.h DESTINATION "${INCLUDE_INSTALL_DIR}")
install (DIRECTORY src/mongoose DESTINATION "${INCLUDE_INSTALL_DIR}" PATTERN "*.cpp" EXCLUDE)
install (TARGETS appServer DESTINATION lib EXPORT mongoose-targets)
install (EXPORT mongoose-targets DESTINATION "lib/cmake/mongoose" FILE MongooseTargets.cmake)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/MongooseConfig.cmake DESTINATION "lib/cmake/mongoose")

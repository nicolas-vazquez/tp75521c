cmake_minimum_required(VERSION 2.6)
project(appServer)
find_package(Threads)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/lib/modules/")

set(LIBS_ROOT_DIR "${PROJECT_SOURCE_DIR}/lib")
set(ROCKSDB_ROOT_DIR "${LIBS_ROOT_DIR}/rocksdb/")

#Mongoose lib
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
        ${MONGOOSE_CPP}/jsoncpp.cpp
        ${MONGOOSE_CPP}/JsonResponse.cpp
        ${MONGOOSE_CPP}/JsonController.cpp
        ${MONGOOSE_CPP}/WebSocket.cpp
        ${MONGOOSE_CPP}/WebSockets.cpp)


include_directories("${MONGOOSE_CPP}")
include_directories("${PROJECT_SOURCE_DIR}")

add_definitions("-DENABLE_STATS")
add_definitions("-DNO_WEBSOCKET")

set(EXTRA_LIBS ${EXTRA_LIBS} dl)

# Compiling library
add_library(mongoose ${SOURCES})
target_link_libraries(mongoose ${EXTRA_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# install
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")
configure_file(AppServerConfig.cmake.in AppServerConfig.cmake @ONLY)

install(FILES "${LIBS_ROOT_DIR}/mongoose/mongoose.h" DESTINATION "${INCLUDE_INSTALL_DIR}")
install(DIRECTORY "${LIBS_ROOT_DIR}/mongoose" DESTINATION "${INCLUDE_INSTALL_DIR}" PATTERN "*.cpp" EXCLUDE)
install(TARGETS mongoose DESTINATION lib EXPORT mongoose-targets)
install(EXPORT mongoose-targets DESTINATION "lib/cmake/mongoose" FILE AppServerTargets.cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/AppServerConfig.cmake DESTINATION "lib/cmake/mongoose")

#Mongoose lib End

# Compiling executable
add_executable(main src/main.cpp src/controllers/AccountController.cpp src/controllers/AccountController.h
        src/controllers/BaseController.cpp
        src/controllers/BaseController.h
        src/errors/Error.h
        src/errors/EmptyParamError.h
        src/errors/BadJsonError.h)

target_link_libraries(main mongoose)



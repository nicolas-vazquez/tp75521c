project(${PROJECT_NAME})

add_library(utils FileLogger.cpp LockFile.cpp Utils.cpp sha256.cpp)
target_link_libraries(utils ${LIBS_NAMES})



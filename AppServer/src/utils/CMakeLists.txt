project(${PROJECT_NAME})

add_library(utils FileLogger.cpp LockFile.cpp utils.cpp sha256.cpp ConnectionUtils.cpp ConnectionUtils.h)
target_link_libraries(utils ${LIBS_NAMES})



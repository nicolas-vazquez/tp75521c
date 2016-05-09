project(${PROJECT_NAME} C CXX)

add_library(db Database.cpp)
target_link_libraries(db ${LIBS_NAMES})

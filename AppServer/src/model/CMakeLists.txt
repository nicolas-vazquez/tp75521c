project(${PROJECT_NAME} C CXX)

add_library(model AccessToken.cpp Account.cpp Entity.cpp)
target_link_libraries(model utils ${LIBS_NAMES})



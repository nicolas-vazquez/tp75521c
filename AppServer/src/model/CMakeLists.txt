project(${PROJECT_NAME} C CXX)

add_library(model AccessToken.cpp Account.cpp Entity.cpp)
target_link_libraries(model db utils ${LIBS_NAMES})



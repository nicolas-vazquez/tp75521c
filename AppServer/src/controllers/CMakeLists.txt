project(${PROJECT_NAME} C CXX)

add_library(controllers BaseController.cpp accounts/AccountController.cpp matchs/MatchsController.cpp)
target_link_libraries(controllers model ${LIBS_NAMES})



add_executable(AccountTest model/AccountTest.cpp ${SOURCES} main.cpp)
target_link_libraries(AccountTest ${LIBS_NAMES})


add_test(NAME "AccountTest" COMMAND AccountTest)

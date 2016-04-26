add_executable(AccountTest model/AccountTest.cpp main.cpp)
target_link_libraries(AccountTest cppunit)


add_test(NAME "AccountTest" COMMAND AccountTest)

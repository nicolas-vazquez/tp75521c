add_executable(EntityTest model/EntityTest.cpp main.cpp)
target_link_libraries(EntityTest model db ${LIBS_NAMES})

add_executable(AccountTest model/AccountTest.cpp main.cpp )
target_link_libraries(AccountTest model db ${LIBS_NAMES})

add_executable(AccessTokenTest model/AccessTokenTest.cpp main.cpp )
target_link_libraries(AccessTokenTest model db ${LIBS_NAMES})

add_test(NAME "EntityTest" COMMAND EntityTest)
add_test(NAME "AccountTest" COMMAND AccountTest)
add_test(NAME "AccessTokenTest" COMMAND AccessTokenTest)

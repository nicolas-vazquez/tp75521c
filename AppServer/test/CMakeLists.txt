add_executable(AccountTest model/AccountTest.cpp ${SOURCES} main.cpp model/EntityTest.cpp model/EntityTest.h)
target_link_libraries(AccountTest model db ${LIBS_NAMES})

add_executable(EntityTest ${SOURCES} main.cpp)
target_link_libraries(EntityTest model db ${LIBS_NAMES})

add_test(NAME "EntityTest" COMMAND EntityTest)
add_test(NAME "AccountTest" COMMAND AccountTest)

//
// Created by federicofarina on 4/26/16.
//

#ifndef APPSERVER_ACCOUNTTEST_H
#define APPSERVER_ACCOUNTTEST_H

#include <cppunit/extensions/HelperMacros.h>

using namespace CPPUNIT_NS;

class AccountTest : public TestFixture {
CPPUNIT_TEST_SUITE(AccountTest);
        CPPUNIT_TEST(testToJson);
    CPPUNIT_TEST_SUITE_END();

public:
    AccountTest();

    void testToJson();

    virtual ~AccountTest();
};


#endif //APPSERVER_ACCOUNTTEST_H

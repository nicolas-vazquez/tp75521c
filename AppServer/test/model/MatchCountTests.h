//
// Created by federicofarina on 4/26/16.
//

#ifndef APPSERVER_ENTITYTEST_H
#define APPSERVER_ENTITYTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../../src/model/Account.h"

using namespace CPPUNIT_NS;

class MatchCountTest : public TestFixture {
CPPUNIT_TEST_SUITE(MatchCountTest);
        CPPUNIT_TEST(primaryKeyValue);
        CPPUNIT_TEST(getName);
        CPPUNIT_TEST(testAddGetMatch);
        CPPUNIT_TEST(testAddGetAccount);
    CPPUNIT_TEST_SUITE_END();

private:

    MatchCount testMatchCount;

public:
    MatchCountTest();

    void primaryKeyValue();

    void getName();

    void testAddGetMatch();

    void testAddGetAccount();

    virtual void setUp() override;

    virtual void tearDown() override;;

    virtual ~MatchCountTest();


};


#endif //APPSERVER_ENTITYTEST_H

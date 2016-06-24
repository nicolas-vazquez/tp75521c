//
// Created by federicofarina on 4/26/16.
//

#ifndef APPSERVER_MATCHCOUNTTEST_H
#define APPSERVER_MATCHCOUNTTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../../src/model/MatchCount.h"

using namespace CPPUNIT_NS;

class MatchCountTest : public TestFixture {
CPPUNIT_TEST_SUITE(MatchCountTest);
        CPPUNIT_TEST(toJSON);
        CPPUNIT_TEST(fromJSON);
        CPPUNIT_TEST(totalMatches);
        CPPUNIT_TEST(totalAccounts);
    CPPUNIT_TEST_SUITE_END();

private:
    MatchCount testMatchCount;

public:
    MatchCountTest();

    void toJSON();

    void fromJSON();

    void totalMatches();

    void totalAccounts();

    virtual void setUp() override;

    virtual void tearDown() override;;

    virtual ~MatchCountTest();


};


#endif //APPSERVER_MATCHCOUNTTEST_H

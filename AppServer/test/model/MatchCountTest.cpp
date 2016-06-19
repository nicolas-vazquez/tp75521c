//
// Created by federicofarina on 4/26/16.
//

#include "MatchCountTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatchCountTest);

MatchCountTest::MatchCountTest() {
    MatchCount testMatchCount(); 
}

void MatchCountTest::setUp() {
    
}

void MatchCountTest::toJSON() {
    testMatchCount.addMatch();
    testMatchCount.addAccount();
    const Value &value = testMatchCount.toJSON();
    CPPUNIT_ASSERT(!value.get("matches", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("accounts", "no empty").empty());
}

void MatchCountTest::fromJSON() {
    testMatchCount.addMatch();
    testMatchCount.addAccount();
    testMatchCount.fetch();
    int accounts = testMatchCount.getAccounts();

    CPPUNIT_ASSERT(accounts == 1);
}

void MatchCountTest::testAddGetMatch() {
   testMatchCount.addMatch();
   CPPUNIT_ASSERT(testMatchCount.getMatches() == 1);
}

void MatchCountTest::testAddGetAccount() {
   testMatchCount.addAccount();
   CPPUNIT_ASSERT(testMatchCount.getAccounts() == 1);
}

void MatchCountTest::tearDown() {
}

MatchCountTest::~MatchCountTest() {

}


















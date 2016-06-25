//
// Created by federicofarina on 4/26/16.
//

#include "MatchCountTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatchCountTest);

MatchCountTest::MatchCountTest() {

}

void MatchCountTest::setUp() {
    testMatchCount.setId("testId");
    testMatchCount.addAccount();
    testMatchCount.addAccount();
    testMatchCount.addMatch();
    testMatchCount.save();
}

void MatchCountTest::toJSON() {
    const Value &value = testMatchCount.toJSON();
    CPPUNIT_ASSERT(!value.get("matches", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("accounts", "no empty").empty());
}

void MatchCountTest::fromJSON() {
    MatchCount matchCount;
    matchCount.setId("testId");
    matchCount.fetch();
    CPPUNIT_ASSERT(matchCount.getAccounts() == 2);
    CPPUNIT_ASSERT(matchCount.getMatches() == 1);
}

void MatchCountTest::totalMatches() {
    testMatchCount.addMatch();
    int matches = testMatchCount.getMatches();
    CPPUNIT_ASSERT(matches == 2);
}

void MatchCountTest::totalAccounts() {
    testMatchCount.addAccount();
    int accounts = testMatchCount.getAccounts();
    CPPUNIT_ASSERT(accounts == 3);
}

void MatchCountTest::tearDown() {
    testMatchCount.remove();
}

MatchCountTest::~MatchCountTest() {

}

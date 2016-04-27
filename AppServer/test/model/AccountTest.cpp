//
// Created by federicofarina on 4/26/16.
//

#include "AccountTest.h"
#include "../../src/model/Account.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AccountTest);

AccountTest::AccountTest() {

}


void AccountTest::setUp() {
    testAccount.setUsername("anUsername");
    testAccount.setPassword("aPassword");
    testAccount.setUserId("1234");
    testAccount.save();
}


void AccountTest::toJSON() {

    const Value &value = testAccount.toJSON();

    //Tests that all fields are serialized in json result
    CPPUNIT_ASSERT(!value.get("userId", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("username", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("password", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("keptAccounts", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("tossedAccounts", "no empty").empty());
}

void AccountTest::fromJSON() {
    Account account;
    account.setUserId("1234");
    account.fetch();
    CPPUNIT_ASSERT(account.getUsername() == "anUsername");
    CPPUNIT_ASSERT(account.getPassword() == "aPassword");
}


void AccountTest::tearDown() {
    testAccount.remove();
}


AccountTest::~AccountTest() {

}





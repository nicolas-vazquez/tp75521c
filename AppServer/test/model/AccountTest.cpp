//
// Created by federicofarina on 4/26/16.
//

#include <utils/sha256.h>
#include <utils/utils.h>
#include "AccountTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AccountTest);

AccountTest::AccountTest() {

}

void AccountTest::setUp() {
    testAccount.setUsername("1");
    testAccount.setPassword("password");
    testAccount.addKeepAccount("2");
    testAccount.addKeepAccount("3");
    testAccount.addTossAccount("4");
    testAccount.addTossAccount("5");
    testAccount.save();

    testAccount2.setUsername("2");
    testAccount2.setPassword("password2");
    testAccount2.addKeepAccount("1");
    testAccount2.addKeepAccount("3");
    testAccount2.addTossAccount("4");
    testAccount2.addTossAccount("5");
    testAccount2.save();
}

void AccountTest::toJSON() {
    const Value &value = testAccount.toJSON();
    //Tests that all fields are serialized in json result
    CPPUNIT_ASSERT(!value.get("username", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("password", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("keptAccounts", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("tossedAccounts", "no empty").empty());
}

void AccountTest::fromJSON() {
    Account account;
    account.setUsername("1");
    account.fetch();
    CPPUNIT_ASSERT(account.getUsername() == "1");
//    CPPUNIT_ASSERT(account.getPassword() == sha256("password"));
//
//    const vector<string> &keptAccounts = account.getKeptAccounts();
//    CPPUNIT_ASSERT(keptAccounts.size() == 2);
//    CPPUNIT_ASSERT(keptAccounts.at(1) == "2");
//    CPPUNIT_ASSERT(keptAccounts.at(2) == "3");
//
//    const vector<string> &tossedAccounts = account.getTossedAccounts();
//    CPPUNIT_ASSERT(tossedAccounts.size() == 2);
//    CPPUNIT_ASSERT(tossedAccounts.at(0) == "4");
//    CPPUNIT_ASSERT(tossedAccounts.at(1) == "5");
}

void AccountTest::tearDown() {
    testAccount.remove();
}

AccountTest::~AccountTest() {

}

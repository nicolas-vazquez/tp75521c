//
// Created by federicofarina on 4/26/16.
//

#include "EntityTest.h"

EntityTest::EntityTest() {

}

void EntityTest::setUp() {
    testEntity.setUsername("aTestUsername");
    testEntity.setPassword("aPassword");
    testEntity.setUserId("1234");
    testEntity.addKeepAccount("1");
    testEntity.addKeepAccount("2");
    testEntity.addKeepAccount("3");
    testEntity.addTossAccount("4");
    testEntity.addTossAccount("5");
    testEntity.save();
}


void EntityTest::fetched() {
    CPPUNIT_ASSERT(testEntity.fetch());
}

void EntityTest::notFetched() {
    Account account;
    //An account with no userId should not be fetched
    CPPUNIT_ASSERT(account.fetch());
}


void EntityTest::removed() {
    Account account;
    account.setUserId("1456");
    account.save();
    //Should be removed if was saved
    CPPUNIT_ASSERT(account.remove());
}

void EntityTest::notRemoved() {
    Account account;
    account.setUserId("unoNuevo");
    //Should not be removed if saved was not done
    CPPUNIT_ASSERT(account.remove());
}


void EntityTest::tearDown() {
    testEntity.remove();
}

EntityTest::~EntityTest() {

}















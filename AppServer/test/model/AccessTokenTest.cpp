//
// Created by federicofarina on 5/9/16.
//

#include "AccessTokenTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AccessTokenTest);

AccessTokenTest::AccessTokenTest() {

}


void AccessTokenTest::setUp() {
    accessToken.setToken("token");
    accessToken.setUsername("username");
    accessToken.save();
}


void AccessTokenTest::fromJSON() {
    const Value &value = accessToken.toJSON();

    //Tests that all fields are serialized in json result
    CPPUNIT_ASSERT(!value.get("username", "no empty").empty());
}

void AccessTokenTest::toJSON() {
    AccessToken accessToken;
    accessToken.setToken("token");
    CPPUNIT_ASSERT(accessToken.getToken() == "token");
    accessToken.fetch();
    CPPUNIT_ASSERT(accessToken.getUsername() == "username");
}


void AccessTokenTest::tearDown() {
    accessToken.remove();
}

AccessTokenTest::~AccessTokenTest() {

}








//
// Created by federicofarina on 5/9/16.
//

#include <utils/sha256.h>
#include "AccessTokenTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AccessTokenTest);

AccessTokenTest::AccessTokenTest() {

}

void AccessTokenTest::setUp() {
    const string &username = "username";
    const string &password = "password";
    const string &token = sha256(username + password);
    accessToken.setToken(token);
    accessToken.setUsername("username");
    accessToken.save();
}

void AccessTokenTest::fromJSON() {
    AccessToken testToken;
    const string &username = "username";
    const string &password = "password";
    const string &token = sha256(username + password);
    testToken.setToken(token);
    testToken.fetch();
    CPPUNIT_ASSERT(testToken.getUsername() == "username");
}

void AccessTokenTest::toJSON() {
    const Value &value = accessToken.toJSON();
    CPPUNIT_ASSERT(!value.get("token", "no empty").empty());
    CPPUNIT_ASSERT(!value.get("username", "no empty").empty());
}

void AccessTokenTest::tearDown() {
    accessToken.remove();
}

AccessTokenTest::~AccessTokenTest() {

}

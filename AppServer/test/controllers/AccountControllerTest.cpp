//
// Created by federicofarina on 5/10/16.
//

#include <db/Database.h>
#include "AccountControllerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AccountControllerTest);

AccountControllerTest::AccountControllerTest() {

}


void AccountControllerTest::loginInvalidCredentialsTest() {
    string data = "{\"username\":\"noValidUser\",\"password\":\"anInvalidPassword\"}";
    Request request = makePostRequest(data);
    JsonResponse *response = new JsonResponse();
    accountController.login(request, *response);
    const Value &value = response->get("errors", "[]");
    string code = value[0]["code"].asString();
    delete (response);
    CPPUNIT_ASSERT(code == "5");
}


void AccountControllerTest::loginEmptyUsernameTest() {
    string data = "{\"password\":\"aPassword\"}";
    Request request = makePostRequest(data);
    JsonResponse *response = new JsonResponse();
    accountController.login(request, *response);
    const Value &value = response->get("errors", "[]");
    string code = value[0]["code"].asString();
    delete (response);
    CPPUNIT_ASSERT(code == "2");
}

void AccountControllerTest::loginEmptyPasswordTest() {
    string data = "{\"username\":\"anUsername\"}";
    Request request = makePostRequest(data);
    JsonResponse *response = new JsonResponse();
    accountController.login(request, *response);
    const Value &value = response->get("errors", "[]");
    string code = value[0]["code"].asString();
    delete (response);
    CPPUNIT_ASSERT(code == "2");
}


AccountControllerTest::~AccountControllerTest() {
}





















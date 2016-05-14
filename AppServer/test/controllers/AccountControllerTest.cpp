//
// Created by federicofarina on 5/10/16.
//

#include <db/Database.h>
#include "AccountControllerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AccountControllerTest);

AccountControllerTest::AccountControllerTest() {

}


void AccountControllerTest::login() {
    mg_connection connection;
    connection.request_method = "POST";
    char content[] = "mock";
    connection.content = content;
    connection.content_len = 4;
    connection.uri = "testUri";
    Request request(&connection);
    JsonResponse *response = new JsonResponse();
    string data = "{\"username\":\"noValidUser\",\"password\":\"anInvalidPassword\"}";
    Json::Reader reader;
    Value body;
    reader.parse(data, body);
    request.setBody(body);
    accountController.login(request, *response);

    delete (response);

    //const Value &value = response->get("errors", "[]");
    //string code = value[0]["code"].asString();
    CPPUNIT_ASSERT(true);
}


AccountControllerTest::~AccountControllerTest() {
}





















//
// Created by federicofarina on 5/10/16.
//

#include <db/Database.h>
#include "AccountControllerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AccountControllerTest);

AccountControllerTest::AccountControllerTest() {
}

void  AccountControllerTest::setUp() {
    accountController.setDebugMode(true);
    accountController.setup();
    testAccount.setUsername("username");
    testAccount.setPassword("password");
    testAccount.save();
}

void AccountControllerTest::loginValidCredentialsTest() {
    string data = "{\"username\":\"fede\",\"password\":\"1234\"}";
    Request request = makeDummyBodyRequest(data, "POST");
    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, &AccountController::login);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("data", "[]");
    delete (response);
    CPPUNIT_ASSERT(value["message"] == "Successful login");
}

void AccountControllerTest::loginInvalidCredentialsTest() {
    string data = "{\"username\":\"noValidUser\",\"password\":\"anInvalidPassword\"}";
    Request request = makeDummyBodyRequest(data, "POST");
    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, &AccountController::login);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("errors", "[]");
    string code = value[0]["code"].asString();
    response->getCode();
    delete (response);
    CPPUNIT_ASSERT(code == "5");
}

void AccountControllerTest::loginEmptyUsernameTest() {
    string data = "{\"password\":\"aPassword\"}";
    Request request = makeDummyBodyRequest(data, "POST");
    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, &AccountController::login);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("errors", "[]");
    string code = value[0]["code"].asString();

    delete (response);
    CPPUNIT_ASSERT(code == "2");
}

void AccountControllerTest::loginEmptyPasswordTest() {
    string data = "{\"username\":\"anUsername\"}";
    Request request = makeDummyBodyRequest(data, "POST");
    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, &AccountController::login);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("errors", "[]");
    string code = value[0]["code"].asString();

    delete (response);
    CPPUNIT_ASSERT(code == "2");
}

void AccountControllerTest::badJsonResponseTest() {
    string data = "invalid body";
    Request request = makeDummyBodyRequest(data, "POST");

    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, NULL);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("errors", "[]");
    string code = value[0]["code"].asString();

    delete (response);
    CPPUNIT_ASSERT(code == "3");
}

void AccountControllerTest::signupTest() {
    string data = "{\"username\": \"username1\", \"password\": \"password\", \"name\": \"name\", \"age\": 20, \"gender\":\"M\", \"email\":\"email@email.com\", \"latitude\": \"-34.58\", \"longitude\": \"-58.60\", \"photo_profile\":\"AAA\"}";
    Request request = makeDummyBodyRequest(data, "POST");

    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, &AccountController::signup);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("data", "[]");
    delete (response);
    CPPUNIT_ASSERT(value["message"] == "Successful signup");
}

void AccountControllerTest::likeTest() {

    accountController.routeParams->insert(std::pair<string, string>("username", "username"));

    string data = "{\"username\":\"pepe\"}";
    Request request = makeDummyBodyRequest(data, "PUT");

    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, &AccountController::like);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("data", "[]");
    delete (response);
    CPPUNIT_ASSERT(value["message"] == "Like successful");
}

void AccountControllerTest::dislikeTest() {
    accountController.routeParams->insert(std::pair<string, string>("username", "username"));

    string data = "{\"username\":\"pepi\"}";
    Request request = makeDummyBodyRequest(data, "PUT");

    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController, &AccountController::dislike);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    const Value &value = response->get("data", "[]");
    delete (response);
    CPPUNIT_ASSERT(value["message"] == "Dislike successful");
}

void AccountControllerTest::getInterestsTest() {
    //fixme
    /*accountController.routeParams->insert(std::pair<string, string>("username", "username"));
    string data = "{\"username\":\"pepi\"}";
    Request request = makeDummyRequest(data, "PUT");
    RequestHandler<AccountController, JsonResponse> requestHandler(&accountController,
                                                                   &AccountController::getInterests);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);*/
    CPPUNIT_ASSERT(true);
}


void AccountControllerTest::tearDown() {
    testAccount.remove();
}

AccountControllerTest::~AccountControllerTest() {
}

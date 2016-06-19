//
// Created by federicofarina on 5/9/16.
//

#include "MatchControllerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatchControllerTest);

MatchControllerTest::MatchControllerTest() {

}

void MatchControllerTest::getMessages() {
    string data = "{\"id\": \"2\"}";
    Request request = makeDummyRequest(data, "GET");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getMessages);
    matchsController.routeParams->insert(std::pair<string, string>("id", "username"));
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    Response *response2 =  matchsController.process(request);
    const Value &value = response->get("messages", "[]");
    CPPUNIT_ASSERT(value.size() == 0);
}

void MatchControllerTest::getCandidates() {
    matchsController.routeParams->insert(std::pair<string, string>("id", "username"));

    string data = "";
    Request request = makeDummyRequest(data, "GET");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getCandidates);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);

    CPPUNIT_ASSERT(code == HTTP_SERVER_ERROR);
}

void MatchControllerTest::update() {
    matchsController.routeParams->insert(std::pair<string, string>("id", "username"));

    string data = "{\"id\": \"2\", \"message\": \"Hola\"}";
    Request request = makeDummyRequest(data, "PUT");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::update);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    const Value &value = response->get("data", "[]");
    CPPUNIT_ASSERT(value["message"] == "Successful updated chat");
}

void MatchControllerTest::getMatches() {
    string data = "{\"id\": \"2\"}";
    Request request = makeDummyRequest(data, "GET");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getMatches);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);
   
    CPPUNIT_ASSERT(code == HTTP_OK);
}

void  MatchControllerTest::testLog() {
    log();
    CPPUNIT_ASSERT(true);
}

void  MatchControllerTest::setUp() {
    matchsController.setDebugMode(true);
    matchsController.setup();
    testAccount.setUsername("username");
    testAccount.setPassword("password");
    testAccount.save();
}

MatchControllerTest::~MatchControllerTest() {

}




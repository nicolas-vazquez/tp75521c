//
// Created by federicofarina on 5/9/16.
//

#include "MatchControllerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatchControllerTest);

MatchControllerTest::MatchControllerTest() {

}

void MatchControllerTest::getMessages() {
/*    matchsController.routeParams->insert(std::pair<string, string>("id", "username"));
    string data = "{\"id\": \"2\"}";
    Request request = makeDummyRequest(data, "GET");*/
   /* RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getMessages);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);
    CPPUNIT_ASSERT(code == 400);*/
    CPPUNIT_ASSERT(true);
}

void MatchControllerTest::getCandidates() {
/*    matchsController.routeParams->insert(std::pair<string, string>("id", "username"));
    string data = "";
    Request request = makeDummyRequest(data, "GET");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getCandidates);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);*/
    CPPUNIT_ASSERT(true);
}

void MatchControllerTest::update() {
    matchsController.routeParams->insert(std::pair<string, string>("id", "username"));

    string data = "{\"message\": \"Hola\"}";
    Request request = makeDummyRequest(data, "POST");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::update);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);
    CPPUNIT_ASSERT(code == 400);
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




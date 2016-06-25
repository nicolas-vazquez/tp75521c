//
// Created by federicofarina on 5/9/16.
//

#include "MatchControllerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatchControllerTest);

MatchControllerTest::MatchControllerTest() {

}

void  MatchControllerTest::setUp() {
    matchsController.setDebugMode(true);
    matchsController.setup();
    testAccount.setUsername("username");
    testAccount.setPassword("password");
    testAccount.save();
}


void MatchControllerTest::getUnexistentChatMessages() {
    matchsController.routeParams->insert(std::pair<string, string>("id", "user1+user2"));
    Request request = makeDummyRequest("GET", "");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getMessages);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);
    CPPUNIT_ASSERT(code == 400);
}

void MatchControllerTest::getMessagesForEmptyExistentChat() {
    Chat chat("user1+user2");
    chat.save();

    matchsController.routeParams->insert(std::pair<string, string>("id", "user1+user2"));
    Request request = makeDummyRequest("GET", "");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getMessages);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    chat.remove();
    int code = response->getCode();

    Json::Value jsonArray;
    jsonArray.append(Json::Value::null);
    jsonArray.clear();

    const Value &value = response->get("data", "[]");
    CPPUNIT_ASSERT(value["messages"] == jsonArray);

    delete (response);
    CPPUNIT_ASSERT(code == 200);
}


void MatchControllerTest::getMessagesForExistentChat() {
    Chat chat("user1+user2");

    chat.setUser("user1");

    Value message1;
    message1["message"] = "I am user1!";
    chat.update(message1);

    chat.setUser("user2");
    Value message2;
    message2["message"] = "Hi user1!, I am user 2.";
    chat.update(message2);

    chat.save();

    matchsController.routeParams->insert(std::pair<string, string>("id", "user1+user2"));
    Request request = makeDummyRequest("GET", "");
    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getMessages);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);

    chat.remove();
    int code = response->getCode();

    const Value &value = response->get("data", "[]");
    CPPUNIT_ASSERT(value["messages"].size() == 2);

    delete (response);
    CPPUNIT_ASSERT(code == 200);
}


void MatchControllerTest::getCandidates() {
    Request request = makeDummyRequest("GET", "radius=10&longitude=-58.60&latitude=-34.59668");
    request.setUsername((string &) testAccount.getUsername());

    RequestHandler<MatchsController, JsonResponse> requestHandler(&matchsController, &MatchsController::getCandidates);
    JsonResponse *response = (JsonResponse *) requestHandler.process(request);
    int code = response->getCode();
    delete (response);
    CPPUNIT_ASSERT(code == 400);
}

void MatchControllerTest::update() {
    matchsController.routeParams->insert(std::pair<string, string>("id", "username"));

    string data = "{\"message\": \"Este es un nuevo mensaje\"}";
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

void MatchControllerTest::tearDown() {
    testAccount.remove();
}

MatchControllerTest::~MatchControllerTest() {

}

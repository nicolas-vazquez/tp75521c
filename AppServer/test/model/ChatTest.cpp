//
// Created by gisedaye on 6/17/16.
//

#include <utils/sha256.h>
#include "ChatTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ChatTest);

void ChatTest::setUp() {
    testChat = Chat("nico", "fede");
    testChat.setUser("nico");
    Value value;
    value["message"] = "Este es un mensaje inicial";
    testChat.update(value);
    testChat.save();
}

void ChatTest::toJSON() {
    const Value &value = testChat.toJSON();
    CPPUNIT_ASSERT(!value.get("username", "no empty").empty());
}

void ChatTest::fromJSON() {
    testChat.fetch();
    CPPUNIT_ASSERT(testChat.getId() == "fede+nico");
    const Json::Value &messages = testChat.getMessages();
    CPPUNIT_ASSERT(messages[0].get("sender", "") == "nico");
    CPPUNIT_ASSERT(messages[0].get("message", "") == "Este es un mensaje inicial");
}

void ChatTest::update() {
    testChat.setUser("fede");
    Value value;
    value["message"] = "Este es un nuevo mensaje";
    testChat.update(value);
    const Json::Value &messages = testChat.getMessages();
    CPPUNIT_ASSERT(messages[1].get("sender", "") == "fede");
    CPPUNIT_ASSERT(messages[1].get("message", "") == "Este es un nuevo mensaje");
}

void ChatTest::validateIds() {
    Chat chat1("nico", "fede");
    Chat chat2("fede", "nico");
    CPPUNIT_ASSERT(chat1.getId() == chat2.getId());
}

void ChatTest::tearDown() {
    testChat.remove();
}

ChatTest::~ChatTest() {

}

//
// Created by gisedaye on 6/17/16.
//

#include <utils/sha256.h>
#include "ChatTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ChatTest);

void ChatTest::toJSON() {
    Chat testChat2("gii");    
    testChat2.setUser("nico");
    Value value2;
    value2["message"] = "Hola gii";
    testChat2.update(value2);
    testChat2.save();
    const Value &value = testChat2.toJSON();
    CPPUNIT_ASSERT(!value.get("sender", "no empty").empty());
}

void ChatTest::fromJSON() {
    Chat testChat("nico", "fede");    
    Json::Value value;
    value["message"] = "Holaa";
    testChat.update(value);
    testChat.save();
    testChat.fetch();    
    const Json::Value &messages = testChat.getMessages();
    CPPUNIT_ASSERT(messages[0].get("message", "") == "Holaa");
}

void ChatTest::validateIds() {
    Chat testChat("nico", "fede");  
    Chat testChat3("fede", "nico");    
    CPPUNIT_ASSERT(testChat.getId() == testChat3.getId());
}

ChatTest::~ChatTest() {

}





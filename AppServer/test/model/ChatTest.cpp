//
// Created by gisedaye on 6/17/16.
//

#include <utils/sha256.h>
#include "ChatTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ChatTest);

void ChatTest::toJSON() {
    Chat chat("Gise");
    chat.setUser("pepe");
    const Value &value = chat.toJSON();
    CPPUNIT_ASSERT(!value.get("sender", "no empty").empty());
}

void ChatTest::fromJSON() {
    Chat chat("Gise");
    chat.setUser("pepe");
    //chat.update("Hola Gise");
    chat.fetch();
    //const vector<string> &messages = chat.getMessages();

    CPPUNIT_ASSERT(true);
}


ChatTest::~ChatTest() {

}





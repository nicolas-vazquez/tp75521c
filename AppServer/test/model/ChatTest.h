//
// Created by gisedaye on 6/17/16.
//

#ifndef APPSERVER_CHATTEST_H
#define APPSERVER_CHATTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <model/Chat.h>

using namespace CPPUNIT_NS;

class ChatTest : public TestFixture {

CPPUNIT_TEST_SUITE(ChatTest);
        CPPUNIT_TEST(toJSON);
        CPPUNIT_TEST(fromJSON);
        CPPUNIT_TEST(validateIds);
    CPPUNIT_TEST_SUITE_END();

public:

    void toJSON();

    void fromJSON();

    void validateIds();

    virtual ~ChatTest();
};


#endif //APPSERVER_CHATTEST_H

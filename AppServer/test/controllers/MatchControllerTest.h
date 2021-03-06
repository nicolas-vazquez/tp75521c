//
// Created by federicofarina on 5/9/16.
//

#ifndef APPSERVER_MATCHCONTROLLERTEST_H
#define APPSERVER_MATCHCONTROLLERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <controllers/matchs/MatchsController.h>
#include "BaseControllerTest.h"

using namespace CPPUNIT_NS;

class MatchControllerTest : public TestFixture, BaseControllerTest {
CPPUNIT_TEST_SUITE(MatchControllerTest);
        CPPUNIT_TEST(getMessagesForEmptyExistentChat);
        CPPUNIT_TEST(getMessagesForExistentChat);
        CPPUNIT_TEST(getUnexistentChatMessages);
        CPPUNIT_TEST(getCandidates);
        CPPUNIT_TEST(update);
        CPPUNIT_TEST(getMatches);
        CPPUNIT_TEST(testLog);
    CPPUNIT_TEST_SUITE_END();

private:
    MatchsController matchsController;
    Account testAccount;

public:
    MatchControllerTest();

    virtual void setUp();

    void getMessagesForEmptyExistentChat();

    void getUnexistentChatMessages();

    void getMatches();

    void getCandidates();

    void update();

    void testLog();

    void tearDown();

    virtual ~MatchControllerTest();

    void getMessagesForExistentChat();
};


#endif //APPSERVER_MATCHCONTROLLERTEST_H

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
        CPPUNIT_TEST(getMessages);
        CPPUNIT_TEST(getCandidates);
    CPPUNIT_TEST_SUITE_END();

private:
    MatchsController matchsController;
    Account testAccount;

public:
    MatchControllerTest();

    virtual void setUp();

    void getMessages();

    void getMatches();

    void getCandidates();

    void update();

    virtual ~MatchControllerTest();
};


#endif //APPSERVER_MATCHCONTROLLERTEST_H

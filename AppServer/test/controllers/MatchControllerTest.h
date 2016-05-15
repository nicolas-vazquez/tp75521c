//
// Created by federicofarina on 5/9/16.
//

#ifndef APPSERVER_MATCHCONTROLLERTEST_H
#define APPSERVER_MATCHCONTROLLERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <controllers/matchs/MatchsController.h>
#include "BaseTestController.h"

using namespace CPPUNIT_NS;

class MatchControllerTest : public TestFixture, BaseTestController {
CPPUNIT_TEST_SUITE(MatchControllerTest);
    CPPUNIT_TEST_SUITE_END();

private:
    MatchsController matchsController;

public:
    MatchControllerTest();

    virtual ~MatchControllerTest();
};


#endif //APPSERVER_MATCHCONTROLLERTEST_H

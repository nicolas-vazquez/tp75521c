//
// Created by federicofarina on 5/10/16.
//

#ifndef APPSERVER_ACCOUNTCONTROLLERTEST_H
#define APPSERVER_ACCOUNTCONTROLLERTEST_H

#include <utils/FileLogger.h>
#include <cppunit/extensions/HelperMacros.h>
#include <controllers/accounts/AccountController.h>
#include "BaseTestController.h"

using namespace CPPUNIT_NS;

class AccountControllerTest : public TestFixture, BaseTestController {
CPPUNIT_TEST_SUITE(AccountControllerTest);
        CPPUNIT_TEST(loginInvalidCredentialsTest);
        CPPUNIT_TEST(loginEmptyPasswordTest);
        CPPUNIT_TEST(loginEmptyUsernameTest);
    CPPUNIT_TEST_SUITE_END();

private:
    AccountController accountController;

public:
    AccountControllerTest();

    void loginInvalidCredentialsTest();

    void loginEmptyUsernameTest();

    void loginEmptyPasswordTest();

    virtual ~AccountControllerTest();
};


#endif //APPSERVER_ACCOUNTCONTROLLERTEST_H

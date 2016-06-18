//
// Created by federicofarina on 5/10/16.
//

#ifndef APPSERVER_ACCOUNTCONTROLLERTEST_H
#define APPSERVER_ACCOUNTCONTROLLERTEST_H

#include <utils/FileLogger.h>
#include <cppunit/extensions/HelperMacros.h>
#include <controllers/accounts/AccountController.h>
#include "BaseControllerTest.h"

using namespace CPPUNIT_NS;

class AccountControllerTest : public TestFixture, BaseControllerTest {
CPPUNIT_TEST_SUITE(AccountControllerTest);
        CPPUNIT_TEST(likeTest);
    CPPUNIT_TEST_SUITE_END();

private:
    Account testAccount;
    AccountController accountController;

public:
    AccountControllerTest();

    virtual void setUp();

    void loginValidCredentialsTest();

    void loginInvalidCredentialsTest();

    void loginEmptyUsernameTest();

    void loginEmptyPasswordTest();

    void badJsonResponseTest();

    void signupTest();

    void likeTest();

    void dislikeTest();

    void getInterestsTest();

    virtual void tearDown();

    virtual ~AccountControllerTest();

};


#endif //APPSERVER_ACCOUNTCONTROLLERTEST_H

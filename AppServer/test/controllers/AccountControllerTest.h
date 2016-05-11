//
// Created by federicofarina on 5/10/16.
//

#ifndef APPSERVER_ACCOUNTCONTROLLERTEST_H
#define APPSERVER_ACCOUNTCONTROLLERTEST_H

#include <utils/FileLogger.h>
#include <cppunit/extensions/HelperMacros.h>
#include <controllers/accounts/AccountController.h>

using namespace CPPUNIT_NS;

class AccountControllerTest : public TestFixture {
CPPUNIT_TEST_SUITE(AccountControllerTest);
        CPPUNIT_TEST(login);
    CPPUNIT_TEST_SUITE_END();

private:
    AccountController accountController;

public:
    AccountControllerTest();

    void login();

    virtual ~AccountControllerTest();

};


#endif //APPSERVER_ACCOUNTCONTROLLERTEST_H

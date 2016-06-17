//
// Created by federicofarina on 4/26/16.
//

#ifndef APPSERVER_ACCOUNTTEST_H
#define APPSERVER_ACCOUNTTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <model/Account.h>

using namespace CPPUNIT_NS;

class AccountTest : public TestFixture {

CPPUNIT_TEST_SUITE(AccountTest);
        CPPUNIT_TEST(toJSON);
        CPPUNIT_TEST(fromJSON);
	CPPUNIT_TEST(getMatchesZero);
	CPPUNIT_TEST(getMatchesMultiple);
    CPPUNIT_TEST_SUITE_END();

private:
    Account testAccount;

public:
    AccountTest();

    void toJSON();

    void fromJSON();

    virtual void setUp() override;

    virtual void tearDown() override;

    void  getMatchesZero();

    void  getMatchesMultiple();  


    virtual ~AccountTest();
};


#endif //APPSERVER_ACCOUNTTEST_H

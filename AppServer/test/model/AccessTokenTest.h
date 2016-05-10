//
// Created by federicofarina on 5/9/16.
//

#ifndef APPSERVER_ACCESSTOKENTEST_H
#define APPSERVER_ACCESSTOKENTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <model/AccessToken.h>


using namespace CPPUNIT_NS;

class AccessTokenTest : public TestFixture {
CPPUNIT_TEST_SUITE(AccessTokenTest);
        CPPUNIT_TEST(toJSON);
        CPPUNIT_TEST(fromJSON);
    CPPUNIT_TEST_SUITE_END();

private:
    AccessToken accessToken;

public:
    AccessTokenTest();

    void toJSON();

    void fromJSON();

    virtual void setUp() override;

    virtual void tearDown() override;;

    virtual ~AccessTokenTest();
};


#endif //APPSERVER_ACCESSTOKENTEST_H

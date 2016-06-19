//
// Created by federicofarina on 5/14/16.
//

#ifndef APPSERVER_BASETESTCONTROLLER_H
#define APPSERVER_BASETESTCONTROLLER_H

#include <mongoose/Request.h>
#include <mongoose/mongoose.h>
#include <mongoose/JsonResponse.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace Mongoose;

class BaseControllerTest {

public:

    BaseControllerTest();
    void log();
    
    Request makeDummyRequest(string data, string method) const;

    virtual ~BaseControllerTest();
};


#endif //APPSERVER_BASETESTCONTROLLER_H

//
// Created by federicofarina on 5/14/16.
//

#ifndef APPSERVER_BASETESTCONTROLLER_H
#define APPSERVER_BASETESTCONTROLLER_H

#include <mongoose/Request.h>

using namespace Mongoose;

class BaseTestController {

public:
    BaseTestController();

    Request makePostRequest(string data) const;

    virtual ~BaseTestController();
};


#endif //APPSERVER_BASETESTCONTROLLER_H

//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_ACCOUNTCONTROLLER_H
#define APPSERVER_ACCOUNTCONTROLLER_H

#include <mongoose/Server.h>
#include <mongoose/JsonResponse.h>
#include "BaseController.h"

using namespace std;
using namespace Mongoose;

class AccountController : public BaseController {
public:

    AccountController();

    void signup(Request &request, JsonResponse &response);

    void login(Request &request, JsonResponse &response);

    void setup();

    virtual ~AccountController();
};


#endif //APPSERVER_ACCOUNTCONTROLLER_H

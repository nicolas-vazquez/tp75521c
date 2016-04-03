//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_ACCOUNTCONTROLLER_H
#define APPSERVER_ACCOUNTCONTROLLER_H

#include <mongoose/Server.h>
#include <mongoose/JsonResponse.h>
#include "BaseController.h"
#include "../model/Account.h"
#include "../errors/BadJsonError.h"
#include "../errors/EmptyParamError.h"

using namespace std;
using namespace Mongoose;

class AccountController : public BaseController {
public:

    AccountController();

    void setup();

    void signup(Request &request, JsonResponse &response);

    void login(Request &request, JsonResponse &response);

    void validateUserNameAndPassword(string username, string password, vector<Error *> &errors);

    virtual ~AccountController();
};


#endif //APPSERVER_ACCOUNTCONTROLLER_H

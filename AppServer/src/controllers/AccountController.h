//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_ACCOUNTCONTROLLER_H
#define APPSERVER_ACCOUNTCONTROLLER_H

#include <mongoose/Server.h>
#include <mongoose/JsonController.h>

using namespace std;
using namespace Mongoose;

class AccountController : public JsonController {
public:
    void login(Request &request, JsonResponse &response);
    void setup();
};


#endif //APPSERVER_ACCOUNTCONTROLLER_H

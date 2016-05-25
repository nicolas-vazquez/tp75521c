//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_ACCOUNTCONTROLLER_H
#define APPSERVER_ACCOUNTCONTROLLER_H

#include <utils/sha256.h>
#include <mongoose/Server.h>
#include <mongoose/JsonResponse.h>
#include "../BaseController.h"
#include "../../model/Account.h"
#include "../../errors/BadJsonError.h"
#include "../../errors/EmptyParamError.h"
#include "../../errors/UsernameAlreadyInUseError.h"
#include "../../errors/UnauthorizedError.h"
#include <cpprest/http_client.h>

using namespace std;
using namespace Mongoose;
using namespace web;
using namespace utility;
using namespace http;
using namespace http::client;

class AccountController : public BaseController {
private:
public:
    virtual bool requireAuthentication(string method, string url) override;

    string generateToken(const string &username, const string &password) const;

    string encodePassword(const string &password) const;

public:

    AccountController();

    void setup();

    void signup(Request &request, JsonResponse &response);

    void login(Request &request, JsonResponse &response);

    void like(Request &request, JsonResponse &response);

    void dislike(Request &request, JsonResponse &response);

    void validateAccount(string username, string password, vector<Error *> &errors);

    JsonResponse &buildLoginResponse(const string &username, const string &password, JsonResponse &responseBody) const;

    virtual ~AccountController();
};


#endif //APPSERVER_ACCOUNTCONTROLLER_H

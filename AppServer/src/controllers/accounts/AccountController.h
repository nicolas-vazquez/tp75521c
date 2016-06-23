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
#include "../../model/MatchCount.h"
#include "../../errors/BadJsonError.h"
#include "../../errors/ServerError.h"
#include "../../errors/BadParamError.h"
#include "../../errors/EmptyParamError.h"
#include "../../errors/ResourceNotFound.h"
#include "../../errors/UsernameAlreadyInUseError.h"
#include "../../errors/UnauthorizedError.h"
#include <utils/ConnectionUtils.h>
#include <cpprest/http_client.h>

using namespace std;
using namespace Mongoose;
using namespace web;
using namespace utility;
using namespace http;
using namespace http::client;



class AccountController : public BaseController {

public:

    AccountController();

    virtual bool requireAuthentication(string method, string url) override;

    string generateToken(const string &username, const string &password) const;

    void setup();

    void signup(Request &request, JsonResponse &response);

    void login(Request &request, JsonResponse &response);

    void like(Request &request, JsonResponse &response);

    void dislike(Request &request, JsonResponse &response);

    void getInterests(Request &request, JsonResponse &response);

    void validateAccount(string username, string password, vector<Error *> &errors);

    virtual ~AccountController();

};


#endif //APPSERVER_ACCOUNTCONTROLLER_H

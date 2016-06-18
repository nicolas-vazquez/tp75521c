//
// Created by fedefarina on 17/04/16.
//

#ifndef APPSERVER_MATCHSCONTROLLER_H
#define APPSERVER_MATCHSCONTROLLER_H

#include "../BaseController.h"
#include <mongoose/Server.h>
#include <mongoose/JsonResponse.h>
#include "../../model/Chat.h"
#include "../../model/Account.h"
#include "../../errors/BadJsonError.h"
#include "../../errors/ServerError.h"
#include "../../errors/EmptyParamError.h"
#include "../../errors/UsernameAlreadyInUseError.h"
#include "../../errors/UnauthorizedError.h"
#include <utils/ConnectionUtils.h>
#include <cpprest/http_client.h>
#include "utils/utils.h"

using namespace std;
using namespace Mongoose;
using namespace web;
using namespace utility;
using namespace http;
using namespace http::client;

class MatchsController : public BaseController {

public:
    virtual bool requireAuthentication(string method, string url) override;

    MatchsController();

    void getMatches(Request &request, JsonResponse &response);

    void getCandidates(Request &request, JsonResponse &response);

    void getMessages(Request &request, JsonResponse &response);

    void update(Request &request, JsonResponse &response);

    void setup();

    virtual ~MatchsController();
};

#endif //APPSERVER_MATCHSCONTROLLER_H

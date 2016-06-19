//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_BASECONTROLLER_H
#define APPSERVER_BASECONTROLLER_H

#include <mongoose/JsonController.h>
#include <mongoose/Server.h>
#include <casablanca/cpprest/json.h>
#include "../errors/Error.h"
#include "../errors/BadJsonError.h"
#include "../model/AccessToken.h"


using namespace std;
using namespace Json;
using namespace Mongoose;

typedef web::json::value WebJsonValue;

class BaseController : public JsonController {

protected:
    bool debugMode = false;

public:
    map<string, string> *routeParams;

    BaseController();

    virtual Response *process(Request &request) override;

    virtual bool handles(string method, string url) override;

    virtual bool requireAuthentication(string method, string url);

    bool tokenAuthenticate(Request &request);

    JsonResponse &sendUnauthorizedResponse(JsonResponse &response);

    JsonResponse &sendBadJsonError(JsonResponse &response);

    bool isDebugMode() const;

    void setDebugMode(bool debugMode);


    virtual ~BaseController();

protected:

    void sendErrors(JsonResponse &response, vector<Error *> &errors, int responseCode);

    void sendResult(JsonResponse &response, JsonResponse &responseBody, int responseCode);

    void setHeaders(JsonResponse &response);

private:

    string replaceRouteParams(string key) const;

    void parseRouteParams(const string &key, const string &currentRequest) const;

};


#endif //APPSERVER_BASECONTROLLER_H

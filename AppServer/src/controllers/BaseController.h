//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_BASECONTROLLER_H
#define APPSERVER_BASECONTROLLER_H

#include <mongoose/JsonController.h>
#include <mongoose/Server.h>
#include "../errors/Error.h"
#include "../errors/BadJsonError.h"


using namespace std;
using namespace Json;
using namespace Mongoose;

class BaseController : public JsonController {
protected:

    map<string, string> *routeParams;

public:

    virtual Response *process(Request &request) override;

    virtual bool handles(string method, string url) override;

    BaseController();

    virtual ~BaseController();

protected:

    void sendErrors(JsonResponse &response, vector<Error *> &errors, int responseCode);

    void sendResult(JsonResponse &response, JsonResponse &responseBody, int responseCode);

    void setHeaders(JsonResponse &response);

    bool bodyFormatHandler(Request &request, Value &body);

    void sendBadJsonError(JsonResponse &response);

    bool tokenAuthenticate(Request &request, Value &body);

private:

    void replaceRouteParams(string &key, string requestUrl) const;
};


#endif //APPSERVER_BASECONTROLLER_H

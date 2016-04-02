//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_BASECONTROLLER_H
#define APPSERVER_BASECONTROLLER_H

#include <mongoose/JsonController.h>
#include <mongoose/Server.h>
#include "../errors/Error.h"
#include "rocksdb/db.h"

using namespace std;
using namespace Mongoose;
using namespace rocksdb;

class BaseController : public JsonController {
private:
    DB* db;

protected:
    void sendError(JsonResponse &response, vector<Error *> &errors, int responseCode);

    void sendResult(JsonResponse &response, JsonResponse &responseBody, int responseCode);

    void setHeaders(JsonResponse &response);
};


#endif //APPSERVER_BASECONTROLLER_H

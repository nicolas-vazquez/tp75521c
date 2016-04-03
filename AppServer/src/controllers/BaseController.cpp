//
// Created by fedefarina on 26/03/16.
//

#include "BaseController.h"


BaseController::BaseController() {

}

/*

{
    "errors": [
        {
            "code": errorCode,
            "title": "error"
        }
    ]
}
  */

void BaseController::sendError(JsonResponse &response, vector<Error *> &errors, int responseCode) {

    response.setCode(responseCode);
    setHeaders(response);
    string message;
    int code;
    for (unsigned int i = 0; i < errors.size(); i++) {
        Error *error = errors[i];
        message = error->getMessage();
        code = error->getCode();
        response["errors"][i]["code"] = code;
        response["errors"][i]["message"] = message;
        delete (error);
    }
    errors.clear();
}

void BaseController::sendResult(JsonResponse &response, JsonResponse &responseBody, int responseCode) {
    response.setCode(responseCode);
    response["data"] = responseBody;
    setHeaders(response);
}

void BaseController::setHeaders(JsonResponse &response) {
    response.setHeader("Content-Type", "application/json; charset=utf-8");
}

BaseController::~BaseController() {

}
















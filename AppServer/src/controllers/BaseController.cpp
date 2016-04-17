//
// Created by fedefarina on 26/03/16.
//

#include "BaseController.h"
#include "../utils/Logger.h"


BaseController::BaseController() {

}

bool BaseController::bodyFormatHandler(Request &request, Value &body) {
    string data = request.getData();
    Json::Reader reader;
    return reader.parse(data, body);
}

bool BaseController::tokenAuthenticate(Request &request, Value &body) {


}

void BaseController::sendBadJsonError(JsonResponse &response) {
    vector<Error *> errors;
    BadJsonError *badJsonError = new BadJsonError();
    errors.push_back(badJsonError);
    sendErrors(response, errors, 400);
}

/* Errors format
{
    "errors": [
        {
            "code": errorCode,
            "title": "error"
        }
    ]
}
*/
void BaseController::sendErrors(JsonResponse &response, vector<Error *> &errors, int responseCode) {
    Logger::error(response.asString());
    cout << "Sending error" << endl;
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


/* Responses format
{
  "data": {
    ...
  }
}
*/
void BaseController::sendResult(JsonResponse &response, JsonResponse &responseBody, int responseCode) {
    Logger::info(response.asString());
    cout << "Sending result" << endl;
    response.setCode(responseCode);
    response["data"] = responseBody;
    setHeaders(response);
}

void BaseController::setHeaders(JsonResponse &response) {
    response.setHeader("Content-Type", "application/json; charset=utf-8");
}

BaseController::~BaseController() {

}

















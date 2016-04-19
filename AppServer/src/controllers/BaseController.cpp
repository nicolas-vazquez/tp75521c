//
// Created by fedefarina on 26/03/16.
//

#include <regex>
#include "BaseController.h"
#include "../utils/Logger.h"


BaseController::BaseController() {
    routeParams = new map<string, string>();
}

bool BaseController::bodyFormatHandler(Request &request, Value &body) {
    string data = request.getData();
    Json::Reader reader;
    return reader.parse(data, body);
}


bool BaseController::handles(string method, string url) {

    bool handle = false;
    string incomingKey = method + ":" + url;

    map<string, RequestHandlerBase *>::iterator it;
    for (it = routes.begin(); it != routes.end(); it++) {
        string key = it->first;

        replaceRouteParams(key, incomingKey);

        if (regex_match(incomingKey, regex(key))) {
            handle = true;
            break;
        }
    }

    return handle;
}


Response *BaseController::process(Request &request) {
    cout << "Process" << endl;
    Response *response = NULL;

    map<string, RequestHandlerBase *>::iterator it;
    for (it = routes.begin(); it != routes.end(); it++) {
        string key = it->first;


        string requestKey = request.getMethod() + ":" + request.getUrl();

        replaceRouteParams(key, requestKey);

        if (regex_match(requestKey, regex(key))) {
            response = it->second->process(request);
            break;
        }

        routeParams->clear();
    }

    return response;
}


void BaseController::replaceRouteParams(string &key, string requestUrl) const {

    unsigned long firstPos = key.find("{");
    unsigned long secondPos = key.find("}");

    //Replace {param} with .*
    while (firstPos != string::npos && secondPos != string::npos) {

        //@Fede Due to a mongoose cpp "double url check" issue we have to run this method twice, so we validate that we are in first one
        if (routeParams->empty()) {
            string requestTail = requestUrl.substr(firstPos);
            unsigned long incominRequestValueEnd = requestTail.find("/");
            if (incominRequestValueEnd != string::npos) {
                string mapKey = key.substr(firstPos + 1, secondPos - firstPos - 1);
                string value = requestUrl.substr(firstPos, incominRequestValueEnd);
                routeParams->insert(std::pair<string, string>(mapKey, value));
                cout << "MapKey:" << mapKey << endl;
                cout << "MapValue:" << value << endl;
            }
        }

        key = key.replace(firstPos, secondPos - firstPos + 1, ".*");
        firstPos = key.find("{");
        secondPos = key.find("}");
    }
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
    delete routeParams;
}

















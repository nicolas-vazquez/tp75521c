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
        string replacedKey = replaceRouteParams(it->first);
        if (regex_match(incomingKey, regex(replacedKey))) {
            handle = true;
            break;
        }
    }

    return handle;
}


Response *BaseController::process(Request &request) {
    Response *response = NULL;

    map<string, RequestHandlerBase *>::iterator it;
    for (it = routes.begin(); it != routes.end(); it++) {
        string key = it->first;

        string currentRequest = request.getMethod() + ":" + request.getUrl();
        string regexKey = replaceRouteParams(key);

        if (regex_match(currentRequest, regex(regexKey))) {

            routeParams->clear();
            //Get map key
            unsigned long firstPos = key.find("{");
            unsigned long secondPos = key.find("}");

            string mapKey = key.substr(firstPos + 1, secondPos - firstPos - 1);

            //Get map value
            string requestTail = currentRequest.substr(firstPos);
            unsigned long incomingRequestValueEnd = requestTail.find("/");
            string value = currentRequest.substr(firstPos, incomingRequestValueEnd);

            routeParams->insert(std::pair<string, string>(mapKey, value));

            response = it->second->process(request);
            break;
        }


    }

    return response;
}

//@Fede Due to a mongoose cpp "double url check" issue we have to run this method twice, so we validate that we are in first one
string BaseController::replaceRouteParams(string key) const {

    string replacedKey = key;
    unsigned long firstPos = replacedKey.find("{");
    unsigned long secondPos = replacedKey.find("}");

    //Replace {param} with .*
    while (firstPos != string::npos && secondPos != string::npos) {
        replacedKey = replacedKey.replace(firstPos, secondPos - firstPos + 1, ".*");
        firstPos = replacedKey.find("{");
        secondPos = replacedKey.find("}");
    }

    return replacedKey;
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

















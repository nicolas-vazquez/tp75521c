//
// Created by fedefarina on 26/03/16.
//

#include "AccountController.h"
#include "../errors/BadJsonError.h"
#include "../errors/EmptyParamError.h"

AccountController::AccountController() {

}

void AccountController::login(Request &request, JsonResponse &response) {

    string data = request.getData();

    Json::Value root;
    Json::Reader reader;
    bool parsedSuccess = reader.parse(data, root);

    vector<Error *> errors;

    if (not parsedSuccess) {
        BadJsonError *badJsonError = new BadJsonError();
        errors.push_back(badJsonError);
        sendError(response, errors, 400);
    } else {
        string username = root.get("username", "").asString();
        string password = root.get("password", "").asString();

        if (username.empty()) {
            EmptyParamError *emptyUserError = new EmptyParamError();
            emptyUserError->setMessage("Empty username");
            errors.push_back(emptyUserError);
        }

        if (password.empty()) {
            EmptyParamError *emptyPassword = new EmptyParamError();
            emptyPassword->setMessage("Empty password");
            errors.push_back(emptyPassword);
        }

        if (!errors.empty()) {
            sendError(response, errors, 400);
        } else {
            JsonResponse jsonResponse;
            jsonResponse["accessToken"] = username + password;
            sendResult(response, jsonResponse, HTTP_OK);
        }
    }
}

void AccountController::signup(Request &request, JsonResponse &response) {

}

void AccountController::setup() {
    setPrefix("/api/accounts");
    addRouteResponse("POST", "/login", AccountController, login, JsonResponse);
}

AccountController::~AccountController() {

}









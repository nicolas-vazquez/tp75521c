//
// Created by fedefarina on 26/03/16.
//

#include "AccountController.h"

AccountController::AccountController() {

}


void AccountController::login(Request &request, JsonResponse &jsonResponse) {

    Json::Value body;
    bool parsed = bodyFormatHandler(request, body);

    vector<Error *> errors;

    if (parsed) {
        string username = body.get("username", "").asString();
        string password = body.get("password", "").asString();

        validateUserNameAndPassword(username, password, errors);
        if (!errors.empty()) {
            sendErrors(jsonResponse, errors, 400);
        } else {
            jsonResponse["access-token"] = "Successful signup";
            sendResult(jsonResponse, jsonResponse, HTTP_OK);
        }

    } else {
        sendBadJsonError(jsonResponse);
    }
}


void AccountController::signup(Request &request, JsonResponse &response) {

    Json::Value body;
    bool parsed = bodyFormatHandler(request, body);

    vector<Error *> errors;

    if (parsed) {
        string username = body.get("username", "").asString();
        string password = body.get("password", "").asString();

        validateUserNameAndPassword(username, password, errors);
        if (!errors.empty()) {
            sendErrors(response, errors, 400);
        } else {

            Account account(username);
            //TODO: encode password before save it.
            account.setPassword(password);
            account.save();

            JsonResponse jsonResponse;
            jsonResponse["message"] = "Successful signup";
            sendResult(response, jsonResponse, HTTP_OK);
        }
    } else {
        sendBadJsonError(response);
    }
}

void AccountController::validateUserNameAndPassword(string username, string password,
                                                    vector<Error *> &errors) {
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
}


void AccountController::setup() {
    setPrefix("/api/accounts");
    addRouteResponse("POST", "/signup", AccountController, signup, JsonResponse);
    addRouteResponse("POST", "/login", AccountController, login, JsonResponse);
}

AccountController::~AccountController() {

}









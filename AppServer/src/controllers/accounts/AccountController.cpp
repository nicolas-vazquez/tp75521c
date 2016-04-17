//
// Created by fedefarina on 26/03/16.
//

#include "AccountController.h"
#include "../../errors/UsernameAlreadyInUseError.h"
#include "../../model/Token.h"

AccountController::AccountController() {

}


void AccountController::login(Request &request, JsonResponse &response) {

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
            bool found = account.fetch();

            JsonResponse jsonResponse;
            if (found) {
                if (account.getPassword() != encodePassword(password)) {
                    jsonResponse["message"] = "Wrong credentials.";
                } else {
                    jsonResponse["message"] = "Successful signup.";
                    const string &accessToken = generateToken(username, password);
                    Token token;
                    token.setToken(accessToken);
                    token.setUsername(username);
                    token.save();
                    jsonResponse["accessToken"] = accessToken;
                }
            } else {
                jsonResponse["message"] = "No account found with given username.";
            }

            sendResult(response, jsonResponse, HTTP_OK);
        }

    } else {
        sendBadJsonError(response);
    }
}

string AccountController::encodePassword(const string &password) const {
    return sha256(password);
}

string AccountController::generateToken(const string &username, const string &password) const {
    return sha256(username + password);
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
            JsonResponse jsonResponse;
            Account account(username);
            bool found = account.fetch();

            if (!found) {
                const string &encodedPassword = encodePassword(password);
                account.setPassword(encodedPassword);
                account.save();
                jsonResponse["message"] = "Successful signup";
            } else {
                errors.push_back(new UsernameAlreadyInUseError());
            }

            if (errors.empty()) {
                sendResult(response, jsonResponse, HTTP_OK);
            } else {
                sendErrors(response, errors, 400);
            }
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









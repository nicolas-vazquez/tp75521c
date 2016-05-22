//
// Created by fedefarina on 26/03/16.
//

#include <utils/FileLogger.h>
#include "AccountController.h"

AccountController::AccountController() {

}


void AccountController::login(Request &request, JsonResponse &response) {

    vector<Error *> errors;

    Json::Value body = request.getBody();

    string username = body.get("username", "").asString();
    string password = body.get("password", "").asString();
    validateAccount(username, password, errors);

    if (!errors.empty()) {
        return sendErrors(response, errors, 400);
    }

    Account account(username);
    JsonResponse responseBody;

    if (account.fetch()) {
        if (account.getPassword() != encodePassword(password)) {
            errors.push_back(new UnauthorizedError());
        } else {
            responseBody["message"] = "Successful login";
            const string &accessToken = generateToken(username, password);
            AccessToken token;
            token.setToken(accessToken);
            token.setUsername(username);
            token.save();
            responseBody["accessToken"] = accessToken;
        }
    } else {
        errors.push_back(new UnauthorizedError());
    }

    if (errors.empty()) {
        sendResult(response, responseBody, HTTP_OK);
    } else {
        sendErrors(response, errors, 401);
    }
}

string AccountController::encodePassword(const string &password) const {
    return sha256(password);
}

string AccountController::generateToken(const string &username, const string &password) const {
    return sha256(username + password);
}

void AccountController::signup(Request &request, JsonResponse &response) {

    vector<Error *> errors;

    const Json::Value body = request.getBody();

    string username = body.get("username", "").asString();
    string password = body.get("password", "").asString();
    validateAccount(username, password, errors);

    if (!errors.empty()) {
        return sendErrors(response, errors, 400);
    }

    JsonResponse jsonResponse;
    Account account(username);


    //If account is not fetched here, fetch the SharedServer to try to fetch
    if (!account.fetch()) {
        utility::string_t address = U("http://localhost:");
        utility::string_t port = U("3000");
        address.append(port);

        http::uri uri = http::uri(address);
        http_client sharedServer(http::uri_builder(uri).append_path(U("/signup")).to_uri());

        web::json::value bodyToShared;
        bodyToShared.operator[]("username") = json::value::string(username);
        bodyToShared.operator[]("password") = json::value::string(username);
        const http_response &sharedResponse = sharedServer.request(methods::POST, U(""), bodyToShared).get();

        if (sharedResponse.status_code() == status_codes::OK) {
            account.setPassword(password);
            account.setUsername(username);
            account.save();
            jsonResponse["message"] = "Successful signup";
        } else {
            //Return response given by sharedServer
            sendResult(response, jsonResponse, sharedResponse.status_code());
        }

    } else {
        errors.push_back(new UsernameAlreadyInUseError());
    }

    if (errors.empty()) {
        sendResult(response, jsonResponse, HTTP_OK);
    } else {
        sendErrors(response, errors, 400);
    }
}


void AccountController::like(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    if (tokenAuthenticate(request)) {
        string keptAccount = routeParams->at("username");
        Account account = request.getUser();
        account.addKeepAccount(keptAccount);
        account.save();
        JsonResponse responseBody;
        responseBody["message"] = "Like successful";
        sendResult(response, responseBody, HTTP_OK);
    } else {
        errors.push_back(new UnauthorizedError());
        sendErrors(response, errors, 401);
    }
}

void AccountController::dislike(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    if (tokenAuthenticate(request)) {
        string tossedAccount = routeParams->at("id");
        Account account = request.getUser();
        account.addTossAccount(tossedAccount);
        account.save();
        JsonResponse responseBody;
        responseBody["message"] = "Dislike successful";
        sendResult(response, responseBody, HTTP_OK);
    } else {
        errors.push_back(new UnauthorizedError());
        sendErrors(response, errors, 401);
    }
}

void AccountController::validateAccount(string username, string password,
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
    addRouteResponse("PUT", "/{username}/like", AccountController, like, JsonResponse);
    addRouteResponse("PUT", "/{username}/dislike", AccountController, dislike, JsonResponse);
}

bool AccountController::requireAuthentication(string method, string url) {
    if ((!method.compare("POST") && !url.compare(getPrefix() + "/login"))
        || (!method.compare("POST") && !url.compare(getPrefix() + "/signup"))) {
        return false;
    }
}

AccountController::~AccountController() {

}

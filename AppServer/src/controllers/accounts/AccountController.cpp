//
// Created by fedefarina on 26/03/16.
//


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
        return sendErrors(response, errors, status_codes::BadRequest);
    }

    Account account(username);
    JsonResponse responseBody;

    int responseFailCode = status_codes::Unauthorized;

    if (!account.fetch()) {

        string_t address = ConnectionUtils::buildConnection();

        http::uri uri = http::uri(address);
        http_client sharedServer(http::uri_builder(uri).append_path(U("/login")).to_uri());

        web::json::value bodyToShared;
        bodyToShared["username"] = json::value::string(username);
        bodyToShared["password"] = json::value::string(password);

        const http_response &sharedResponse = sharedServer.request(methods::POST, U(""), bodyToShared).get();

        status_code statusCode = sharedResponse.status_code();

        if (statusCode != status_codes::OK) {
            responseFailCode = statusCode;
        }


        if (statusCode == status_codes::OK) {
            buildLoginResponse(username, password, responseBody);
        } else if (statusCode == status_codes::Unauthorized) {
            errors.push_back(new UnauthorizedError());
        } else {
            errors.push_back(new ServerError());
        }

        if (errors.empty()) {
            sendResult(response, responseBody, HTTP_OK);
        } else {
            sendErrors(response, errors, responseFailCode);
        }

    } else {
        if (account.getPassword() != encodePassword(password)) {
            errors.push_back(new UnauthorizedError());
        } else {
            buildLoginResponse(username, password, responseBody);
            sendResult(response, responseBody, HTTP_OK);
        }

    }
}

void AccountController::buildLoginResponse(const string &username, const string &password,
                                           JsonResponse &responseBody) const {
    responseBody["message"] = "Successful login";
    const string &accessToken = generateToken(username, password);
    AccessToken token;
    token.setToken(accessToken);
    token.setUsername(username);
    token.save();
    responseBody["accessToken"] = accessToken;
}


void AccountController::signup(Request &request, JsonResponse &response) {

    vector<Error *> errors;

    const Json::Value body = request.getBody();

    string username = body.get("username", "").asString();
    string password = body.get("password", "").asString();
    validateAccount(username, password, errors);

    if (!errors.empty()) {
        return sendErrors(response, errors, status_codes::BadRequest);
    }

    JsonResponse jsonResponse;
    Account account(username);

    int responseFailCode = status_codes::BadRequest;


    //If account is not fetched here, fetch the SharedServer to try to fetch
    if (!account.fetch()) {
        string_t address = ConnectionUtils::buildConnection();
        http::uri uri = http::uri(address);
        http_client sharedServer(http::uri_builder(uri).append_path(U("/users")).to_uri());

        web::json::value bodyToShared;
        bodyToShared["username"] = json::value::string(username);
        bodyToShared["password"] = json::value::string(password);
        const http_response &sharedResponse = sharedServer.request(methods::POST, U(""), bodyToShared).get();

        status_code statusCode = sharedResponse.status_code();

        if (statusCode != status_codes::OK) {
            responseFailCode = statusCode;
        }

        if (statusCode == status_codes::OK) {
            account.setPassword(password);
            account.setUsername(username);
            account.save();
            jsonResponse["message"] = "Successful signup";
        } else if (statusCode == status_codes::BadRequest) {
            errors.push_back(new UsernameAlreadyInUseError());
        } else {
            errors.push_back(new ServerError());
        }
    } else {
        errors.push_back(new UsernameAlreadyInUseError());
    }

    if (errors.empty()) {
        sendResult(response, jsonResponse, HTTP_OK);
    } else {
        sendErrors(response, errors, responseFailCode);
    }
}


string AccountController::encodePassword(const string &password) const {
    return sha256(password);
}

string AccountController::generateToken(const string &username, const string &password) const {
    return sha256(username + password);
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
        sendErrors(response, errors, status_codes::Unauthorized);
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
        sendErrors(response, errors, status_codes::Unauthorized);
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

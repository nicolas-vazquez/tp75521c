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

    JsonResponse responseBody;

    int responseFailCode = status_codes::Unauthorized;

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
        const string &accessToken = generateToken(username, password);

        //Save account locally
        Account account(username);
        account.setPassword(password);
        account.save();

        //Generate a new accessToken in every login
        AccessToken token;
        token.setToken(accessToken);
        token.setUsername(username);
        token.save();

        responseBody["message"] = "Successful login";
        responseBody["profile"] = sharedResponse.extract_json().get().serialize();
        responseBody["accessToken"] = accessToken;

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
    MatchCount matchCount;

    int responseFailCode = status_codes::BadRequest;

    //If account is not fetched here, fetch the SharedServer to try to fetch
    if (!account.fetch()) {
        string_t address = ConnectionUtils::buildConnection();
        http::uri uri = http::uri(address);
        http_client sharedServer(http::uri_builder(uri).append_path(U("/users")).to_uri());

        stringstream_t s;
        s << U(body.toStyledString());

        std::error_code errorCode;
        WebJsonValue json = WebJsonValue::parse(s, errorCode);

        const http_response &sharedResponse = sharedServer.request(methods::POST, U(""), json).get();

        status_code statusCode = sharedResponse.status_code();

        if (statusCode != status_codes::OK) {
            responseFailCode = statusCode;
        }

        if (statusCode == status_codes::OK) {
            if (matchCount.fetch()) {
                matchCount.addAccount();
                matchCount.save();
            }
            account.setPassword(password);
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

string AccountController::generateToken(const string &username, const string &password) const {
    return sha256(username + password);
}

void AccountController::like(Request &request, JsonResponse &response) {
    string keptAccount = routeParams->at("username");
    Account account = request.getUser();
    account.addKeepAccount(keptAccount);
    account.save();
    JsonResponse responseBody;
    responseBody["message"] = "Like successful";
    sendResult(response, responseBody, HTTP_OK);
}

void AccountController::dislike(Request &request, JsonResponse &response) {
    string tossedAccount = routeParams->at("username");
    Account account = request.getUser();
    account.addTossAccount(tossedAccount);
    account.save();
    JsonResponse responseBody;
    responseBody["message"] = "Dislike successful";
    sendResult(response, responseBody, HTTP_OK);
}

void AccountController::validateAccount(string username, string password, vector<Error *> &errors) {
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

void AccountController::getInterests(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    string_t address = ConnectionUtils::buildConnection();
    http::uri uri = http::uri(address);
    http_client sharedServer(http::uri_builder(uri).append_path(U("/interests")).to_uri());
    const http_response &sharedResponse = sharedServer.request(methods::GET, U("")).get();

    JsonResponse jsonResponse;
    int responseFailCode = status_codes::BadRequest;
    status_code statusCode = sharedResponse.status_code();

    if (statusCode == status_codes::OK) {
        jsonResponse["interests"] = sharedResponse.extract_json().get().at("interests").serialize();
    } else {
        responseFailCode = statusCode;
        errors.push_back(new ServerError());
    }

    if (errors.empty()) {
        sendResult(response, jsonResponse, HTTP_OK);
    } else {
        sendErrors(response, errors, responseFailCode);
    }
}

void AccountController::setup() {
    setPrefix("/api/accounts");
    addRouteResponse("POST", "/signup", AccountController, signup, JsonResponse);
    addRouteResponse("POST", "/login", AccountController, login, JsonResponse);
    addRouteResponse("GET", "/interests", AccountController, getInterests, JsonResponse);
    addRouteResponse("PUT", "/{username}/like", AccountController, like, JsonResponse);
    addRouteResponse("PUT", "/{username}/dislike", AccountController, dislike, JsonResponse);
}

bool AccountController::requireAuthentication(string method, string url) {

    if (!BaseController::requireAuthentication(method, url) ||
        (!method.compare("POST") && !url.compare(getPrefix() + "/login"))
        || (!method.compare("POST") && !url.compare(getPrefix() + "/signup"))
        || (!method.compare("GET") && !url.compare(getPrefix() + "/interests"))) {
        return false;
    }
}

AccountController::~AccountController() {

}

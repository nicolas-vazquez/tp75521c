//
// Created by fedefarina on 26/03/16.
//

#include <regex>
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
        if (!account.fetch()) {
            account.setPassword(password);
            account.save();
            MatchCount matchCount;
            matchCount.addAccount();
            matchCount.save();
        }

        //Generate a new accessToken in every login
        AccessToken token;
        token.setToken(accessToken);
        token.setUsername(username);
        token.save();

        responseBody["message"] = "Successful login";


        string_t profile = sharedResponse.extract_json().get().serialize();

        Json::Reader reader;
        Value sharedResponseBody;
        reader.parse(profile, sharedResponseBody);

        responseBody["profile"] = sharedResponseBody;
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
    time_t now = time(0);
    char *dt = ctime(&now);
    return sha256(username + password + dt);
}

void AccountController::like(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    JsonResponse responseBody;
    Account account = request.getUser();
    string keptAccount = routeParams->at("username");

    if (request.getUser().getUsername() != keptAccount &&
        !utils::findValueInArray(account.getKeptAccounts(), keptAccount)) {
        Account otherAccount(keptAccount);
        if (otherAccount.fetch()) {
            if (account.addKeepAccount(keptAccount)) {
                responseBody["match"] = true;
            }
            account.save();
        } else {
            errors.push_back(new ResourceNotFoundError());
        }
    } else {
        errors.push_back(new BadParamError());
    }

    if (errors.empty()) {
        responseBody["message"] = "Like successful";
        sendResult(response, responseBody, HTTP_OK);
    } else {
        sendErrors(response, errors, 400);
    }
}

void AccountController::dislike(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    Account account = request.getUser();
    string tossedAccount = routeParams->at("username");

    if (request.getUser().getUsername() != tossedAccount &&
        !utils::findValueInArray(account.getTossedAccounts(), tossedAccount)) {
        Account otherAccount(tossedAccount);
        if (otherAccount.fetch()) {
            account.addTossAccount(tossedAccount);
            account.save();
        } else {
            errors.push_back(new ResourceNotFoundError());
        }
    } else {
        errors.push_back(new BadParamError());
    }

    if (errors.empty()) {
        JsonResponse responseBody;
        responseBody["message"] = "Dislike successful";
        sendResult(response, responseBody, HTTP_OK);
    } else {
        sendErrors(response, errors, 400);
    }
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

        const string_t &interests = sharedResponse.extract_json().get().at("interests").serialize();
        Json::Reader reader;
        Value sharedResponseBody;
        reader.parse(interests, sharedResponseBody);

        jsonResponse["interests"] = sharedResponseBody;
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

    return !(!BaseController::requireAuthentication(method, url) ||
             (!method.compare("POST") && !url.compare(getPrefix() + "/login"))
             || (!method.compare("POST") && !url.compare(getPrefix() + "/signup"))
             || (!method.compare("GET") && !url.compare(getPrefix() + "/interests")));
}

AccountController::~AccountController() {

}

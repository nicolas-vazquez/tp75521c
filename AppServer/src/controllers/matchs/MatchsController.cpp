//
// Created by fedefarina on 17/04/16.
//

#include <utils/FileLogger.h>
#include "MatchsController.h"
#include "../../model/AccessToken.h"
#include "../../errors/UnauthorizedError.h"

MatchsController::MatchsController() {

}

void MatchsController::getMatches(Request &request, JsonResponse &response) {
    //TODO
}

void MatchsController::getCandidates(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    ostringstream s;
    s << "Probando!!";
    FileLogger::error(s.str());

    Account account = request.getUser();
    string_t address = ConnectionUtils::buildConnection();
    http::uri uri = http::uri(address);
    string_t url = U("/users/" + account.getUsername() + "/candidate");
    http_client sharedServer(http::uri_builder(uri).append_path(url).to_uri());

    const http_response &sharedResponse = sharedServer.request(methods::GET, U("")).get();
    status_code statusCode = sharedResponse.status_code();
    JsonResponse jsonResponse;

    if (statusCode == status_codes::OK) {
        web::json::value responseBody = sharedResponse.extract_json().get();
        vector<string> keptAccounts = account.getKeptAccounts();
        vector<string> tossedAccounts = account.getTossedAccounts();
        for (unsigned int i = 0; i < responseBody.at("users").size(); i++) {
            string username = responseBody.at("users").at(i).at("alias").as_string();
            if (!utils::findValueInArray(tossedAccounts, username) &&
                !utils::findValueInArray(keptAccounts, username)) {
                Account candidate(username);
                if (candidate.fetch() && candidate.getMatches().size() < 3) { //TODO Implement Entity MatchCount
                    jsonResponse["profile"] = responseBody.at("users").as_array()[i].serialize();
//                        jsonResponse["profile"]["name"] = responseBody.at("users").as_array()[i].at("name").as_string();
//                        jsonResponse["profile"]["username"] = responseBody.at("users").as_array()[i].at("alias").as_string();
//                        jsonResponse["profile"]["age"] = responseBody.at("users").as_array()[i].at("age").as_number();
//                        jsonResponse["profile"]["sex"] = responseBody.at("users").as_array()[i].at("sex").as_string();
                }
            }
        }
    } else if (statusCode == status_codes::BadRequest) {
        errors.push_back(new UnauthorizedError());
    } else {
        errors.push_back(new ServerError());
    }

    if (errors.empty()) {
        sendResult(response, jsonResponse, HTTP_OK);
    } else {
        sendErrors(response, errors, statusCode);
    }
}

void MatchsController::update(Request &request, JsonResponse &response) {
    vector<Error *> errors;
    const Json::Value body = request.getBody();

    string message = body.get("message", "").asString();
    string chatId = routeParams->at("id");
    string sender = request.getUser().getUsername();
    Chat chat(chatId);
    chat.setUser(sender);
    chat.update(message);
    chat.save();
    JsonResponse responseBody;
    responseBody["message"] = "Successful updated chat";
    sendResult(response, responseBody, HTTP_OK);
}

void MatchsController::getMessages(Request &request, JsonResponse &response) {
    JsonResponse responseBody;

    string chatId = routeParams->at("id");
    Chat chat(chatId);
    if (chat.fetch()) {
        vector<string> messages = chat.getMessages();
        Value jsonResponse;
        for (unsigned int i = 0; i < messages.size(); i++) {
            Value message(messages[i]);
            jsonResponse.append(message);
        }
        responseBody["messages"] = jsonResponse;
        sendResult(response, responseBody, HTTP_OK);
    }
}

void MatchsController::setup() {
    setPrefix("/api/matches");
    addRouteResponse("GET", "/", MatchsController, getMatches, JsonResponse);
    addRouteResponse("GET", "/candidate", MatchsController, getCandidates, JsonResponse);
    addRouteResponse("GET", "/{id}/messages", MatchsController, getMessages, JsonResponse);
    addRouteResponse("PUT", "/{id}/message", MatchsController, update, JsonResponse);
}


bool MatchsController::requireAuthentication(string method, string url) {
    //fixme
    return false;
}


MatchsController::~MatchsController() {

}

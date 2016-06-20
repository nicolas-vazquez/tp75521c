//
// Created by fedefarina on 17/04/16.
//

#include "MatchsController.h"

MatchsController::MatchsController() {

}

void MatchsController::getMatches(Request &request, JsonResponse &response) {
    vector<string> matches = request.getUser().getMatches();
    string_t address = ConnectionUtils::buildConnection();
    http::uri uri = http::uri(address);
    JsonResponse jsonResponse;
    jsonResponse["matches"] = Json::Value(Json::arrayValue);
    for (std::vector<string>::iterator it = matches.begin(); it != matches.end(); ++it) {
        string_t url = U("/users/" + *it + "/profile");
        http_client sharedServer(http::uri_builder(uri).append_path(url).to_uri());
        const http_response &sharedResponse = sharedServer.request(methods::GET, U("")).get();
        status_code statusCode = sharedResponse.status_code();
        web::json::value responseBody = sharedResponse.extract_json().get();
        if (statusCode == status_codes::OK) {
            jsonResponse["matches"].append(responseBody.serialize());
        }
    }
    sendResult(response, jsonResponse, HTTP_OK);
}

void MatchsController::getCandidates(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    Account account = request.getUser();
    string_t address = ConnectionUtils::buildConnection();
    http::uri uri = http::uri(address);

    string_t url = U("/users/" + account.getUsername() + "/candidates");
    http_client sharedServer(http::uri_builder(uri).append_path(url).to_uri());

    const http_response &sharedResponse = sharedServer.request(methods::GET, U("")).get();
    status_code statusCode = sharedResponse.status_code();
    JsonResponse jsonResponse;

    if (statusCode == status_codes::OK) {
        web::json::value responseBody = sharedResponse.extract_json().get();
        vector<string> keptAccounts = account.getKeptAccounts();
        vector<string> tossedAccounts = account.getTossedAccounts();

        size_t index = 0;
        bool found = false;
        json::value &users = responseBody.at("users");

        while (!found && index < users.size()) {
            string username = users.at(index).at("alias").as_string();
            if (!utils::findValueInArray(tossedAccounts, username) &&
                !utils::findValueInArray(keptAccounts, username)) {
                Account candidate(username);
                MatchCount matchCount;
                int criteria = 1;

                if (matchCount.fetch()) {
                    int totalMatchs = matchCount.getMatches();
                    int totalAccounts = matchCount.getAccounts();
                    criteria = totalMatchs / totalAccounts;
                }

                if (candidate.fetch() && candidate.getMatches().size() <= criteria) {
                    jsonResponse["profile"] = users.as_array()[index].serialize();
                    found = true;
                }
            }
            index++;
        }

        if (!found) {
            //Return empty object if criteria is not matched
            jsonResponse["profile"] = Json::Value(Json::objectValue);
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
//    JsonResponse responseBody;
//
//    string chatId = routeParams->at("id");
//    Chat chat(chatId);
//    if (chat.fetch()) {
//        //vector<string> messages = chat.getMessages();
//        Value jsonResponse;
//        for (unsigned int i = 0; i < messages.size(); i++) {
//            Value message(messages[i]);
//            jsonResponse.append(message);
//        }
//        responseBody["messages"] = jsonResponse;
//        sendResult(response, responseBody, HTTP_OK);
//    }
}

void MatchsController::setup() {
    setPrefix("/api/matches");
    addRouteResponse("GET", "/", MatchsController, getMatches, JsonResponse);
    addRouteResponse("GET", "/candidates", MatchsController, getCandidates, JsonResponse);
    addRouteResponse("GET", "/{id}/messages", MatchsController, getMessages, JsonResponse);
    addRouteResponse("PUT", "/{id}/message", MatchsController, update, JsonResponse);
}

MatchsController::~MatchsController() {

}

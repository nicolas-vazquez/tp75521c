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
            Value value;
            Chat chat(request.getUser().getUsername(), *it);
            if (chat.fetch()) {
                value["chatId"] = chat.getId();
            }
            value["profile"] = responseBody.serialize();
            jsonResponse["matches"].append(value);
        }
    }

    sendResult(response, jsonResponse, HTTP_OK);
}

void MatchsController::getCandidates(Request &request, JsonResponse &response) {
    vector<Error *> errors;

    Account account = request.getUser();
    string_t address = ConnectionUtils::buildConnection();
    http::uri uri = http::uri(address);

    string radius = request.get("radius", "5");
    string latitude = request.get("latitude", "0");
    string longitude = request.get("longitude", "0");

    string_t url = U("/users/" + account.getUsername() + "/candidates");
    uri_builder builder = http::uri_builder(uri);
    builder.append_path(url);
    builder.append_query(U("radius"), U(radius));
    builder.append_query(U("latitude"), U(latitude));
    builder.append_query(U("longitude"), U(longitude));

    http_client sharedServer(builder.to_uri());

    const http_response &sharedResponse = sharedServer.request(methods::GET, U("")).get();
    status_code statusCode = sharedResponse.status_code();
    JsonResponse jsonResponse;

    if (statusCode == status_codes::OK) {
        const json::value &sharedResponseBody = sharedResponse.extract_json().get();
        web::json::value responseBody = sharedResponseBody;
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

                //Only apply this criteria if we have a reasonable amount of accounts.
                if (candidate.fetch() &&
                    (matchCount.getAccounts() <= 100 || candidate.getMatches().size() <= criteria)) {

                    const string_t &profile = users.as_array()[index].serialize();
                    Json::Reader reader;
                    Value candidateResponse;
                    reader.parse(profile, candidateResponse);
                    jsonResponse["profile"] = candidateResponse;
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
        errors.push_back(new BadParamError());
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
    Json::Value body = request.getBody();
    string sender = request.getUser().getUsername();
    string chatId = routeParams->at("id");
    Chat chat(chatId);
    if (chat.fetch()) {
        chat.setUser(sender);
        chat.update(body);
        chat.save();
    } else {
        errors.push_back(new ResourceNotFoundError());
    }

    JsonResponse responseBody;
    responseBody["message"] = "Successful updated chat";

    if (errors.empty()) {
        sendResult(response, responseBody, HTTP_OK);
    } else {
        sendErrors(response, errors, 400);
    }
}

void MatchsController::getMessages(Request &request, JsonResponse &response) {
    vector<Error *> errors;
    JsonResponse responseBody;
    Chat chat(routeParams->at("id"));

    if (chat.fetch()) {
        Value jsonResponse = chat.getMessages();
        responseBody["messages"] = jsonResponse;
        sendResult(response, responseBody, HTTP_OK);
    } else {
        errors.push_back(new ResourceNotFoundError());
        sendErrors(response, errors, 400);
    }
}

void MatchsController::setup() {
    setPrefix("/api/matches");
    addRouteResponse("GET", "/", MatchsController, getMatches, JsonResponse);
    addRouteResponse("GET", "/candidates", MatchsController, getCandidates, JsonResponse);
    addRouteResponse("GET", "/{id}/messages", MatchsController, getMessages, JsonResponse);
    addRouteResponse("POST", "/{id}/message", MatchsController, update, JsonResponse);
}

MatchsController::~MatchsController() {

}

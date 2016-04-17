//
// Created by fedefarina on 17/04/16.
//

#include "MatchsController.h"
#include "../../model/Token.h"
#include "../../errors/UnauthorizedError.h"

MatchsController::MatchsController() {

}

void MatchsController::getMatches(Request &request, JsonResponse &response) {

    string tokenHeader = request.getHeaderKeyValue("Authorization");

    Token token;
    token.setToken(tokenHeader);

    bool found = token.fetch();

    vector<Error *> errors;
    if (found) {
        //todo
    } else {
        errors.push_back(new UnauthorizedError());
        sendErrors(response, errors, 401);
    }
}

void MatchsController::setup() {
    setPrefix("/api/matches");
    addRouteResponse("GET", "/", MatchsController, getMatches, JsonResponse);
}

virtual MatchsController::~MatchsController() {

}
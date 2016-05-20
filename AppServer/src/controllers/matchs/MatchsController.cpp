//
// Created by fedefarina on 17/04/16.
//

#include "MatchsController.h"
#include "../../model/AccessToken.h"
#include "../../errors/UnauthorizedError.h"

MatchsController::MatchsController() {

}

void MatchsController::getMatches(Request &request, JsonResponse &response) {
    //TODO
}

void MatchsController::setup() {
    setPrefix("/api/matches");
    addRouteResponse("GET", "/", MatchsController, getMatches, JsonResponse);
}

MatchsController::~MatchsController() {

}
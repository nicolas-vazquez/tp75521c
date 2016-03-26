//
// Created by fedefarina on 26/03/16.
//

#include "AccountController.h"

void AccountController::login(Request &request, JsonResponse &response) {
    int i;

    for (i = 0; i < 12; i++) {
        response["users"][i]["Name"] = "Bobi";
    }

    response["timestamp"] = (int) time(NULL);
}


void AccountController::setup() {
    // Example of prefix, putting all the urls into "/api"
    setPrefix("/api");

    // Hello demo
    addRouteResponse("GET", "/", AccountController, login, JsonResponse);
    addRouteResponse("GET", "/login", AccountController, login, JsonResponse);
}

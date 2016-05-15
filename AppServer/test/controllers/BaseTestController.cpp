//
// Created by federicofarina on 5/14/16.
//

#include <mongoose/mongoose.h>
#include "BaseTestController.h"


BaseTestController::BaseTestController() {

}

Request BaseTestController::makePostRequest(string data) const {
    mg_connection connection;
    //Only mock data, method it´s not important
    connection.request_method = "POST";
    char content[] = "mock";
    connection.content = content;
    connection.content_len = 4;
    connection.uri = "testUri";
    Request request(&connection);

    Json::Reader reader;
    Value body;
    reader.parse(data, body);
    request.setBody(body);

    return request;
}

BaseTestController::~BaseTestController() {

}
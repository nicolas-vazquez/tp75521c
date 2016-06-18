//
// Created by federicofarina on 5/14/16.
//


#include "BaseControllerTest.h"
#include "../../src/utils/FileLogger.h"


BaseControllerTest::BaseControllerTest() {
}

Request BaseControllerTest::makeDummyRequest(string data, string method) const {
    mg_connection connection;
    //Only mock data, method it´s not important
    connection.request_method = method.c_str();
    connection.num_headers = 0;
    char content[] = "mock";
    connection.content = content;
    connection.content_len = 4;
    connection.uri = "mock";
    Request request(&connection);


    Json::Reader reader;
    Value body;
    reader.parse(data, body);
    request.setBody(body);
    request.setData(data);
    
    return request;
}

BaseControllerTest::~BaseControllerTest() {

}




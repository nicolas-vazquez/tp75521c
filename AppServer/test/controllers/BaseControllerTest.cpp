//
// Created by federicofarina on 5/14/16.
//


#include "BaseControllerTest.h"
#include "../../src/utils/FileLogger.h"


BaseControllerTest::BaseControllerTest() {
}

void BaseControllerTest::log() {
    FileLogger::warn("Warning on BasecontrollerTest");
    FileLogger::warn("Warning on Basecontroller", "BaseControllerTest");
    FileLogger::info("Info on BasecontrollerTest");
    FileLogger::info("Info on BasecontrollerTest", "BaseControllerTest");
    FileLogger::log("Log on BasecontrollerTest", 0);
    FileLogger::log("Log on BasecontrollerTest", 0, "BaseControllerTest");
    FileLogger::debug("Debug on BasecontrollerTest");
    FileLogger::debug("Debug on BasecontrollerTest", "BaseControllerTest");
    FileLogger::error("Error on BasecontrollerTest");
    FileLogger::error("Error on BasecontrollerTest", "BaseControllerTest");
}

Request BaseControllerTest::buildBasicRequest(string method, string queryString) const {
    mg_connection connection;
    //Only mock data, method it´s not important
    connection.request_method = method.c_str();
    connection.num_headers = 0;
    char content[] = "mock";
    connection.content = content;
    connection.content_len = 4;
    connection.uri = "mock";

    connection.query_string = queryString.c_str();

    Request request(&connection);
    return request;
}


Request BaseControllerTest::makeDummyRequest(string method, string queryString) const {
    const Request &request = buildBasicRequest(method, queryString);
    return request;
}

Request BaseControllerTest::makeDummyBodyRequest(string data, string method) const {
    Request request = buildBasicRequest(method, "");
    Json::Reader reader;
    Value body;
    reader.parse(data, body);
    request.setBody(body);
    request.setData(data);
    return request;
}


BaseControllerTest::~BaseControllerTest() {

}




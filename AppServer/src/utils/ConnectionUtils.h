//
// Created by fedefarina on 25/05/16.
//

#ifndef APPSERVER_CONNECTIONUTILS_H
#define APPSERVER_CONNECTIONUTILS_H


#include <iostream>
#include <casablanca/cpprest/details/basic_types.h>

using namespace std;


class ConnectionUtils {

public:
    static utility::string_t buildConnection();
};


#endif //APPSERVER_CONNECTIONUTILS_H

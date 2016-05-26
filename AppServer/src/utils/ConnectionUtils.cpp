//
// Created by fedefarina on 25/05/16.
//

#include "ConnectionUtils.h"

utility::string_t ConnectionUtils::buildConnection() {
    utility::string_t address = U("http://tallerdeprogramacionii-1c2016.herokuapp.com:");
    utility::string_t port = U("80");
    address.append(port);
    return address;
}


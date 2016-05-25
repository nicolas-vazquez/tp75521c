//
// Created by fedefarina on 25/05/16.
//

#include "ConnectionUtils.h"

utility::string_t ConnectionUtils::buildConnection() {
    utility::string_t address = U("http://localhost:");
    utility::string_t port = U("3000");
    address.append(port);
    return address;
}


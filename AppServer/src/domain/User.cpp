//
// Created by fede on 4/3/16.
//

#include "User.h"


Value User::toJSON() {
    Value value;
    value["username"] = username;
    value["password"] = password;
    return value;
}


void User::fromJSON() {

}


string User::getName() {
    return "user";
}

const string &User::getUsername() const {
    return username;
}

void User::setUsername(const string &username) {
    this->username = username;
}

const string &User::getPassword() const {
    return password;
}

void User::setPassword(const string &password) {
    User::password = password;
}


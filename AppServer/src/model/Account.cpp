//
// Created by fede on 4/3/16.
//

#include "Account.h"

Account::Account(const string &username) : username(username) {

}

Value Account::toJSON() {
    Value value;
    value["username"] = username;
    value["password"] = password;
    return value;
}

void Account::fromJSON(Value value) {
    this->username = value.get("username", "").asString();
    this->password = value.get("password", "").asString();
}


string Account::primaryKeyValue() {
    return username;
}


string Account::getName() {
    return "account";
}

const string &Account::getUsername() const {
    return username;
}

const string &Account::getPassword() const {
    return password;
}

void Account::setPassword(const string &password) {
    this->password = password;
}

Account::~Account() {

}




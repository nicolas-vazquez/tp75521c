//
// Created by fedefarina on 07/04/16.
//

#include "Token.h"

Token::Token() {

}

void Token::fromJSON(Value value) {
    username = value["username"].asString();
    token = value["token"].asString();
}

string Token::getName() {
    return "token/";
}

Value Token::toJSON() {
    Value value;
    value["username"] = username;
    value["token"] = token;
    return value;
}

string Token::primaryKeyValue() {
    return this->token;
}


const string &Token::getToken() const {
    return token;
}

void Token::setToken(const string &token) {
    this->token = token;
}

const string &Token::getUsername() const {
    return username;
}

void Token::setUsername(const string &username) {
    this->username = username;
}

Token::~Token() {

}





















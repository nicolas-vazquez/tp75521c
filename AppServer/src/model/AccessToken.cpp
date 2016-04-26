//
// Created by fedefarina on 07/04/16.
//

#include "AccessToken.h"

AccessToken::AccessToken() {

}

void AccessToken::fromJSON(Value value) {
    this->_id = value.get("_id", "").asString();
}

string AccessToken::getName() {
    return "token/";
}

Value AccessToken::toJSON() {
    Value value;
    value["_id"] = _id;
    return value;
}

string AccessToken::primaryKeyValue() {
    return this->token;
}

const string &AccessToken::getToken() const {
    return token;
}

void AccessToken::setToken(const string &token) {
    this->token = token;
}

const string &AccessToken::getUserId() const {
    return _id;
}

void AccessToken::setUserId(const string &_id) {
    this->_id = _id;
}

AccessToken::~AccessToken() {

}

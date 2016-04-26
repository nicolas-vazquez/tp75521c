//
// Created by fede on 4/3/16.
//

#include "Account.h"

Account::Account() {
    this->keptAccounts.empty();
    this->tossedAccounts.empty();
}

Account::Account(const string &userId) : userId(userId) {
    this->keptAccounts.empty();
    this->tossedAccounts.empty();
}

Value Account::toJSON() {
    Value value;
    std::string s1, s2;
    value["userId"] = userId;
    value["username"] = username;
    value["password"] = password;
    value["keptAccounts"] = Utils::arrayToString(this->keptAccounts, s1);
    value["tossedAccounts"] = Utils::arrayToString(this->tossedAccounts, s2);
    return value;
}

void Account::fromJSON(Value value) {
    this->keptAccounts.clear();
    this->tossedAccounts.clear();
    this->userId = value.get("userId", "").asString();
    this->username = value.get("username", "").asString();
    this->password = value.get("password", "").asString();
    Utils::stringToArray(value.get("keptAccounts", "").asString(), this->keptAccounts);
    Utils::stringToArray(value.get("tossedAccounts", "").asString(), this->tossedAccounts);
}

string Account::primaryKeyValue() {
    return userId;
}

string Account::getName() {
    return "account/";
}

void Account::setUsername(const string &username) {
    Account::username = username;
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

void Account::addKeepAccount(const string &keptAccount) {
    this->keptAccounts.push_back(keptAccount);
}

void Account::addTossAccount(const string &tossedAccount) {
    this->tossedAccounts.push_back(tossedAccount);
}

void Account::setUserId(const string &id) {
    this->userId = id;
}

const string &Account::getUserId() const {
    return this->userId;
}

Account::~Account() {
    this->keptAccounts.clear();
    this->tossedAccounts.clear();
}

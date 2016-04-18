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
    value["keptAccounts"] = &keptAccounts[0];
    value["tossedAccounts"] = &tossedAccounts[0];
    return value;
}

void Account::fromJSON(Value value) {
    this->username = value.get("username", "").asString();
    this->password = value.get("password", "").asString();
    Value keepAccounts = value.get("keptAccounts", 0);
    Value tossAccounts = value.get("tossedAccounts", 0);
    for (unsigned int i = 0; i < keepAccounts.size(); i++) {
        this->keptAccounts.push_back(keepAccounts[i].asString());
    }
    for (unsigned int j = 0; j < tossAccounts.size(); j++) {
        this->tossedAccounts.push_back(tossAccounts[j].asString());
    }
}

string Account::primaryKeyValue() {
    return username;
}

string Account::getName() {
    return "account/";
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

Account::~Account() {
    this->keptAccounts.clear();
    this->tossedAccounts.clear();
}

//
// Created by fede on 4/3/16.
//

#include <utils/sha256.h>
#include "Account.h"

Account::Account() {
    this->matches.empty();
    this->keptAccounts.empty();
    this->tossedAccounts.empty();
}

Account::Account(const string &username) : username(username) {
    this->matches.empty();
    this->keptAccounts.empty();
    this->tossedAccounts.empty();
}

Value Account::toJSON() {
    Value value;
    std::string s1, s2, s3;
    value["username"] = username;
    value["password"] = sha256(password);
    value["matches"] = utils::serializeArray(this->matches, s1);
    value["keptAccounts"] = utils::serializeArray(this->keptAccounts, s2);
    value["tossedAccounts"] = utils::serializeArray(this->tossedAccounts, s3);
    return value;
}

void Account::fromJSON(Value value) {
    this->matches.clear();
    this->keptAccounts.clear();
    this->tossedAccounts.clear();
    this->username = value.get("username", "").asString();
    this->password = value.get("password", "").asString();
    utils::deserializeArray(value.get("matches", "").asString(), this->matches);
    utils::deserializeArray(value.get("keptAccounts", "").asString(), this->keptAccounts);
    utils::deserializeArray(value.get("tossedAccounts", "").asString(), this->tossedAccounts);
}

string Account::primaryKeyValue() {
    return username;
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
    Account otherAccount(keptAccount);
    //A liked account is always stored in local database because during like we fetch "otherAccount" from SharedServer
    if (otherAccount.fetch()) {
        vector<string> otherKepts = otherAccount.getKeptAccounts();
        for (std::vector<string>::iterator it = otherKepts.begin(); it != otherKepts.end(); ++it) {
            if (*it == this->username) {
                this->addMatch(keptAccount);
                otherAccount.addMatch(this->username);
                otherAccount.save();
                Chat chat(this->username, keptAccount);
                chat.save();
                MatchCount matchCount;
                if (matchCount.fetch()) {
                    matchCount.addMatch();
                    matchCount.save();
                }
            }
        }
    }
}

void Account::addTossAccount(const string &tossedAccount) {
    this->tossedAccounts.push_back(tossedAccount);
}

const vector<string> &Account::getMatches() const {
    return matches;
}

const vector<string> &Account::getTossedAccounts() const {
    return tossedAccounts;
}

const vector<string> &Account::getKeptAccounts() const {
    return keptAccounts;
}

void Account::addMatch(const string &match) {
    this->matches.push_back(match);
}

Account::~Account() {
    this->matches.clear();
    this->keptAccounts.clear();
    this->tossedAccounts.clear();
}

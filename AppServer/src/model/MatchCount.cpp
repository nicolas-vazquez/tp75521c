#include "MatchCount.h"


MatchCount::MatchCount() {
    if (!fetch()) {
        this->matches = 0;
        this->accounts = 0;
        save();
    }
}

Value MatchCount::toJSON() {
    Value value;
    value["matches"] = matches;
    value["accounts"] = accounts;
    return value;
}

void MatchCount::fromJSON(Value value) {
    this->matches = value.get("matches", "").asInt();
    this->accounts = value.get("accounts", "").asInt();
}

string MatchCount::primaryKeyValue() {
    return id;
}

string MatchCount::getName() {
    return "matchCount/";
}


void MatchCount::addMatch() {
    this->matches++;

}

void MatchCount::addAccount() {
    this->accounts++;
}

int MatchCount::getMatches() const {
    return matches;
}

int MatchCount::getAccounts() const {
    return accounts;
}

void MatchCount::setId(const string &id) {
    MatchCount::id = id;
}

MatchCount::~MatchCount() {

}

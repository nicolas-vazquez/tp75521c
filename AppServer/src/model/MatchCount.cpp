#include "MatchCount.h"

MatchCount::MatchCount() {

}

Value MatchCount::toJSON() {
    Value value;
    value["matches"] = matches;
    value["accounts"] = accounts;
    return value;
}

void MatchCount::fromJSON(Value value) {
    this->matches = value.get("matches", "").asUInt();
    this->accounts = value.get("accounts", "").asUInt();
}

string MatchCount::primaryKeyValue() {
    return "";
}

string MatchCount::getName() {
    return "matchCount/";
}

MatchCount::~MatchCount() {

}

void MatchCount::addMatch() {
    this->matches++;

}

void MatchCount::addAccount() {
    this->accounts++;
}

#include "Chat.h"

Chat::Chat(const string &id) {
    this->messages.empty();
    this->id = id;
}

Value Chat::toJSON() {
    Value value;
    string s1;
    value["messages"] = utils::serializeArray(this->messages, s1);
    return value;
}

void Chat::fromJSON(Value value) {
    this->messages.clear();
    utils::deserializeArray(value.get("messages", "").asString(), this->messages);
}

void Chat::setUser(const string &sender) {
    this->sender = sender;
}

void Chat::update(const string &message) {
    //TODO Store new date in the message
    Value value;
    value["sender"] = this->sender;
    value["message"] = message;
    this->messages.push_back(value.toStyledString());
}

const vector<string> &Chat::getMessages() const {
    return this->messages;
}

string Chat::primaryKeyValue() {
    return this->id;
}

string Chat::getName() {
    return "conversation/";
}

Chat::~Chat() {
    this->messages.clear();
}

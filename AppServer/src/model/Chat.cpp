#include "Chat.h"

Chat::Chat(const string &id) {
    this->messages = "";
    this->id = id;
}

Chat::Chat(const string &u1, const string &u2) {
    if (u1.compare(u2) < 0) {
        this->id = u1 + ',' + u2;
    } else {
        this->id = u2 + ',' + u1;
    }
}

Value Chat::toJSON() {
    Value value;
    value["messages"] = this->messages;
    return value;
}

void Chat::fromJSON(Value value) {
    this->messages = value.get("messages", "").asString();
}

void Chat::setUser(const string &sender) {
    this->sender = sender;
}

void Chat::update(const string &message) {
    time_t now = time(0);
    char* dt = ctime(&now);
    Value value;
    value["time"] = dt;
    value["sender"] = this->sender;
    value["message"] = message;
    this->messages.append(value.asString());
}

const string &Chat::getMessages() const {
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

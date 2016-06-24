#include "Chat.h"

Chat::Chat() {

}

Chat::Chat(const string &id) {
    this->id = id;
}

Chat::Chat(const string &u1, const string &u2) {
    if (u1.compare(u2) < 0) {
        this->id = u1 + '+' + u2;
    } else {
        this->id = u2 + '+' + u1;
    }
}

Value Chat::toJSON() {
    Value value;
    value["messages"] = this->messages;
    return value;
}

void Chat::fromJSON(Value value) {
    this->messages = value.get("messages", "");
    if (this->messages.isNull()) {
        Json::Value jsonArray;
        jsonArray.append(Json::Value::null);
        jsonArray.clear();
        this->messages = jsonArray;
    }
}

void Chat::setUser(const string &sender) {
    this->sender = sender;
}

const string &Chat::getId() const {
    return this->id;
}

void Chat::update(Value &value) {
    time_t now = time(0);
    char *dt = ctime(&now);
    value["time"] = dt;
    value["sender"] = this->sender;
    this->messages.append(value);
}

const Value &Chat::getMessages() const {
    return this->messages;
}

string Chat::primaryKeyValue() {
    return this->id;
}

string Chat::getName() {
    return "conversation/";
}

Chat::~Chat() {
}

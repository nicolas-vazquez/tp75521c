#ifndef APPSERVER_CONVERSATION_H
#define APPSERVER_CONVERSATION_H

#include <ctime>
#include "Entity.h"
#include <utils/utils.h>

class Chat : public Entity {

private:
    string id;
    string sender;
    Value messages;

public:
    Chat();

    Chat(const string& id);

    Chat(const string& u1, const string& u2);

    const string &getId() const;

    void setUser(const string &sender);

    const Value& getMessages() const;

    virtual Value toJSON() override;

    virtual ~Chat();

    void update(Value &message);

protected:

    virtual void fromJSON(Value value) override;

    virtual string primaryKeyValue() override;

    virtual string getName() override;

};

#endif //APPSERVER_CONVERSATION_H

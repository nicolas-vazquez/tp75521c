#ifndef APPSERVER_CONVERSATION_H
#define APPSERVER_CONVERSATION_H

#include <ctime>
#include "Entity.h"
#include <utils/utils.h>

class Chat : public Entity {

private:
    string id;
    string sender;
    string messages;

public:
    Chat(const string& id);

    Chat(const string& u1, const string& u2);

    void setUser(const string &sender);

    void update(const string &message);

    const string& getMessages() const;

    virtual Value toJSON() override;

    virtual ~Chat();

protected:

    virtual void fromJSON(Value value) override;

    virtual string primaryKeyValue() override;

    virtual string getName() override;

};

#endif //APPSERVER_CONVERSATION_H

//
// Created by fede on 4/3/16.
//

#ifndef APPSERVER_USER_H
#define APPSERVER_USER_H


#include "Entity.h"

class User : public Entity {

private:
    string username;
    string password;

public:

protected:

    virtual void fromJSON(Value value) override;

    virtual string primaryKeyValue() override;

    virtual Value toJSON() override;

    virtual string getName() override;

    void setPassword(const string &password);

    const string &getPassword() const;

    void setUsername(const string &username);

    const string &getUsername() const;
};


#endif //APPSERVER_USER_H

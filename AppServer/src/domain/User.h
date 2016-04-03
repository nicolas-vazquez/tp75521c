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

public:
    User(const string &username);

    const string &getUsername() const;

    const string &getPassword() const;

    virtual Value toJSON() override;

    void setPassword(const string &password);

    virtual ~User();

protected:

    virtual void fromJSON(Value value) override;

    virtual string primaryKeyValue() override;

    virtual string getName() override;

};


#endif //APPSERVER_USER_H

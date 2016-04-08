//
// Created by fedefarina on 07/04/16.
//

#ifndef APPSERVER_TOKEN_H
#define APPSERVER_TOKEN_H


#include "Entity.h"


class Token : public Entity {

private:
    string token;
    string username;

public:

    Token();

    const string &getToken() const;

    void setToken(const string &token);

    const string &getUsername() const;

    void setUsername(const string &username);

    string primaryKeyValue() override;

    virtual ~Token();

protected:

    virtual Value toJSON() override;

    virtual void fromJSON(Value value) override;

    virtual string getName() override;
};


#endif //APPSERVER_TOKEN_H

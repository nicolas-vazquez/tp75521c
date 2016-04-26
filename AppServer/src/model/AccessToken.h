//
// Created by fedefarina on 07/04/16.
//

#ifndef APPSERVER_TOKEN_H
#define APPSERVER_TOKEN_H

#include "Entity.h"

class AccessToken : public Entity {

private:
    string _id;
    string token;

public:

    AccessToken();

    const string &getToken() const;

    void setToken(const string &token);

    const string &getUserId() const;

    void setUserId(const string &username);

    string primaryKeyValue() override;

    virtual ~AccessToken();

protected:

    virtual Value toJSON() override;

    virtual void fromJSON(Value value) override;

    virtual string getName() override;
};


#endif //APPSERVER_TOKEN_H

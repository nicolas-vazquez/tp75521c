//
// Created by fede on 4/3/16.
//

#ifndef APPSERVER_USER_H
#define APPSERVER_USER_H

#include "Entity.h"

class Account : public Entity {

private:
    string username;
    string password;

    vector<string> keptAccounts;
    vector<string> tossedAccounts;

public:
    Account(const string &username);

    const string &getUsername() const;

    const string &getPassword() const;

    virtual Value toJSON() override;

    void setPassword(const string &password);

    void addKeepAccount(const string &keptAccount);

    void addTossAccount(const string &tossedAccount);

    virtual ~Account();

protected:

    virtual void fromJSON(Value value) override;

    virtual string primaryKeyValue() override;

    virtual string getName() override;

};


#endif //APPSERVER_USER_H

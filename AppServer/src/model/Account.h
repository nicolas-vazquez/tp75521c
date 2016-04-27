//
// Created by fede on 4/3/16.
//

#ifndef APPSERVER_USER_H
#define APPSERVER_USER_H

#include "Entity.h"
#include "../utils/Utils.h"

class Account : public Entity {

private:
    string userId;
    string username;
    string password;

    vector<string> keptAccounts;
    vector<string> tossedAccounts;

public:
    Account();

    Account(const string &username);

    void setUsername(const string &username);

    const string &getUsername() const;

    const string &getPassword() const;

    const string &getUserId() const;

    virtual Value toJSON() override;

    void setUserId(const string &id);

    void setPassword(const string &password);

    const vector<string> & getKeptAccounts() const;

    const vector<string> & getTossedAccounts() const;

    void addKeepAccount(const string &keptAccount);

    void addTossAccount(const string &tossedAccount);

    virtual ~Account();

protected:

    virtual void fromJSON(Value value) override;

    virtual string primaryKeyValue() override;

    virtual string getName() override;
};


#endif //APPSERVER_USER_H

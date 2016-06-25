#ifndef APPSERVER_MATCHCOUNT_H
#define APPSERVER_MATCHCOUNT_H

#include "Entity.h"

class MatchCount : public Entity {

private:

    int matches;
    int accounts;
    string id = "id";

public:

    MatchCount();

    void addMatch();

    void addAccount();

    int getMatches() const;

    int getAccounts() const;

    void setId(const string &id);

    virtual Value toJSON() override;

    virtual ~MatchCount();

protected:

    virtual void fromJSON(Value value) override;

    virtual string primaryKeyValue() override;

    virtual string getName() override;

};


#endif //APPSERVER_MATCHCOUNT_H

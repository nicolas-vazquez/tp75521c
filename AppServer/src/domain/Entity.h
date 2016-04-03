//
// Created by fede on 4/3/16.
//

#ifndef APPSERVER_ENTITY_H
#define APPSERVER_ENTITY_H


#include <json/json.h>
#include "rocksdb/db.h"

using namespace std;
using namespace Json;
using namespace rocksdb;

class Entity {

    DB *db;
    string id;

public:
    Entity();

    void fetch();

    bool save();

    virtual Value toJSON() = 0;

    virtual void fromJSON() = 0;

    /**
     * Works as key prefix in key,value rocksdb usage.
     */
    virtual string getName() = 0;

    virtual ~Entity();
};


#endif //APPSERVER_ENTITY_H

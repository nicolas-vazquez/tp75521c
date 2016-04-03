//
// Created by fede on 4/3/16.
//

#ifndef APPSERVER_ENTITY_H
#define APPSERVER_ENTITY_H


#include <json/json.h>

using namespace Json;

class Entity {

public:
    Entity();

    void fetch();

    void save();

    virtual Value toJSON() = 0;

    virtual void fromJSON() = 0;

    virtual ~Entity();
};


#endif //APPSERVER_ENTITY_H

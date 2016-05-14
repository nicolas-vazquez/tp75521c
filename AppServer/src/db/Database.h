//
// Created by federicofarina on 4/20/16.
//

#ifndef APPSERVER_DATABASE_H
#define APPSERVER_DATABASE_H

#include "rocksdb/db.h"

using namespace rocksdb;

class Database {

private:
    DB *db;

public:

    static Database  &getInstance();

    Database(Database const &) = delete;             // Copy construct
    Database(Database &&) = delete;                  // Move construct
    Database &operator=(Database const &) = delete;  // Copy assign
    Database &operator=(Database &&) = delete;      // Move assign
    DB *getDb() const;

protected:

protected:
    Database();

    virtual ~Database();
};


#endif //APPSERVER_DATABASE_H

//
// Created by fede on 4/3/16.
//

#include "Entity.h"

std::string DBPath = "/tmp/appServerDB";

Entity::Entity() {
    Options options;
    // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();
    // create the DB if it's not already present
    options.create_if_missing = true;

    Status s = DB::Open(options, DBPath, &db);
    assert(s.ok());
}

bool Entity::fetch() {
    string value;
    Status s = db->Get(ReadOptions(), getName() + primaryKeyValue(), &value);
    return s.ok();
}

bool Entity::save() {
    Status s = db->Put(WriteOptions(), getName() + primaryKeyValue(), toJSON().toStyledString());
    return s.ok();
}

Entity::~Entity() {
    delete db;
}
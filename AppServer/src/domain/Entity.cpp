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

void Entity::fetch() {

}

bool Entity::save() {
    Status s = db->Put(WriteOptions(), getName() + id, toJSON().toStyledString());
    return s.ok();
}

Entity::~Entity() {
    delete db;
}
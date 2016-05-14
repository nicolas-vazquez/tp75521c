//
// Created by federicofarina on 4/20/16.
//

#include "Database.h"

std::string DBPath = "/tmp/appServerDB";

Database & Database::getInstance() {
    // Since it's a static variable, if the class has already been created,
    // It won't be created again.
    // And it **is** thread-safe in C++11.
    static Database instance;
    return instance;
}

Database::Database() {
    Options options;
    // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
    options.IncreaseParallelism();
    options.OptimizeLevelStyleCompaction();
    // create the DB if it's not already present
    options.create_if_missing = true;
    Status s = DB::Open(options, DBPath, &this->db);
    assert(s.ok());
}

DB *Database::getDb() const {
    return db;
}

Database::~Database() {
    delete (db);
}





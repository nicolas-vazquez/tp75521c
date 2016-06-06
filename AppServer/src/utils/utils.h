#ifndef APPSERVER_UTILS_H
#define APPSERVER_UTILS_H

#include "vector"
#include "iostream"
#include "string.h"
using namespace std;

class utils {
public:
    static string &serializeArray(vector<string> &array, string &result);
    static void deserializeArray(string source, vector<string> &array);
    static bool findValueInArray(vector<string> &array, string &value);
};


#endif //APPSERVER_UTILS_H

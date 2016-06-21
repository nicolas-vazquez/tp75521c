#include "utils.h"

string& utils::serializeArray(vector<string> &array, string &result) {
    for (unsigned int i = 0; i < array.size(); i++) {
        result.append(array[i] + ",");
    }
    return result;
}

void utils::deserializeArray(string source, vector<string> &array) {
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = source.find(delimiter)) != std::string::npos) {
        token = source.substr(0, pos);
        array.push_back(token);
        source.erase(0, pos + delimiter.length());
    }
}

bool utils::findValueInArray(vector<string> &array, string &value) {
    for (std::vector<string>::iterator it = array.begin(); it != array.end(); ++it) {
        if (*it == value) {
            return 1;
        }
    }
    return 0;
}

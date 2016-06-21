#ifndef APPSERVER_RESOURCENOTFOUND_H
#define APPSERVER_RESOURCENOTFOUND_H

#include "Error.h"

class ResourceNotFoundError : public Error {

public:
    ResourceNotFoundError() {
        this->message = "Resource not found";
    }

    virtual int getCode() {
        return 1;
    }


    virtual ~ResourceNotFoundError() {

    }
};

#endif //APPSERVER_RESOURCENOTFOUND_H

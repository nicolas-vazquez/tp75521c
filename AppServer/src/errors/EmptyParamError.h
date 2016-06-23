//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_EMPTYPARAMERROR_H
#define APPSERVER_EMPTYPARAMERROR_H


#include "Error.h"

class EmptyParamError : public Error {

public:

    EmptyParamError() { }

    virtual int getCode() {
        return 2;
    }

    virtual ~EmptyParamError() { }
};


#endif //APPSERVER_EMPTYPARAMERROR_H

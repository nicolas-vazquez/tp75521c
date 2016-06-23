//
// Created by fedefarina on 26/03/16.
//

#ifndef APPSERVER_BADPARAMERROR_H
#define APPSERVER_BADPARAMERROR_H

#include "Error.h"

class BadParamError : public Error {

public:

    BadParamError() { }

    virtual int getCode() {
        return 7;
    }

    virtual ~BadParamError() { }
};


#endif //APPSERVER_BADPARAMERROR_H

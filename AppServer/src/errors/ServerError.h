//
// Created by fedefarina on 25/05/16.
//

#ifndef APPSERVER_SERVERERROR_H
#define APPSERVER_SERVERERROR_H

class ServerError : public Error {

public:
    ServerError() {
        this->message = "Server error";
    }

    virtual int getCode() {
        return 6;
    }

    virtual ~ServerError() {

    }
};

#endif //APPSERVER_SERVERERROR_H

#ifndef _MONGOOSE_REQUEST_HANDLER_H
#define _MONGOOSE_REQUEST_HANDLER_H

#include "Request.h"
#include "Response.h"
#include "StreamResponse.h"
#include <string>

namespace Mongoose {

    class RequestHandlerBase {
    public:
        virtual Response *process(Request &request) = 0;
    };

    template<typename BaseController, typename JsonResponse>
    class RequestHandler : public RequestHandlerBase {
    public:
        typedef void (BaseController::*fPtr)(Request &request, JsonResponse &response);

        RequestHandler(BaseController *controller_, fPtr function_)
                : controller(controller_), function(function_) {

        }

        Response *process(Request &request) {
            JsonResponse *response = new JsonResponse;

            try {

                if (controller->requireAuthentication(request.getMethod(), request.getUrl())) {
                    bool validToken = controller->tokenAuthenticate(request);
                    if (!validToken) {
                        return &controller->sendUnauthorizedResponse(*response);
                    }
                }

                controller->preProcess(request, *response);
                (controller->*function)(request, *response);
            } catch (string exception) {
                return controller->serverInternalError(exception);
            } catch (...) {
                return controller->serverInternalError("Unknown error");
            }

            return response;
        }

    protected:
        BaseController *controller;
        fPtr function;
    };
}

#endif

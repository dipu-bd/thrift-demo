#pragma once

#include "Service.h"

#include "./errors.hpp"

using namespace demo::rpc::service;
using namespace demo::rpc::shared;

// ------------------------------------------------------------------------- //

inline void __throw_error(int code, const std::string &msg)
{
    printf("[service] code %d: %s\n", code, msg.c_str());
    ServiceError ex;
    ex.code = code;
    ex.message = msg;
    throw ex;
}

// ------------------------------------------------------------------------- //

class ServiceHandler : public ServiceIf
{
public:
    ~ServiceHandler()
    {
        printf("[service] cleaning ServiceHandler\n");
    }

    bool ping()
    {
        printf("[service] ping received\n");
        return true;
    }

    void sayHello(SayHelloResponse &response, const SayHelloRequest &request)
    {
        printf("[service] sayHello received: %s\n", request.name.c_str());

        if (request.name.size() == 0)
        {
            __throw_error(ERR_EMPTY_ARGUMENT, "Name should not be empty");
        }

        response.message = "Hello " + request.name;
        printf("[service] sayHello response: %s\n", response.message.c_str());
    }
};

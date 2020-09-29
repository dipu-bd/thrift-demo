#include <stdio.h>
#include <assert.h>
#include <getopt.h>

#include <thrift/server/TSimpleServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "./headers/errors.hpp"
#include "./headers/service_handler.hpp"

namespace ats = apache::thrift::server;
namespace atp = apache::thrift::protocol;
namespace att = apache::thrift::transport;

// --------------------------------------------------------------------------------------------- //

int port = 6565;
const char *host = "0.0.0.0";

void read_arguments(int argc, char **argv)
{
    for (int opt; (opt = getopt(argc, argv, "p:h:")) != -1;)
    {
        if ('p' == opt)
        {
            port = atoi(optarg);
        }
        else if ('h' == opt)
        {
            host = optarg;
        }
    }
    if (port <= 0)
    {
        fprintf(stderr, "Error: A valid port is required.\n");
        fprintf(stderr, "USAGE:\n server [-p PORT] [-h HOST]\n");
        exit(ERR_INVALID_ARGUMENTS);
    }
}

int main(int argc, char **argv)
{
    // Read server arguments
    read_arguments(argc, argv);

    // Create a thrift server
    ats::TSimpleServer server(
        std::make_shared<ServiceProcessor>(std::make_shared<ServiceHandler>()),
        std::make_shared<att::TServerSocket>(host, port),   /* create a simple server socket */
        std::make_shared<att::TBufferedTransportFactory>(), /* use buffered transport */
        std::make_shared<atp::TBinaryProtocolFactory>()     /* pass data as binary */
    );

    // Start the server
    printf("Starting server on %s:%d\n", host, port);
    server.serve();
    printf("Server stopped\n");

    exit(ERR_NONE);
}

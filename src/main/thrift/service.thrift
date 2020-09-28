/*
 * Service related structures
 */

namespace cpp demo.rpc.service
namespace java com.demo.rpc.service

include 'shared.thrift'

/*
 * Service
 */
service Service {
    bool ping()
    SayHelloResponse sayHello(1: SayHelloRequest request) throws (1: shared.ServiceError ex)
}

struct SayHelloRequest {
    1: string name
}
struct SayHelloResponse {
    1: string message
}

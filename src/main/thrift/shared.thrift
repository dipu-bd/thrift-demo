/*
 * Shared structures between services
 */

namespace cpp demo.rpc.shared
namespace java com.demo.rpc.shared

/*
 * The exception thrown on service failure
 */
exception ServiceError {
    1: i32 code = -1    // error code
    2: string message   // error message
}

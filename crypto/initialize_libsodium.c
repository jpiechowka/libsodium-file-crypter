#include <sodium.h>
#include "../utils/logger.h"

void initialize_libsodium() {
    log_debug("Trying to initialize libsodium library, calling sodium_init() function");
    int sodiumInitReturnVal = sodium_init();
    if (sodiumInitReturnVal < 0) {
        log_error("libsodium couldn't be initialized with sodium_init(), it is not safe to use.");
        log_error("Quitting!");
        exit(0xDEAD);
    } else if (sodiumInitReturnVal == 1) {
        log_debug("sodium_init() function returned 1, libsodium has been already initialized");
    } else {
        log_debug("libsodium successfully initialized");
    }
}

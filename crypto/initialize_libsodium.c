#include "../utils/logger.h"
#include <sodium.h>

void initialize_libsodium() {
    log_info("Trying to initialize libsodium library");
    if (sodium_init() < 0) {
        log_error("libsodium couldn't be initialized with sodium_init(), it is not safe to use.");
        log_error("Quitting!");
        exit(0xDEAD);
    } else {
        log_info("libsodium successfully initialized");
    }
}
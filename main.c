#include <argp.h>
#include "crypto/initialize_libsodium.h"
#include "utils/logger.h"

static int handle_parsed_option(int key, char *arg, struct argp_state *state) {
    switch (key) {
        case 'v':
            log_info("Enabling DEBUG logging");
            toggle_debug_logging(true);
            break;
        default:
            break;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    //Try to initialize libsodium before doing anything else. If this fails the program will exit.
    initialize_libsodium();

    struct argp_option argpParsingOptions[] = {
            {"verbose", 'v', 0, 0,            "Increase verbosity - show debug messages"},
            {"debug",   0,   0, OPTION_ALIAS, 0},
            {0}
    };

    struct argp argpStruct = {argpParsingOptions, handle_parsed_option};

    return argp_parse(&argpStruct, argc, argv, 0, 0, 0);
}

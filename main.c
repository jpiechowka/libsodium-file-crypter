#include <argp.h>
#include <error.h>
#include "crypto/decrypt_file.h"
#include "utils/logger.h"
#include "crypto/encrypt_file.h"

#define DEFAULT_OUTPUT_FILE "output.crypt"

/* Parsing command line arguments using argp. Code based on this examples:
 * http://www.gnu.org/software/libc/manual/html_node/Argp-Example-3.html
 * http://www.gnu.org/software/libc/manual/html_node/Argp-Example-4.html */

const char *argp_program_version = "libsodium-file-crypter version 1.0.0";
const char *argp_program_bug_address = "https://github.com/jpiechowka/libsodium-file-crypter/issues";

unsigned char crypto_key[crypto_secretstream_xchacha20poly1305_KEYBYTES];

// Program documentation
static char doc[] = "A file encryption utility written in C using libsodium";

// A description of the arguments we accept
static char args_doc[] = "FILE PASSWORD";

// The options we understand
static struct argp_option options[] = {
        {"verbose", 'v', 0,      0,       "Increase verbosity - show debug messages"},
        {"debug",   0,   0, OPTION_ALIAS, 0},
        {"output",  'o', "FILE", 0,       "Specify output file instead of default: output.crypt"},
        {"encrypt", 'e', 0,      0,       "Encrypt the specified file. Specifying operation mode is mandatory for program to run"},
        {"decrypt", 'd', 0,      0,       "Decrypt the specified file. Specifying operation mode is mandatory for program to run"},
        {0}
};

// Used by main to communicate with parse_opt
struct arguments {
    char *args[2]; /* FILE & PASSWORD */
    bool verbose;
    int operationMode; /* 1 for encryption, 2 for decryption, other values treated as invalid */
    char *outputFile;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    /* Get the input argument from argp_parse, which we know is a pointer to our arguments structure */
    struct arguments *arguments = state->input;

    switch (key) {
        case 'v':
            arguments->verbose = true;
            break;
        case 'o':
            arguments->outputFile = arg;
            break;
        case 'd':
            arguments->operationMode = 2;
            break;
        case 'e':
            arguments->operationMode = 1;
            break;
        case ARGP_KEY_ARG: {
            if (state->arg_num >= 2)
                /* Too many arguments. */
                argp_usage(state);
            arguments->args[state->arg_num] = arg;
            break;
        }
        case ARGP_KEY_END: {
            if (state->arg_num < 2)
                /* Not enough arguments. */
                argp_usage(state);
            break;
        }
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// Our argp parser
static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char *argv[]) {
    struct arguments arguments;

    /* Default values */
    arguments.verbose = false;
    arguments.operationMode = -1; /* Default is not specified. User needs to provide this value */
    arguments.outputFile = DEFAULT_OUTPUT_FILE;

    /* Parse our arguments; every option seen by parse_opt will be reflected in arguments */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.verbose == true) {
        toggle_debug_logging(true);
    }

    /* arguments.args[0] - FILE
     * arguments.args[1] - PASSWORD*/

    if (arguments.operationMode == 1) {
        // Encrypt
        encrypt_file(arguments.args[0], arguments.outputFile, arguments.args[1]);
    } else if (arguments.operationMode == 2) {
        //Decrypt
        decrypt_file(arguments.args[0], arguments.outputFile, arguments.args[1]);
    } else {
        log_error("No operation mode provided. Make sure to use [-d] or [-e] options to specify operation mode");
        return 1;
    }

    return 0;
}

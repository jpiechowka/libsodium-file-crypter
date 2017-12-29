#ifndef LIBSODIUM_FILE_CRYPTER_LOGGER_H
#define LIBSODIUM_FILE_CRYPTER_LOGGER_H

#include <stdbool.h>

//Colors used when printing text to console
#define RED "\x1B[31m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET_COLOR "\x1B[0m"

void toggle_debug_logging(bool shouldDebugLoggingBeEnabled);

void log_debug(char *debugMessage);

void log_info(char *infoMessage);

void log_warning(char *warningMessage);

void log_error(char *errorMessage);

#endif //LIBSODIUM_FILE_CRYPTER_LOGGER_H

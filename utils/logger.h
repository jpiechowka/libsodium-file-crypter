#ifndef LIBSODIUM_FILE_CRYPTER_LOGGER_H
#define LIBSODIUM_FILE_CRYPTER_LOGGER_H

#include <stdbool.h>

#define CONCAT_STR_BUFFER_LEN 4096

//Colors used when printing text to console
#define RED "\x1B[31m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET_COLOR "\x1B[0m"

void toggle_debug_logging(bool shouldDebugLoggingBeEnabled);

void log_debug(const char *debugMessage);

void log_debug_concat_str(const char *debugMessage, const char *stringToConcatenate);

void log_info(const char *infoMessage);

void log_info_concat_str(const char *infoMessage, const char *stringToConcatenate);

void log_warning(const char *warningMessage);

void log_warning_concat_str(const char *warningMessage, const char *stringToConcatenate);

void log_error(const char *errorMessage);

void log_error_concat_str(const char *errorMessage, const char *stringToConcatenate);

#endif //LIBSODIUM_FILE_CRYPTER_LOGGER_H

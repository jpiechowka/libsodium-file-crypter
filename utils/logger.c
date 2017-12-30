#include <stdio.h>
#include <time.h>
#include <string.h>
#include "logger.h"

struct LoggerOptions {
    bool showDebugMessages;
};

struct LoggerOptions loggerOptions = {.showDebugMessages = false};

void toggle_debug_logging(bool shouldDebugLoggingBeEnabled) {
    log_info("Enabling DEBUG logging");
    loggerOptions.showDebugMessages = shouldDebugLoggingBeEnabled;
};

void log_debug(const char *debugMessage) {
    // Check if debug logging is enabled
    if (loggerOptions.showDebugMessages) {
        time_t now;
        time(&now);
        char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
        printf(BLUE "[DEBUG][%s] %s\n" RESET_COLOR, ctimeNoNewline, debugMessage);
    }
}

void log_debug_concat_str(const char *debugMessage, const char *stringToConcatenate) {
    char concatenatedLog[CONCAT_STR_BUFFER_LEN];
    strncpy(concatenatedLog, debugMessage, sizeof(concatenatedLog));
    strncat(concatenatedLog, stringToConcatenate, sizeof(concatenatedLog));

    // Check if debug logging is enabled
    if (loggerOptions.showDebugMessages) {
        time_t now;
        time(&now);
        char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
        printf(BLUE "[DEBUG][%s] %s\n" RESET_COLOR, ctimeNoNewline, concatenatedLog);
    }
}

void log_info(const char *infoMessage) {
    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n");
    printf("[ INFO][%s] %s\n", ctimeNoNewline, infoMessage);
}

void log_info_concat_str(const char *infoMessage, const char *stringToConcatenate) {
    char concatenatedLog[CONCAT_STR_BUFFER_LEN];
    strncpy(concatenatedLog, infoMessage, sizeof(concatenatedLog));
    strncat(concatenatedLog, stringToConcatenate, sizeof(concatenatedLog));

    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
    printf("[ INFO][%s] %s\n", ctimeNoNewline, concatenatedLog);
}

void log_warning(const char *warningMessage) {
    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
    printf(YELLOW "[ WARN][%s] %s\n" RESET_COLOR, ctimeNoNewline, warningMessage);
}

void log_warning_concat_str(const char *warningMessage, const char *stringToConcatenate) {
    char concatenatedLog[CONCAT_STR_BUFFER_LEN];
    strncpy(concatenatedLog, warningMessage, sizeof(concatenatedLog));
    strncat(concatenatedLog, stringToConcatenate, sizeof(concatenatedLog));

    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
    printf(YELLOW "[ WARN][%s] %s\n" RESET_COLOR, ctimeNoNewline, concatenatedLog);
}

void log_error(const char *errorMessage) {
    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
    printf(RED "[ERROR][%s] %s\n" RESET_COLOR, ctimeNoNewline, errorMessage);
}

void log_error_concat_str(const char *errorMessage, const char *stringToConcatenate) {
    char concatenatedLog[CONCAT_STR_BUFFER_LEN];
    strncpy(concatenatedLog, errorMessage, sizeof(concatenatedLog));
    strncat(concatenatedLog, stringToConcatenate, sizeof(concatenatedLog));

    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
    printf(RED "[ERROR][%s] %s\n" RESET_COLOR, ctimeNoNewline, concatenatedLog);
}
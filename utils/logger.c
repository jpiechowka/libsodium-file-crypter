#include <stdio.h>
#include <time.h>
#include <string.h>
#include "logger.h"

void log_debug(char *debugMessage) {
    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n"); // Delete newline, so that the log message is not split
    printf(BLUE "[DEBUG][%s] %s\n" RESET_COLOR, ctimeNoNewline, debugMessage);
}

void log_info(char *infoMessage) {
    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n");
    printf("[ INFO][%s] %s\n", ctimeNoNewline, infoMessage);
}

void log_warning(char *warningMessage) {
    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n");
    printf(YELLOW "[ WARN][%s] %s\n" RESET_COLOR, ctimeNoNewline, warningMessage);
}

void log_error(char *errorMessage) {
    time_t now;
    time(&now);
    char *ctimeNoNewline = strtok(ctime(&now), "\n");
    printf(RED "[ERROR][%s] %s\n" RESET_COLOR, ctimeNoNewline, errorMessage);
}
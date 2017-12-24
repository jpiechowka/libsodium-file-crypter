#include <stdio.h>
#include "logger.h"

void log_debug(char *debugMessage) {
    printf(BLUE "[DEBUG] %s\n" RESET_COLOR, debugMessage);
}

void log_info(char *infoMessage) {
    printf("[INFO] %s\n", infoMessage);
}

void log_warning(char *warningMessage) {
    printf(YELLOW "[WARN] %s\n" RESET_COLOR, warningMessage);
}

void log_error(char *errorMessage) {
    printf(RED "[ERROR] %s\n" RESET_COLOR, errorMessage);
}
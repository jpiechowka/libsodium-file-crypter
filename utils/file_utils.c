#include <unistd.h>
#include "file_utils.h"
#include "logger.h"

bool check_if_file_exists(const char *filePath) {
    if (access(filePath, F_OK) != -1) {
        // File exists
        log_debug_concat_str(filePath, " file exists");
        return true;
    } else {
        // File doesn't exist
        log_error_concat_str(filePath, " file does not exists");
        return false;
    }
}

bool check_if_file_is_readable(const char *filePath) {
    if (access(filePath, R_OK) != -1) {
        // File readable
        log_debug_concat_str(filePath, " file is readable");
        return true;
    } else {
        // File is not readable
        log_error_concat_str(filePath, " file is not readable");
        return false;
    }
}

bool check_if_file_is_writable(const char *filePath) {
    if (access(filePath, W_OK) != -1) {
        // File is writable
        log_debug_concat_str(filePath, " file is writable");
        return true;
    } else {
        // File is not writable
        log_error_concat_str(filePath, " file is not writable");
        return false;
    }
}



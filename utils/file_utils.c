#include <unistd.h>
#include "file_utils.h"

bool check_if_file_exists(const char *filePath) {
    if (access(filePath, F_OK) != -1) {
        // File exists
        return true;
    } else {
        // File doesn't exist
        return false;
    }
}

bool check_if_file_is_readable(const char *filePath) {
    if (access(filePath, R_OK) != -1) {
        // File readable
        return true;
    } else {
        // File is not readable
        return false;
    }
}

bool check_if_file_is_writable(const char *filePath) {
    if (access(filePath, W_OK) != -1) {
        // File is writable
        return true;
    } else {
        // File is not writable
        return false;
    }
}



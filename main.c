#include "utils/logger.h"

int main() {
    log_debug("debug message");
    log_info("info message");
    log_warning("warning message");
    log_error("error message");
    return 0;
}
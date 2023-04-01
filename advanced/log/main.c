#include "log.h"

int main() {
    set_log_flags(LOG_FLAG_ALL);
    set_log_time_format("%H:%M:%S");
    set_log_file(stdout);

    log_debug("This is a debug message\n");
    log_info("This is an info message\n");
    log_warn("This is a warning message\n");
    log_error("This is an error message\n");
}
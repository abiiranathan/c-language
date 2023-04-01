#include "log.h"
char LOG_TIME_FORMAT[] = "%Y-%m-%d %H:%M:%S";
FILE *log_file = NULL;

/**
 * @brief Set the log time format object
 *
 * @param format
 */
void set_log_time_format(char *format) {
    if (format) {
        strncpy(LOG_TIME_FORMAT, format, 17);
        LOG_TIME_FORMAT[17] = '\0';
    } else {
        LOG_TIME_FORMAT[0] = '\0';
    }
}

/**
 * @brief Set the log level object
 *
 * @param level
 */
void set_log_level(int level) {
    log_level = level;
}

/**
 * @brief Set the log flags object
 *
 * @param flags
 */
void set_log_flags(int flags) {
    log_flags = flags;
}

/**
 * @brief Set the log file object
 *
 * @param file
 */
void set_log_file(FILE *file) {
    log_file = file;
}

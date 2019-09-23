#include <stdio.h>
#include <sck_core.h>

/* LOG DEBUG */
int sck_log_debug(const char * message) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_DEBUG)) {
        printf("[DEBUG] %s", message);
        return 0;
    }
    return 1;
}

/* LOG WARNING */
int sck_log_warning(const char * message) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_WARNING)) {
        printf("[WARNING] %s", message);
        return 0;
    }
    return 1;
}

/* LOG ERROR */
int sck_log_error(const char * message) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_ERROR)) {
        printf("[ERROR] %s", message);
        return 0;
    }
    return 1;
}

/* LOG CRITICAL */
int sck_log_critical(const char * message) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_CRITICAL)) {
        printf("[CRITICAL] %s", message);
        return 0;
    }
    return 1;
}
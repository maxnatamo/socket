#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sck_core.h>

/* LOG DEBUG */
int sck_log_debug(const char * fmt, ...) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_DEBUG)) {
        char *buffer = malloc(sizeof(char) * 0);
        int len;
        va_list vl;
        
        va_start(vl, fmt);
        len = vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        buffer = realloc(buffer, sizeof(char) * len);
        va_start(vl, fmt);
        vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        printf("[DEBUG] %s", buffer);
        return 0;
    }
    return 1;
}

/* LOG WARNING */
int sck_log_warning(const char * fmt, ...) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_WARNING)) {
        char *buffer = malloc(sizeof(char) * 0);
        int len;
        va_list vl;
        
        va_start(vl, fmt);
        len = vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        buffer = realloc(buffer, sizeof(char) * len);
        va_start(vl, fmt);
        vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        printf("[WARNING] %s", buffer);
        return 0;
    }
    return 1;
}

/* LOG ERROR */
int sck_log_error(const char * fmt, ...) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_ERROR)) {
        char *buffer = malloc(sizeof(char) * 0);
        int len;
        va_list vl;
        
        va_start(vl, fmt);
        len = vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        buffer = realloc(buffer, sizeof(char) * len);
        va_start(vl, fmt);
        vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        printf("[ERROR] %s", buffer);
        return 0;
    }
    return 1;
}

/* LOG CRITICAL */
int sck_log_critical(const char * fmt, ...) {
    if((SCK_LOG_LEVEL & SCK_LOG_LEVEL_CRITICAL)) {
        char *buffer = malloc(sizeof(char) * 0);
        int len;
        va_list vl;
        
        va_start(vl, fmt);
        len = vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        buffer = realloc(buffer, sizeof(char) * len);
        va_start(vl, fmt);
        vsnprintf( buffer, sizeof(buffer), fmt, vl);
        va_end(vl);

        printf("[CRITICAL] %s", buffer);
        return 0;
    }
    return 1;
}
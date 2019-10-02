#ifndef SCK_LOG_H
#define SCK_LOG_H

/*
 * Default return values.
 */
#define SCK_OK                          0
#define SCK_ERROR                      -1
#define SCK_INVALID_PARAMETERS         -2
#define SCK_CALL_DECLINED              -3
#define SCK_CALL_ABORTED               -4
#define SCK_MEMORY_ERROR               -5
#define SCK_FILE_NOT_FOUND             -6

/*
 * Log-level bitwise values.
 */
#define SCK_LOG_LEVEL_DEBUG             0b0001 /* 0001 */
#define SCK_LOG_LEVEL_WARNING           0b0010 /* 0010 */
#define SCK_LOG_LEVEL_ERROR             0b0100 /* 0100 */
#define SCK_LOG_LEVEL_CRITICAL          0b1000 /* 1000 */

/*
 * Print message to DEBUG-log.
 * Only displays in console,
 * if the SCK_LOG_LEVEL includes SCK_LOG_LEVEL_DEBUG.
 * Accepts string formatting like printf().
 * 
 * Returns: 1 on console print, 0 otherwise.
 */
int sck_log_debug    (const char *, ...);

/*
 * Print message to WARNING-log.
 * Only displays in console,
 * if the SCK_LOG_LEVEL includes SCK_LOG_LEVEL_WARNING.
 * Accepts string formatting like printf().
 * 
 * Returns: 1 on console print, 0 otherwise.
 */
int sck_log_warning  (const char *, ...);

/*
 * Print message to ERROR-log.
 * Only displays in console,
 * if the SCK_LOG_LEVEL includes SCK_LOG_LEVEL_ERROR.
 * Accepts string formatting like printf().
 * 
 * Returns: 1 on console print, 0 otherwise.
 */
int sck_log_error    (const char *, ...);

/*
 * Print message to CRITICAL-log.
 * Only displays in console,
 * if the SCK_LOG_LEVEL includes SCK_LOG_LEVEL_CRITICAL.
 * Accepts string formatting like printf().
 * 
 * Returns: 1 on console print, 0 otherwise.
 */
int sck_log_critical (const char *, ...);

#endif /* SCK_LOG_H */
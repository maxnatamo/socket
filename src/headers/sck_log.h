#ifndef SCK_LOG_H
#define SCK_LOG_H

#define SCK_LOG_LEVEL_DEBUG             0b0001 /* 0001 */
#define SCK_LOG_LEVEL_WARNING           0b0010 /* 0010 */
#define SCK_LOG_LEVEL_ERROR             0b0100 /* 0100 */
#define SCK_LOG_LEVEL_CRITICAL          0b1000 /* 1000 */

int sck_log_debug(const char * message);
int sck_log_warning(const char * message);
int sck_log_error(const char * message);
int sck_log_critical(const char * message);

#endif /* SCK_LOG_H */
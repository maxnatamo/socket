#ifndef SCK_CONFIG_H
#define SCK_CONFIG_H

#define SCK_SOCKET_MAX_CONNECTIONS      50
#define SCK_LOG_LEVEL                   (SCK_LOG_LEVEL_DEBUG | SCK_LOG_LEVEL_WARNING | SCK_LOG_LEVEL_ERROR | SCK_LOG_LEVEL_CRITICAL)

/*
 * Server-root
 * This is the directory, in which to put requested files relative to.
 * The server-root should be an absolute path.
 */
static char *sck_server_root = "/var/www/html/";

/*
 * Try-files
 * In case that no specific files is requested,
 * try to look for default files.
 * These files are relative to the server-root directory.
 */
static char *sck_try_files[] = {
    "index.html",
    "index.htm",
    "index.php"
};

#endif /* SCK_CONFIG_H */
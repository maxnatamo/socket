#ifndef SCK_CONFIG_H
#define SCK_CONFIG_H

#define SCK_SOCKET_MAX_CONNECTIONS      50
#define SCK_LOG_LEVEL                   (SCK_LOG_LEVEL_DEBUG | SCK_LOG_LEVEL_WARNING | SCK_LOG_LEVEL_ERROR | SCK_LOG_LEVEL_CRITICAL)

static const char *sck_server_root = "/var/www/html";
static const char *sck_try_files[] = {
    "index.html",
    "index.htm",
    "index.php"
};

#endif /* SCK_CONFIG_H */
#ifndef SCK_CORE_H
#define SCK_CORE_H

#define uint_t       unsigned int

typedef struct sck_connection_s    sck_connection_t;

#include <sck_http.h>
#include <sck_socket.h>
#include <sck_config.h>

int sck_length_of_int(int);

#endif /* SCK_CORE_H */
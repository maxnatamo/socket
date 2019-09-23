#ifndef SCK_SOCKET_H
#define SCK_SOCKET_H

#define SCK_SOCKET_ADDR_ANY     ((in_addr_t) 0x00000000)

#include <sck_core.h>

void sck_socket_initialize (sck_connection_t *connection, int listen_address, int port);
void sck_socket_bind (sck_connection_t *connection);
void sck_socket_listen (sck_connection_t *connection, int max_connections);
void sck_socket_accept (sck_connection_t *connection, sck_http_request_t *request);

#endif /* SCK_SOCKET_H */
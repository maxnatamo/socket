#ifndef SCK_SOCKET_H
#define SCK_SOCKET_H

#define SCK_SOCKET_ADDR_ANY     ((in_addr_t) 0x00000000)

#include <sck_core.h>

void sck_socket_initialize (sck_socket_t *sock, int listen_address, int port);
void sck_socket_bind (sck_socket_t *socket);
void sck_socket_listen (sck_socket_t *socket, int max_connections);
void sck_socket_accept (sck_socket_t *socket, sck_http_request_t *request);

#endif /* SCK_SOCKET_H */
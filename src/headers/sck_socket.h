#ifndef SCK_SOCKET_H
#define SCK_SOCKET_H

#define SCK_SOCKET_ADDR_ANY     ((in_addr_t) 0x00000000)

#include <sck_core.h>

/*
 * Initialize the connection-socket,
 * without binding the address or port.
 * 
 * Returns: SCK_OK (0) on success, negative value otherwise.
 * See sck_log.h for error codes.
 */
int sck_socket_initialize (sck_socket_t *sock, int listen_address, int port);

/*
 * Bind the connection-socket, to the specified address and port,
 * set in sck_socket_initialize.
 * 
 * Returns: SCK_OK (0) on success, negative value otherwise.
 * See sck_log.h for error codes.
 */
int sck_socket_bind (sck_socket_t *socket);

/*
 * Start listening on the connection socket.
 * max_connections is the maximum amount of concurrent connections,
 * before making the listening-call blocking.
 * 
 * Returns: SCK_OK (0) on success, negative value otherwise.
 * See sck_log.h for error codes.
 */
int sck_socket_listen (sck_socket_t *socket, int max_connections);

/*
 * Waits for a connection on the socket.
 * This function is blocking, until a connection arrives.
 * 
 * Returns: SCK_OK (0) on success, negative value otherwise.
 * See sck_log.h for error codes.
 */
int sck_socket_accept (sck_socket_t *socket, sck_http_request_t *request);

#endif /* SCK_SOCKET_H */
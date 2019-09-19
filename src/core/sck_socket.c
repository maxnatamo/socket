#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sck_core.h>

void sck_socket_initialize (sck_connection_t *connection, int listen_address, int port) {
    connection->error  = (connection->fd = socket(AF_INET, SOCK_STREAM, 0));
    connection->port   = port;

    if(connection->error == -1) {
        fprintf(stderr, "ERROR: Failed to initialize socket.\nError code: %s (%d)\n", strerror(errno), errno);
        return;
    }

    connection->addr.sin_family        = AF_INET;
    connection->addr.sin_addr.s_addr   = htonl(listen_address);
    connection->addr.sin_port          = htons(port);
}

void sck_socket_bind (sck_connection_t *connection) {
    connection->error = bind(connection->fd, (struct sockaddr *) &(connection->addr), sizeof(connection->addr));
    
    if(connection->error == -1) {
        fprintf(stderr, "ERROR: Failed to bind socket.\nError code: %s (%d)\n", strerror(errno), errno);
    }
}

void sck_socket_listen (sck_connection_t *connection, int max_connections) {
    connection->error = listen(connection->fd, max_connections);
    
    if(connection->error == -1) {
        fprintf(stderr, "ERROR: Failed to listen to address.\nError code: %s (%d)\n", strerror(errno), errno);
    }
}

// Blocking function
void sck_socket_accept (sck_connection_t *connection, sck_http_request_t *request) {
    socklen_t client_len;
    struct sockaddr_in client_addr;

    client_len      = sizeof(client_addr);
    request->error  = (request->fd = accept(connection->fd, (struct sockaddr *) &client_addr, &client_len));
    request->conn   = connection;

    if(request->error == -1) {
        fprintf(stderr, "ERROR: Failed to accept connection.\nError code: %s (%d)\n", strerror(errno), errno);
    }
}
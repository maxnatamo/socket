#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
// #include <fcntl.h>

#include <sck_core.h>

/*
 * sck_socket_t renamed to 'sock' as, otherwise,
 * <sys/socket.h> socket function was unable to be called.
 */ 
int sck_socket_initialize (sck_socket_t *sock, int listen_address, int port) {
    sock->error  = (sock->fd = socket(AF_INET, SOCK_STREAM, 0));
    sock->port   = port;

    if(sock->error == -1) {
        sck_log_critical("Failed to initialize socket. %s (%d)", strerror(errno), errno);
        return SCK_ERROR;
    }

    sock->addr.sin_family        = AF_INET;
    sock->addr.sin_addr.s_addr   = htonl(listen_address);
    sock->addr.sin_port          = htons(port);

    return SCK_OK;
}

int sck_socket_bind (sck_socket_t *socket) {
    socket->error = bind(socket->fd, (struct sockaddr *) &(socket->addr), sizeof(socket->addr));
    
    if(socket->error == -1) {
        sck_log_critical("Failed to bind socket. %s (%d)", strerror(errno), errno);
        return SCK_ERROR;
    }
    return SCK_OK;
}

int sck_socket_listen (sck_socket_t *socket, int max_connections) {
    socket->error = listen(socket->fd, max_connections);
    
    if(socket->error == -1) {
        sck_log_critical("Failed to listen to address. %s (%d)", strerror(errno), errno);
        return SCK_ERROR;
    }
    return SCK_OK;
}

int sck_socket_accept (sck_socket_t *socket, sck_http_request_t *request) {
    socklen_t client_len;
    struct sockaddr_in client_addr;

    client_len       = sizeof(client_addr);
    request->error   = (request->fd = accept(socket->fd, (struct sockaddr *) &client_addr, &client_len));
    request->conn    = socket;
    request->address = (uint32_t)client_addr.sin_addr.s_addr;

    if(request->error == -1 || request->fd == -1) {
        sck_log_error("Failed to accept connection. %s (%d)", strerror(errno), errno);
        return SCK_ERROR;
    }
    return SCK_OK;
}
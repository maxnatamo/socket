#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sck_core.h>

int main(int argc, char *argv[])
{
    int err;
    sck_socket_t *socket = malloc(sizeof(sck_socket_t));

    err = sck_socket_initialize (socket, SCK_SOCKET_ADDR_ANY, 4444);
    if(err != SCK_OK) {
        sck_log_critical("Closing.");
        return err;
    }

    sck_modules_init();

    err = sck_socket_bind (socket);
    if(err != SCK_OK) {
        sck_log_critical("Closing.");
        return err;
    }

    err = sck_socket_listen (socket, SCK_SOCKET_MAX_CONNECTIONS);
    if(err != SCK_OK) {
        sck_log_critical("Closing.");
        return err;
    }

    for(;;) {
        sck_http_request_t *request   = malloc(sizeof(sck_http_request_t));
        sck_http_response_t *response = malloc(sizeof(sck_http_response_t));

        err = sck_socket_accept(socket, request);
        if(err != SCK_OK) {
            sck_log_error("Failed to accept socket connection. Closing connection.");
            continue;
        }

        err = sck_http_read_request(request, response);
        if(err != SCK_OK) {
            sck_log_error("Failed to read HTTP-request. Closing connection.");
            sck_http_close (request);
            continue;
        }

        err = sck_http_handle_request(request, response);
        if(err != SCK_OK) {
            sck_log_error("Failed to handle HTTP-request. Closing connection.");
            sck_http_close (request);
            continue;
        }
        sck_modules_handler(request, response);

        response->conn          = socket;
        response->contentlength = strlen(response->content);

        err = sck_http_write (request, response);
        if(err != SCK_OK) {
            sck_log_error("Failed to send HTTP-response. Closing connection.");
            sck_http_close (request);
            continue;
        }

        err = sck_http_close (request);
        if(err != SCK_OK) {
            sck_log_error("Failed to close HTTP-connection.");
            continue;
        }
    }
    return 0;
}
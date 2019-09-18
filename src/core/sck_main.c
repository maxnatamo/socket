#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sck_core.h>

int main(int argc, char *argv[])
{
    sck_connection_t *connection = malloc(sizeof(sck_connection_t));

    sck_socket_initialize (connection, SCK_SOCKET_ADDR_ANY, 4444);
    if(connection->error == -1) {
        return 1;
    }

    sck_socket_bind (connection);
    if(connection->error == -1) {
        return 1;
    }

    sck_socket_listen (connection, SCK_SOCKET_MAX_CONNECTIONS);
    if(connection->error == -1) {
        return 1;
    }

    for(;;) {
        sck_http_request_t *request = malloc(sizeof(sck_http_request_t));

        sck_socket_accept(connection, request);
        printf("Client connected!\n");

        char *http_response = "HTTP/1.1 200 Ok\r\n"
                              "Content-Length: 8\r\n"
                              "\r\n"
                              "OIOIOI\r\n";

        // Send HTTP response
        sck_http_write (request, http_response);
        if(request->error == -1) {
            return 1;
        }

        sck_http_close (request);
        if(request->error == -1) {
            return 1;
        }
    }

    return 0;
}
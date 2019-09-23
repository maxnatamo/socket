#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        sck_http_request_t *request   = malloc(sizeof(sck_http_request_t));
        sck_http_response_t *response = malloc(sizeof(sck_http_response_t));

        sck_socket_accept(connection, request);
        sck_http_handle_request(connection, request);

        response->httpmajor    = 1;
        response->httpminor    = 0;
        response->statuscode   = 200;
        response->contenttype  = "text/html";
        response->content      = "<html><body><h1>lol</h1></body></html>";
        response->contentlength = strlen(response->content);

        // Send HTTP response
        sck_http_write (request, response);
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
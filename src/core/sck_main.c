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
        sck_http_request_t *request = malloc(sizeof(sck_http_request_t));
        request->response = malloc(sizeof(sck_http_request_response_t));

        sck_socket_accept(connection, request);

        request->response->httpmajor    = 1;
        request->response->httpminor    = 1;
        request->response->statuscode   = 200;
        request->response->contenttype  = "text/html";
        request->response->content      = "<html><body><h1>lol</h1></body></html>";
        request->response->contentlength = strlen(request->response->content);

        // Send HTTP response
        sck_http_write (request, request->response);
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
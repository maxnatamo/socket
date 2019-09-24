#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sck_core.h>

int main(int argc, char *argv[])
{
    sck_socket_t *socket = malloc(sizeof(sck_socket_t));

    sck_socket_initialize (socket, SCK_SOCKET_ADDR_ANY, 4444);
    if(socket->error == -1) {
        return 1;
    }

    sck_socket_bind (socket);
    if(socket->error == -1) {
        return 1;
    }

    sck_socket_listen (socket, SCK_SOCKET_MAX_CONNECTIONS);
    if(socket->error == -1) {
        return 1;
    }

    for(;;) {
        sck_http_request_t *request   = malloc(sizeof(sck_http_request_t));
        sck_http_response_t *response = malloc(sizeof(sck_http_response_t));

        sck_socket_accept(socket, request);
        sck_http_handle_request(request);

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sck_core.h>

void sck_http_write(sck_http_request_t *request, char *response) {
    request->error = write(request->fd, response, strlen(response));

    if(request->error == -1) {
        fprintf(stderr, "ERROR: Failed to accept connection.\nError code: %s (%d)\n", strerror(request->error), request->error);
    }
}

void sck_http_close(sck_http_request_t *request) {
    request->error = close(request->fd);

    if(request->error == -1) {
        fprintf(stderr, "ERROR: Failed to close connection.\nError code: %s (%d)\n", strerror(request->error), request->error);
    }
    free(request);
}
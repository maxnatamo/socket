#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sck_core.h>

void sck_http_write(sck_http_request_t *request, sck_http_request_response_t *response) {
    /*
        char *http_response = "HTTP/1.1 200 OK\r\n"
            "Content-Length: 8\r\n"
            "\r\n"
            "OIOIOI\r\n";
    */

    char *baseresponse = "HTTP/%d.%d %d %s\r\nContent-Length: %d\r\nContent-type: %s\r\n\r\n%s\r\n";
    unsigned int entirelength = strlen(baseresponse) - 12;

    entirelength += sck_length_of_int(request->response->httpmajor);
    entirelength += sck_length_of_int(request->response->httpminor);
    entirelength += sck_length_of_int(request->response->statuscode);
    entirelength += sck_length_of_int(request->response->contentlength);
    entirelength += strlen(request->response->contenttype);
    entirelength += strlen(request->response->content);

    char *formattedstring = malloc(sizeof(char) * entirelength);
    int len = sprintf(
        formattedstring, baseresponse,
        request->response->httpmajor,
        request->response->httpminor,
        request->response->statuscode,
        "OK",
        request->response->contentlength,
        request->response->contenttype,
        request->response->content
    );

    if(entirelength != len) {
        fprintf(stderr, "ERROR: Predicted length of HTTP-response is not correct!\nPred. length: %d, actual length: %d\n\nHTTP-response:\n%s", entirelength, len, formattedstring);
    }

    request->error = write(request->fd, formattedstring, entirelength);

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
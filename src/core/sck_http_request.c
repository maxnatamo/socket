#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sck_core.h>

// TODO: Refactor this disaster
int sck_http_write(sck_http_request_t *request, sck_http_response_t *response) {
    char *baseresponse = "HTTP/%d.%d %d %s\r\nContent-Length: %d\r\nContent-type: %s\r\n\r\n%s\r\n";
    unsigned int entirelength = strlen(baseresponse) - 12;

    entirelength += sck_util_length_of_int(response->httpmajor);
    entirelength += sck_util_length_of_int(response->httpminor);
    entirelength += sck_util_length_of_int(response->statuscode);
    entirelength += sck_util_length_of_int(response->contentlength);
    entirelength += strlen(response->contenttype);
    entirelength += strlen(response->content);

    char *formattedstring = malloc(sizeof(char) * entirelength);
    int len = sprintf(
        formattedstring, baseresponse,
        response->httpmajor,
        response->httpminor,
        response->statuscode,
        "OK",
        response->contentlength,
        response->contenttype,
        response->content
    );

    if(entirelength != len) {
        sck_log_warning("Predicted length of HTTP-response is not correct!\nPred. length: %d, actual length: %d\n\nHTTP-response:\n%s", entirelength, len, formattedstring);
    }

    request->error = write(request->fd, formattedstring, entirelength);

    if(request->error == -1) {
        sck_log_error("Failed to accept connection.\nError code: %s (%d)\n", strerror(request->error), request->error);
        return SCK_ERROR;
    }
    return SCK_OK;
}

int sck_http_close(sck_http_request_t *request) {
    request->error = close(request->fd);

    if(request->error == -1) {
        sck_log_error("Failed to close connection.\nError code: %s (%d)\n", strerror(request->error), request->error);
        return SCK_ERROR;
    }
    free(request);
    return SCK_OK;
}
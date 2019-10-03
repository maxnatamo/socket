#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sck_core.h>

// TODO: Refactor this disaster
int sck_http_write(sck_http_request_t *request, sck_http_response_t *response) {
    sck_string_t *resp_content = sck_string_create();

    sck_string_append(resp_content, "HTTP/");
    sck_string_append(resp_content, sck_util_integer_to_char_p(response->httpmajor));
    sck_string_append(resp_content, ".");
    sck_string_append(resp_content, sck_util_integer_to_char_p(response->httpminor));
    sck_string_append(resp_content, " ");
    sck_string_append(resp_content, sck_util_integer_to_char_p((int)(response->statuscode)));
    sck_string_append(resp_content, " ");
    sck_string_append(resp_content, "OK\r\n");
    sck_string_append(resp_content, "Content-Length: ");
    sck_string_append(resp_content, sck_util_integer_to_char_p(response->contentlength));
    sck_string_append(resp_content, "\r\n");
    sck_string_append(resp_content, "Content-Type: ");
    sck_string_append(resp_content, response->contenttype);
    sck_string_append(resp_content, "\r\n\r\n");
    sck_string_append(resp_content, response->content);
    sck_string_append(resp_content, "\r\n");

    request->error = write(request->fd, resp_content->data, resp_content->length);

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
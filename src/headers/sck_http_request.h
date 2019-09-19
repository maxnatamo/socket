#ifndef SCK_HTTP_REQUEST_H
#define SCK_HTTP_REQUEST_H

struct sck_http_request_response_s {
    // HTTP Version numbering.
    int                 httpmajor;      // HTTP/1.1, Major = 1
    int                 httpminor;      // HTTP/1.1, Minor = 1

    // Response headers.
    int                 statuscode;     // 200, 403, 404, etc.
    int                 contentlength;  // Length of content.
    char                *contenttype;   // "text/html", "text/plain", etc.
    char                *content;       // Actual content. HTML, plaintext, etc.
};
typedef struct sck_http_request_response_s sck_http_request_response_t;

struct sck_http_request_s {
    sck_connection_t    *conn;          // HTTP parent connection.
    int                 fd;             // File descriptor
    int                 error;          // Socket error code. Not to be confused with status code.
    sck_http_request_response_t *response; // Response headers. Not always set.
};
typedef struct sck_http_request_s  sck_http_request_t;

void sck_http_write (sck_http_request_t *request, sck_http_request_response_t *response);
void sck_http_close (sck_http_request_t *request);

#endif /* SCK_HTTP_REQUEST_H */
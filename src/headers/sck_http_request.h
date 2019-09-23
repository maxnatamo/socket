#ifndef SCK_HTTP_REQUEST_H
#define SCK_HTTP_REQUEST_H

#include <sck_core.h>
#include <stdint.h>

struct sck_http_response_s {
    // HTTP Version numbering.
    uint8_t             httpmajor;      // HTTP/1.1, Major = 1
    uint8_t             httpminor;      // HTTP/1.1, Minor = 1

    // Response headers.
    uint8_t             statuscode;     // 200, 403, 404, etc.
    uint32_t            contentlength;  // Length of content.
    char                *contenttype;   // "text/html", "text/plain", etc.
    char                *content;       // Actual content. HTML, plaintext, etc.
};

struct sck_http_request_s {
    sck_connection_t    *conn;          // HTTP parent connection.
    int                 fd;             // File descriptor
    int                 error;          // Socket error code. Not to be confused with status code.
    uint32_t            address;        // Request address, stored in a 4-byte hexadecimal value.
};

struct sck_http_request_line_s {
    char            *method;            // GET, HEAD, POST, PUT, etc.
    char            *requested_url;     // Requsted file, relative to root (/).
    int             http_version_major; // HTTP 1.1, major = 1.
    int             http_version_minor; // HTTP 1.1, minor = 1.
};

struct sck_http_headers_s {
    sck_http_request_line_t     *request_line;
    sck_vector_t                *single_headers;
};

void sck_http_write (sck_http_request_t *request, sck_http_response_t *response);
void sck_http_close (sck_http_request_t *request);

#endif /* SCK_HTTP_REQUEST_H */
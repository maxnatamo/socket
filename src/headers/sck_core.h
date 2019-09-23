#ifndef SCK_CORE_H
#define SCK_CORE_H

#include <stdint.h>
#include <netinet/in.h>

typedef struct sockaddr_in      sck_sock_addr_t;

typedef struct {
    int                 fd;
    unsigned int        port;
    sck_sock_addr_t     addr;
    int                 error;
} sck_connection_t;

typedef struct {
    // HTTP Version numbering.
    uint8_t             httpmajor;      // HTTP/1.1, Major = 1
    uint8_t             httpminor;      // HTTP/1.1, Minor = 1

    // Response headers.
    uint8_t             statuscode;     // 200, 403, 404, etc.
    uint32_t            contentlength;  // Length of content.
    char                *contenttype;   // "text/html", "text/plain", etc.
    char                *content;       // Actual content. HTML, plaintext, etc.
} sck_http_request_response_t;

typedef struct {
    sck_connection_t    *conn;          // HTTP parent connection.
    int                 fd;             // File descriptor
    int                 error;          // Socket error code. Not to be confused with status code.
    uint32_t            address;        // Request address, stored in a 4-byte hexadecimal value.
    sck_http_request_response_t *response; // Response headers. Not always set.
} sck_http_request_t;

typedef struct {
    char *index;
    char *value;
} sck_http_single_header_t;

typedef struct {
    char            *method;            // GET, HEAD, POST, PUT, etc.
    char            *requested_url;     // Requsted file, relative to root (/).
    int             http_version_major; // HTTP 1.1, major = 1.
    int             http_version_minor; // HTTP 1.1, minor = 1.
} sck_http_request_line_t;

typedef struct {
    sck_http_request_line_t     *request_line;
    sck_http_single_header_t    **single_headers;
} sck_http_headers_t;

#include <sck_socket.h>
#include <sck_http.h>
#include <sck_utils.h>
#include <sck_log.h>
#include <sck_config.h>

#endif /* SCK_CORE_H */
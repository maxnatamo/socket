#ifndef SCK_HTTP_H
#define SCK_HTTP_H

#include <netinet/in.h>
/*
 *  STATUS CODES
 */

#define SCK_HTTP_OK                   (uint8_t)200
#define SCK_HTTP_CREATED              (uint8_t)201
#define SCK_HTTP_ACCEPTED             (uint8_t)202
#define SCK_HTTP_NOINFO               (uint8_t)204
#define SCK_HTTP_PARTIAL              (uint8_t)206

#define SCK_HTTP_MULTIPLE_CHOICE      (uint8_t)300
#define SCK_HTTP_MOVED_PERM           (uint8_t)301
#define SCK_HTTP_MOVED_TEMP           (uint8_t)302
#define SCK_HTTP_TEMP_REDIRECT        (uint8_t)307
#define SCK_HTTP_PERM_REDIRECT        (uint8_t)308

#define SCK_HTTP_BAD_REQUEST          (uint8_t)400
#define SCK_HTTP_UNAUTHORIZED         (uint8_t)401
#define SCK_HTTP_FORBIDDEN            (uint8_t)403
#define SCK_HTTP_NOT_FOUND            (uint8_t)404
#define SCK_HTTP_NOT_ALLOWED          (uint8_t)405
#define SCK_HTTP_REQUEST_TIME_OUT     (uint8_t)408
#define SCK_HTTP_PAYLOAD_TOO_LARGE    (uint8_t)413
#define SCK_HTTP_URI_TOO_LARGE        (uint8_t)414
#define SCK_HTTP_INVALID_RANGE        (uint8_t)416
#define SCK_HTTP_TEAPOT               (uint8_t)418  /* Simply a joke. See HTTP 418. */

#define SCK_HTTP_INTERNAL_ERROR       (uint8_t)500
#define NGX_HTTP_NOT_IMPLEMENTED      (uint8_t)501
#define NGX_HTTP_BAD_GATEWAY          (uint8_t)502
#define NGX_HTTP_SERVICE_UNAVAILABLE  (uint8_t)503
#define NGX_HTTP_GATEWAY_TIME_OUT     (uint8_t)504

struct sck_socket_s {
    int                 fd;
    unsigned int        port;
    struct sockaddr_in  addr;
    int                 error;
};

#include <sck_http_request.h>
#include <sck_http_handler.h>
#include <sck_http_parser.h>

#endif /* SCK_HTTP_H */
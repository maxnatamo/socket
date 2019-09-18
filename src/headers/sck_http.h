#ifndef SCK_HTTP_H
#define SCK_HTTP_H

/*
 *  STATUS CODES
 */

#define SCK_HTTP_OK                   200
#define SCK_HTTP_CREATED              201
#define SCK_HTTP_ACCEPTED             202
#define SCK_HTTP_NOINFO               204
#define SCK_HTTP_PARTIAL              206

#define SCK_HTTP_MULTIPLE_CHOICE      300
#define SCK_HTTP_MOVED_PERM           301
#define SCK_HTTP_MOVED_TEMP           302
#define SCK_HTTP_TEMP_REDIRECT        307
#define SCK_HTTP_PERM_REDIRECT        308

#define SCK_HTTP_BAD_REQUEST          400
#define SCK_HTTP_UNAUTHORIZED         401
#define SCK_HTTP_FORBIDDEN            403
#define SCK_HTTP_NOT_FOUND            404
#define SCK_HTTP_NOT_ALLOWED          405
#define SCK_HTTP_REQUEST_TIME_OUT     408
#define SCK_HTTP_PAYLOAD_TOO_LARGE    413
#define SCK_HTTP_URI_TOO_LARGE        414
#define SCK_HTTP_INVALID_RANGE        416
#define SCK_HTTP_TEAPOT               418  /* Simply a joke. See HTTP 418. */

#define SCK_HTTP_INTERNAL_ERROR       500
#define NGX_HTTP_NOT_IMPLEMENTED      501
#define NGX_HTTP_BAD_GATEWAY          502
#define NGX_HTTP_SERVICE_UNAVAILABLE  503
#define NGX_HTTP_GATEWAY_TIME_OUT     504

#include <sck_http_request.h>

#endif /* SCK_HTTP_H */
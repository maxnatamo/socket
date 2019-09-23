#ifndef SCK_HTTP_REQUEST_H
#define SCK_HTTP_REQUEST_H

#include <sck_core.h>

void sck_http_write (sck_http_request_t *request, sck_http_request_response_t *response);
void sck_http_close (sck_http_request_t *request);

#endif /* SCK_HTTP_REQUEST_H */
#ifndef SCK_HTTP_HANDLER_H
#define SCK_HTTP_HANDLER_H

#include <sck_core.h>

/*
 * Read the HTTP-request headers,
 * and parse them into the request->headers_in field.
 * 
 * Returns: SCK_OK (0) on success, negative value otherwise.
 * See sck_log.h for error codes.
 */
int sck_http_read_request   (sck_http_request_t *, sck_http_response_t *);

/*
 * Determine the content for the HTTP-response,
 * and respond accordingly.
 * 
 * Returns: SCK_OK (0) on success, negative value otherwise.
 * See sck_log.h for error codes.
 */
int sck_http_handle_request (sck_http_request_t *, sck_http_response_t *);

#endif /* SCK_HTTP_HANDLER_H */
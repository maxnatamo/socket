#ifndef SCK_HTTP_PARSER_H
#define SCK_HTTP_PARSER_H

#include <sck_core.h>

/*
 * Parse HTTP-request headers, to a sck_http_headers_t pointer.
 * Request line and single headers are parsed individually.
 * See src/headers/sck_http_request.h for header-structure.
 * 
 * Returns: Parsed HTTP-header, in sck_http_headers_t-pointer format.
 */
sck_http_headers_t *sck_http_header_parse (char *raw_header);

#endif /* SCK_HTTP_PARSER_H */
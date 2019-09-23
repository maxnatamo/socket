#ifndef SCK_HTTP_PARSER_H
#define SCK_HTTP_PARSER_H

#include <sck_core.h>

sck_http_headers_t *sck_http_header_parse (char *raw_header);

#endif /* SCK_HTTP_PARSER_H */
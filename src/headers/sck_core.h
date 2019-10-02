#ifndef SCK_CORE_H
#define SCK_CORE_H

/* sck_http.h */
typedef struct sck_socket_s sck_socket_t;

/* sck_http_request.h */
typedef struct sck_http_request_line_s sck_http_request_line_t;
typedef struct sck_http_headers_s sck_http_headers_t;
typedef struct sck_http_request_s sck_http_request_t;
typedef struct sck_http_response_s sck_http_response_t;

/* sck_utils.h */
typedef struct sck_util_table_elem_s sck_util_table_elem_t;

/* sck_vector.h */
typedef struct sck_vector_s sck_vector_t;

/* sck_string.h */
typedef struct sck_string_s sck_string_t;

#include <sck_socket.h>
#include <sck_http.h>
#include <sck_utils.h>
#include <sck_log.h>
#include <sck_vector.h>
#include <sck_string.h>
#include <sck_module.h>
#include <sck_config.h>

#endif /* SCK_CORE_H */
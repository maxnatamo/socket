#ifndef SCK_HTTP_REQUEST_H
#define SCK_HTTP_REQUEST_H

struct sck_http_request_s {
    sck_connection_t  *conn;
    int               fd;
    int               error;
};

typedef struct sck_http_request_s  sck_http_request_t;

void sck_http_write (sck_http_request_t *request, char *response);
void sck_http_close (sck_http_request_t *request);

#endif /* SCK_HTTP_REQUEST_H */
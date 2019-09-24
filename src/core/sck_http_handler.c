#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sck_core.h>

void sck_http_handle_request (sck_http_request_t *request) {
    uint16_t increment = 64;
    uint16_t total = increment;

    char a='\0',b='\0',c='\0',d='\0';
    char *content = malloc(sizeof(char) * total);
    int n, size = 0;

    while(1) {
        a = b;
        b = c;
        c = d;

        if(size >= total) {
            total += increment;
            content = realloc(content, sizeof(char) * total);
        }

        n = recv(request->fd, &d, sizeof(d), 0);
        if(n < 0) {
            perror("sck_http_handle_request()");
            fprintf(stderr, "ERROR: An error occured, while receiving data from the client. %s (%d)\n", strerror(errno), errno);
            break;
        }

        // End of request.
        if(a == '\r' && b == '\n' && c == '\r' && d == '\n') {
            break;
        }

        content[size] = d;
        size++;
    }
    sck_http_header_parse(content);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sck_core.h>

int sck_http_handle_request (sck_http_request_t *request) {
    char *server_root = malloc(sizeof(char) * strlen(sck_server_root));
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
            sck_log_error("An error occured, while receiving data from the client. %s (%d)", strerror(errno), errno);
            return SCK_ERROR;
        }

        // End of request.
        if(a == '\r' && b == '\n' && c == '\r' && d == '\n') {
            break;
        }

        content[size] = d;
        size++;
    }
    request->headers_in = sck_http_header_parse(content);
    strcpy(server_root, sck_server_root);

    char *file_path = sck_util_path_join(server_root, request->headers_in->request_line->requested_url);
    uint8_t status = 0;

    if(sck_util_file_exists(file_path) == 1) {
        status = 1;
    } else {
        for(int i = 0; i < SIZE(sck_try_files); i++) {
            char *try_file    = malloc(sizeof(char) * strlen(sck_try_files[i]));
            strcpy(try_file, sck_try_files[i]);

            char *try_file_path = sck_util_path_join(
                server_root,
                sck_util_path_join(request->headers_in->request_line->requested_url, try_file)
            );
            if(sck_util_file_exists(try_file_path)) {
                status = 1;
                strcpy(file_path, try_file_path);
                break;
            }
        }
    }
    return SCK_OK;
}
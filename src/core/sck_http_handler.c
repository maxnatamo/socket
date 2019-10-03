#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sck_core.h>

int sck_http_handler_file     (sck_http_request_t *, sck_http_response_t *, sck_string_t *);
int sck_http_handler_dirindex (sck_http_request_t *, sck_http_response_t *);

int sck_http_read_request (sck_http_request_t *request, sck_http_response_t *response) {
    uint32_t increment = 64;
    uint32_t total = increment;
    uint16_t size = 0;

    char a='\0',b='\0',c='\0',d='\0';
    char *content = calloc(total, sizeof(char));
    int n;

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
    return SCK_OK;
}

int sck_http_handle_request (sck_http_request_t *request, sck_http_response_t *response) {
    sck_string_t *file_path = sck_string_create();
    sck_string_append(file_path, sck_util_path_join(sck_server_root, request->headers_in->request_line->requested_url));

    uint8_t file_descriptor = sck_util_is_file(file_path->data);
    uint8_t file_found = 0;

    if(file_descriptor == SCK_FILE_REG) {
        if(sck_http_handler_file(request, response, file_path) == SCK_OK) {
            file_found = 1;
        }
    } else if(file_descriptor == SCK_FILE_DIR) {
        for(int i = 0; i < SIZE(sck_try_files); i++) {
            char *try_file              = sck_try_files[i];
            sck_string_t *try_file_path = sck_string_create();

            sck_string_append_s(try_file_path, file_path);
            sck_string_append  (try_file_path, try_file);

            if(sck_util_is_file(try_file_path->data) == SCK_FILE_REG) {
                if(sck_http_handler_file(request, response, try_file_path) == SCK_OK) {
                    file_found = 1;
                }
                break;
            }
        }
    } else if(file_descriptor == SCK_FILE_IDK) {
        sck_log_debug("Invalid file requested. Attemped URL: %s", file_path->data);
        return SCK_INVALID_PARAMETERS;
    }
    
    if(!file_found) {
        sck_log_warning("Requested file not found. Using Dirindex.");
        sck_http_handler_dirindex(request, response);
    }
    return SCK_OK;
}

int sck_http_handler_file(sck_http_request_t *request, sck_http_response_t *response, sck_string_t *file) {
    char *content;
    size_t size = 0;
    size_t res  = 0;

    FILE *f = fopen(file->data, "rb");
    if(f == NULL) {
        sck_log_error("Could not open file '%s,' %s (%d)", file->data, strerror(errno), errno);

        response->content       = "<h1>Error - File not found</h1>";
        response->contenttype   = sck_util_get_content_type("html");
        response->contentlength = strlen(response->content);
        response->statuscode    = SCK_HTTP_NOT_FOUND;
        response->httpmajor     = 1;
        response->httpminor     = 1;

        return SCK_INVALID_PARAMETERS;
    }

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    rewind(f);

    content = malloc(size * sizeof(char));
    res = fread(content, 1, size, f);

    if(res != size) {
        sck_log_error("Error reading file '%s'", file->data);

        response->content     = "<h1>Error reading file</h1>";
        response->contenttype = sck_util_get_content_type("html");
        response->statuscode  = SCK_HTTP_INTERNAL_ERROR;
        response->httpmajor   = 1;
        response->httpminor   = 1;

        return SCK_MEMORY_ERROR;
    }
    printf("Image size: %ld\n", size);
    for(int i = 0; i < 64; i++) {
        printf("%d ", content[i]);
    }
    printf("\n");
    fclose(f);
    
    response->content       = content;
    response->contentlength = size;
    response->contenttype   = sck_util_get_content_type(file->data);
    response->statuscode    = SCK_HTTP_OK;
    response->httpmajor     = 1;
    response->httpminor     = 1;

    return SCK_OK;
}

int sck_http_handler_dirindex(sck_http_request_t *request, sck_http_response_t *response) {
    sck_vector_t *vec = sck_vector_create(sizeof(char **));
    char *file_path   = sck_util_path_join(sck_server_root, request->headers_in->request_line->requested_url);

    if(sck_util_list_directory(file_path, vec) != SCK_OK) {
        sck_log_error("Dirindex failed to list directory '%s'.", file_path);
        return SCK_INVALID_PARAMETERS;
    }

    sck_string_t *html = sck_string_create();
    sck_string_append(html, "<!DOCTYPE html><html><body>");

    for(int i = 0; i < vec->size; i++) {
        char *elem = (char *) sck_vector_get(vec, i);
        printf("elem: %s\n", elem);
        sck_string_append(html, "<p><a href='");
        sck_string_append(html, elem);
        sck_string_append(html, "'>");
        sck_string_append(html, elem);
        sck_string_append(html, "</a></p>");
    }
    sck_string_append(html, "</body></html>");

    response->content       = html->data;
    response->contentlength = strlen(response->content);
    response->httpmajor     = 1;
    response->httpminor     = 1;
    response->contenttype   = "text/html";
    response->statuscode    = SCK_HTTP_OK;

    return SCK_OK;
}
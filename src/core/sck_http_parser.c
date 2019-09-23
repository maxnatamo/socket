#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sck_core.h>

sck_http_request_line_t *sck_http_header_parse_request_line(char *raw_header) {
    sck_http_request_line_t *request_line = malloc(sizeof(sck_http_request_line_t));

    // Parse request-line into string.
    int i = strcspn(raw_header, "\n");
    char *request_line_c = sck_util_substring(raw_header, 0, i);
    
    // Parse rest of fields.
    int j = 0;
    char *http_version;
    char *pch = strtok(request_line_c, " ");

    while(pch != NULL && j <= 2) {
        if(j == 0) {
            request_line->method = pch;
        } else if(j == 1) {
            request_line->requested_url = pch;
        } else if(j == 2) {
            http_version = pch;
        }
        pch = strtok(NULL, " ");
        j++;
    }

    // Parse HTTP-version.
    char *http_major, *http_minor;
    i = strcspn(http_version, "/") + 1;

    request_line->http_version_major = atoi(sck_util_substring(http_version, i, i + 1));
    request_line->http_version_minor = atoi(sck_util_substring(http_version, i + 2, i + 3));

    return request_line;
}

sck_util_table_elem_t *sck_http_header_parse_single(char *header_c) {
    sck_util_table_elem_t *header = malloc(sizeof(sck_util_table_elem_t));

    long colon = strchr(header_c, ':') - header_c + 1;
    header->index = sck_util_trim(sck_util_substring(header_c, 0, (int)colon - 1));
    header->value = sck_util_trim(sck_util_substring(header_c, (int)colon + 1, -1));

    return header;
}

sck_http_headers_t *sck_http_header_parse(char *raw_header) {
    sck_http_headers_t *http_headers = malloc(sizeof(sck_http_headers_t));
    sck_vector_char_t *lines         = malloc(sizeof(sck_vector_char_t));
    lines->length                    = sck_util_char_amount(raw_header, "\r");
    lines->data                      = malloc(sizeof(char *) * lines->length);
    http_headers->request_line       = sck_http_header_parse_request_line(raw_header);
    http_headers->single_headers     = sck_vector_create();

    int i = 0;
    char *pch, head[strlen(raw_header)];

    strcpy(head, raw_header);
    pch = strtok(head, "\r");

    while(pch != NULL) {
        lines->data[i] = pch;
        pch = strtok(NULL, "\r");
        i++;
    }

    // Starts at 1, to skip request-line.
    // Stops at len-1, to skip the CRLF.
    for(int i = 1; i < lines->length - 1; i++) {
        sck_vector_push(http_headers->single_headers, (void *)sck_http_header_parse_single(lines->data[i]));
    }
    return http_headers;
}
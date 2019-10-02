#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sck_core.h>

sck_string_t *sck_string_create() {
    sck_string_t *string = malloc(sizeof(sck_string_t));

    string->length = 0;
    string->data   = calloc(string->length, sizeof(char));

    return string;
}

sck_string_t *sck_string_create_n(char *start) {
    sck_string_t *string = sck_string_create();
    sck_string_set(string, start, strlen(start));
    
    return string;
}

sck_string_t *sck_string_create_ns(sck_string_t *start) {
    sck_string_t *string = sck_string_create();
    sck_string_set_s(string, start, start->length);
    
    return string;
}

void sck_string_allocate(sck_string_t *string, int fields) {
    if(!string) { return; }

    string->length = fields;
    string->data   = calloc(string->length, sizeof(char));
}

void sck_string_set(sck_string_t *string, char *source, int num) {
    if(!source || !string) { return; }

    string->data = calloc(num, sizeof(char));
    strncpy(string->data, source, num);
    string->length = strlen(string->data);
}

void sck_string_set_s(sck_string_t *string, sck_string_t *source, int num) {
    if(!source || !string) { return; }

    string->data = calloc(num, sizeof(char));
    strncpy(string->data, source->data, num);
    string->length = strlen(string->data);
}

void sck_string_append(sck_string_t *string, char *source) {
    if(!source || !string) { return; }

    string->data   = realloc(string->data, (string->length + strlen(source)) * sizeof(char) + 1);
    string->length = string->length + strlen(source);
    strcat(string->data, source);
}

void sck_string_append_s(sck_string_t *string, sck_string_t *source) {
    if(!source || !string) { return; }

    string->data   = realloc(string->data, (string->length + source->length) * sizeof(char));
    string->length = string->length + source->length;
    strncat(string->data, source->data, source->length);
}

void sck_string_delete(sck_string_t *string) {
    string->length = 0;
    free(string->data);
    free(string);
}
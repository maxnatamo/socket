#include <stdlib.h>
#include <stdint.h>
#include <sck_core.h>

sck_vector_t *sck_vector_create() {
    sck_vector_t *vec   = malloc(sizeof(sck_vector_t));

    vec->size           = 0;
    vec->data           = malloc(vec->size * sizeof(void *));
    return vec;
}

void sck_vector_push(sck_vector_t *vec, void *element) {
    vec->size++;
    vec->data = realloc(vec->data, vec->size * sizeof(void *));
    vec->data[vec->size - 1] = element;
}

void sck_vector_pop(sck_vector_t *vec) {
    if(vec->size > 0) {
        vec->size--;
        vec->data = realloc(vec->data, vec->size * sizeof(void *));
    }
}

void sck_vector_set(sck_vector_t *vec, int index, void *element) {
    if(index <= vec->size) {
        vec->data[index] = element;
    }
}

void *sck_vector_get(sck_vector_t *vec, int index) {
    if(index <= vec->size) {
        return vec->data[index];
    }
    return (void *)NULL;
}
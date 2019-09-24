#include <stdlib.h>
#include <stdint.h>
#include <sck_core.h>

sck_vector_t *sck_vector_create(uint16_t pointer_size) {
    sck_vector_t *vec   = malloc(sizeof(sck_vector_t));

    vec->size           = 0;
    vec->pointer_size   = pointer_size;
    vec->data           = malloc(vec->size * pointer_size);
    return vec;
}

void sck_vector_push(sck_vector_t *vec, void *element) {
    vec->size++;
    vec->data = realloc(vec->data, vec->size * vec->pointer_size);
    vec->data[vec->size - 1] = element;
}

void sck_vector_pop(sck_vector_t *vec) {
    if(vec->size > 0) {
        vec->size--;
        vec->data = realloc(vec->data, vec->size * vec->pointer_size);
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
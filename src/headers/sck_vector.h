#ifndef SCK_VECTOR_H
#define SCK_VECTOR_H

#include <stdint.h>
#include <sck_core.h>

struct sck_vector_s {
    void        **data;
    uint16_t    size;
    uint16_t    pointer_size;
};

sck_vector_t *sck_vector_create(uint16_t pointer_size);
void sck_vector_allocate  (sck_vector_t *, uint16_t size);
void sck_vector_push      (sck_vector_t *, void *element);
void sck_vector_pop       (sck_vector_t * );
void sck_vector_set       (sck_vector_t *, int index, void *element);
void *sck_vector_get      (sck_vector_t *, int index);

#endif /* SCK_VECTOR_H */
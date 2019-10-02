#ifndef SCK_VECTOR_H
#define SCK_VECTOR_H

#include <stdint.h>
#include <sck_core.h>

struct sck_vector_s {
    void        **data;        // Data of the vector
    uint16_t    size;          // The length of the vector
    uint16_t    pointer_size;  // Size of the element-pointer.
};

/*
 * Create sck_vector_t object.
 * The value-pointer size have to be specified,
 * as not all pointer sizes are equal. Therefore, if making a character-vector,
 * (vector containing 'char *') pass the size of a char** (char-pointer-pointer).
 * For an integer vector, pass the size of a int* (int-pointer)
 * 
 * Returns: The allocated sck_vector_t pointer.
 */
sck_vector_t *sck_vector_create (uint16_t);

/*
 * Allocate space of 'size'-amount of fields.
 * This is usually for manually setting elements.
 * 
 * Returns: void
 */
void sck_vector_allocate (sck_vector_t *, uint16_t);

/*
 * Push/add element onto the end of vector.
 * Types and pointer-sizes are not managed.
 * You're expected to manage that yourself.
 * 
 * Returns: void
 */
void sck_vector_push (sck_vector_t *, void *);

/*
 * Pop/remove the last element of vector.
 * 
 * Returns: void
 */
int sck_vector_pop (sck_vector_t *);

/*
 * Set the value of the vector at 'index' to 'element'.
 * Types and pointer-sizes are not managed.
 * You're expected to manage that yourself.
 * 
 * Returns: void
 */
int sck_vector_set (sck_vector_t *, int, void *);

/*
 * Get the value of the vector at 'index'.
 * Types and pointer-sizes are not managed.
 * You're expected to manage that yourself.
 * 
 * Returns: void
 */
void *sck_vector_get (sck_vector_t *, int);

#endif /* SCK_VECTOR_H */
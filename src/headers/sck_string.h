#ifndef SCK_STRING_H
#define SCK_STRING_H

#include <sck_core.h>

struct sck_string_s {
    char        *data;
    uint16_t     length;
};

/*
 * Create sck_string_t object.
 * 
 * Returns: The allocated sck_string_t pointer.
 */
sck_string_t *sck_string_create    ();

/*
 * Create sck_string_t object,
 * with specified start-value (char *).
 * 
 * Returns: The allocated sck_string_t pointer.
 */
sck_string_t *sck_string_create_n  (char *);

/*
 * Create sck_string_t object,
 * with specified start-value (sck_string_t *).
 * 
 * Returns: The allocated sck_string_t pointer.
 */
sck_string_t *sck_string_create_ns (sck_string_t *);

/*
 * Allocate space of 'field'-amount of characters.
 * This is usually for manually setting char-indexes.
 * 
 * Returns: void
 */
void          sck_string_allocate  (sck_string_t *, int);

/*
 * Set the current content of the string to the first *num* characters of source (char *).
 * Much like strncpy() and strncat(), from string.h
 * 
 * Returns: void
 */
void          sck_string_set       (sck_string_t *, char *, int);

/*
 * Set the current content of the string to the first *num* characters of source (sck_string_t *).
 * Much like strncpy() and strncat(), from string.h
 * 
 * Returns: void
 */
void          sck_string_set_s     (sck_string_t *, sck_string_t *, int);

/*
 * Append characters to the string (char *).
 * This function also reallocates the data-array.
 * 
 * Returns: void
 */
void          sck_string_append    (sck_string_t *, char *);

/*
 * Append characters to the string (sck_string_t *).
 * This function also reallocates the data-array.
 * 
 * Returns: void
 */
void          sck_string_append_s  (sck_string_t *, sck_string_t *);

/*
 * Delete/free/deallocate the string.
 * 
 * Returns: void
 */
void          sck_string_delete    (sck_string_t *);

#endif /* SCK_STRING_H */
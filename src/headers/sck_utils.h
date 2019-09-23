#ifndef SCK_UTILS_H
#define SCK_UTILS_H

typedef struct {
    int length;
    char **data;

} sck_vector_char_t;

int   sck_util_length_of_int(int x);
char *sck_util_substring(char *string, int beginning, int end);
int   sck_util_char_amount(char *string, char *chars);
char *sck_util_trim(char *string);

#endif /* SCK_UTILS_H */
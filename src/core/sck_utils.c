#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sck_core.h>

int sck_util_length_of_int(int x) {
    if(x == 0) return 1;
    if(x <  0) return sck_util_length_of_int(abs(x)) + 1;
    
    return floor(log10(abs(x))) + 1;
}

char *sck_util_substring(char *string, int beginning, int end) {
    if((beginning >= end && end != -1) || beginning < 0 || strlen(string) <= beginning) {
        return "(null)";
    }
    if(end == -1 || strlen(string) < end) {
        end = strlen(string);
    }

    char *res = malloc(sizeof(char) * end - beginning);
    strncpy(res, string + beginning, end - beginning);
    return res;
}

int sck_util_char_amount(char *string, char *chars) {
    int amount = 0;
    for(int x = 0; x < strlen(string); x++) {
        for(int y = 0; y < strlen(chars); y++) {
            if(string[x] == chars[y]) {
                amount++;
            }
        }
    }
    return amount;
}

char *sck_util_trim(char *string) {
    int l = strlen(string);
    int front  = (string[0] == ' ' || string[0] == '\n' || string[0] == '\r') ? 1 : 0;
    int back   = (string[l] == ' ' || string[l] == '\n' || string[l] == '\r') ? 1 : 0;

    if(back == 1) {
        l--;
        string = realloc(string, sizeof(char) * l);
    }

    if(front == 1) {
        for(int i = 1; i < l; i++) {
            string[i - 1] = string[i];
        }
        l--;
        string[l] = '\0';
        string = realloc(string, sizeof(char) * l);
    }
    return string;
}

char *sck_util_path_join(char *a, char *b) {
    sck_string_t *path_a = sck_string_create_n(a);
    sck_string_t *path_b = sck_string_create_n(b);
    sck_string_t *full_path = sck_string_create();

    if(path_a->data[path_a->length - 1] == '/') {
        sck_string_delete(path_a);
        path_a = sck_string_create();

        sck_string_allocate(path_a, strlen(a) - 1);
        strncpy(path_a->data, a, strlen(a) - 1);
        path_a->length = strlen(path_a->data);
    }

    if(path_b->data[0] == '/') {
        char *temp = calloc(strlen(b), sizeof(char));
        strcpy(temp, path_b->data);

        sck_string_delete(path_b);
        path_b = sck_string_create();

        sck_string_allocate(path_b, strlen(b) - 1);
        memmove(temp, b + 1, strlen(b) - 1);
        strncpy(path_b->data, temp, strlen(b) - 1);
        path_b->length = strlen(b) - 1;
    }

    sck_string_append_s(full_path, path_a);
    sck_string_append  (full_path, "/");
    sck_string_append_s(full_path, path_b);

    return full_path->data;
}

uint8_t sck_util_file_exists(char *path) {
    return (access(path, R_OK) != -1) ? (uint8_t) 1 : (uint8_t) 0;
}

uint8_t sck_util_is_file(char *path) {
    if(sck_util_file_exists(path) == 0) {
        return SCK_FILE_IDK;
    }

    struct stat s;
    if(stat(path, &s) == 0) {
        switch(s.st_mode & __S_IFMT) {
            case __S_IFREG:     return SCK_FILE_REG;  break;
            case __S_IFDIR:     return SCK_FILE_DIR;  break;
            case __S_IFCHR:     return SCK_FILE_CHR;  break;
            case __S_IFBLK:     return SCK_FILE_BLK;  break;
            case __S_IFIFO:     return SCK_FILE_FIFO; break;
            case __S_IFLNK:     return SCK_FILE_LNK;  break;
            default:            return SCK_FILE_IDK;  break;
        }
    }
}

int sck_util_list_directory(char *path, sck_vector_t *vec) {
    DIR *dp;
    int t = sck_util_is_file(path);
    if(t != SCK_FILE_DIR ) {
        sck_log_error("'%s' is not a directory.", path);
        return SCK_FILE_NOT_FOUND;
    }

    dp = opendir(path);
    if(dp == NULL) {
        sck_log_error("'%s' is not a valid directory. Failed to open directory. (%d)", path, errno);
        return SCK_FILE_NOT_FOUND;
    }

    struct dirent *ep;
    while((ep = readdir(dp)) != NULL) {
        sck_vector_push(vec, ep->d_name);
    }
    closedir(dp);
    return SCK_OK;
}

char *sck_util_get_file_extension(char *file) {
    char *pch = (char *) strrchr(file, '.');
    char *extension;
    if(pch != NULL) {
        // If the '.' (period) is the last character, allocate nothing.
        if((int)(pch - file) >= strlen(file) - 1) {
            extension = calloc(0, sizeof(char));
        } else {
            extension = malloc((strlen(file) - (int)(pch - file) - 1) * sizeof(char));
            strcpy(extension, sck_util_substring(file, (int)(pch - file + 1), strlen(file)));
        }
    } else {
        extension = calloc(0, sizeof(char));
    }
    return extension;
}

char *sck_util_default_content_type() {
    char *assoc = calloc(strlen(sck_file_type_assoc[0].value) - 1, sizeof(char));
    strcpy(assoc, sck_file_type_assoc[0].value);

    return assoc;
}

char *sck_util_get_content_type(char *file) {
    char *assoc;
    char *extension = sck_util_get_file_extension(file);
    for(int i = 0; i < SIZE(sck_file_type_assoc); i++) {
        if(strcmp(sck_file_type_assoc[i].index, extension) == 0) {
            assoc = calloc(strlen(sck_file_type_assoc[i].value) - 1, sizeof(char));
            strcpy(assoc, sck_file_type_assoc[i].value);

            return assoc;
        }
    }

    // If none is found, take the first association.
    return sck_util_default_content_type();
}
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

char *sck_util_path_join(char *path_a, char *path_b) {
    char *path_a_e = malloc(sizeof(char) * strlen(path_a)); // Must not have a suffixed backslash (/)
    char *path_b_e = malloc(sizeof(char) * strlen(path_b)); // Must not have a prefixed backslash (/)
    char *slash = malloc(sizeof(char));
    strcpy(slash, "/");

    // Remove trailing backslash of path_a, if found.
    if(path_a[strlen(path_a) - 1] == '/') {
        strncpy(path_a_e, path_a, strlen(path_a) - 1);
    } else {
        strncpy(path_a_e, path_a, strlen(path_a));
    }

    // Remove preceding backslash of path_b, if found.
    strncpy(path_b_e, path_b, strlen(path_b));
    if(path_b[0] == '/') {
        path_b_e[0] = ' ';
        strncpy(path_b_e, sck_util_trim(path_b_e), strlen(path_b) - 1);
    }
    return strcat(path_a_e, strcat(slash, path_b_e));
}

uint8_t sck_util_file_exists(char *path) {
    return (access(path, R_OK) != -1) ? (uint8_t)1 : (uint8_t)0;
}
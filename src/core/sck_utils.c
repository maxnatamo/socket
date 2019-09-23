#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
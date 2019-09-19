#include <math.h>
#include <stdlib.h>

int sck_length_of_int(int x) {
    return floor(log10(abs(x))) + 1;
}
#include "str-util.h"

void formatFloat(char* target, char* src, float value) {
    int decimal = value;  // Get the integer (678).
    int fraction = trunc((value - decimal) * 1000);

    sprintf(target, src, decimal, fraction);
}
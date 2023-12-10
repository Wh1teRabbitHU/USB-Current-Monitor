#include "str-util.h"

void formatFloat(char* target, float value, char* unit) {
    int decimal = value;
    int fraction = trunc((value - decimal) * 100);
    char* padding;

    if (decimal < 10) {
        padding = "   ";
    } else if (decimal < 100) {
        padding = "  ";
    } else if (decimal < 1000) {
        padding = " ";
    } else {
        padding = "";
    }

    sprintf(target, "%s%d.%02d %s", padding, decimal, fraction, unit);
}
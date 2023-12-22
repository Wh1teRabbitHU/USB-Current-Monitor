#ifndef __BUFFER_H
#define __BUFFER_H

#include "display.h"

#define BUFFER_SIZE (DISPLAY_WIDTH - 7)

void Buffer_addValue(double value);
double Buffer_readValue(uint16_t index);

#endif
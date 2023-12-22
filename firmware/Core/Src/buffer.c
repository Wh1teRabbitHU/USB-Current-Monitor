#include "buffer.h"

static uint16_t nextIndex = 0;
static double currentHistory[BUFFER_SIZE] = {0};

void Buffer_addValue(double value) {
    currentHistory[nextIndex++] = value;

    if (nextIndex == BUFFER_SIZE) {
        nextIndex = 0;
    }
}

double Buffer_readValue(uint16_t index) {
    volatile uint16_t currentIndex = (nextIndex == 0 ? BUFFER_SIZE : nextIndex) - 1;
    volatile uint16_t absoluteIndex =
        currentIndex < index ? BUFFER_SIZE - (index - currentIndex) : currentIndex - index;

    return currentHistory[absoluteIndex];
}
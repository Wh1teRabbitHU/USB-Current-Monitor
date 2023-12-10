#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "main.h"

#define CONVERT_24BIT_COLOR(rgbValue) \
    (((rgbValue >> 19) & 0b111111) << 11) | (((rgbValue >> 10) & 0b111111) << 5) | ((rgbValue >> 3) & 0b111111)

typedef struct Display_textProps {
    uint8_t *font;
    char *text;
    uint16_t posX;
    uint16_t posY;
    uint16_t fontSize;
    uint16_t fontColor;
    uint16_t backgroundColor;
} Display_textProps;

void Display_init(void);
void Display_setPosition(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void Display_clear(unsigned int bColor);
void Display_drawCharacter(uint8_t *font, uint8_t character, uint16_t x, uint16_t y, uint8_t fontSize,
                           uint16_t fontColor, uint16_t bgcolor);
void Display_drawText(Display_textProps *textProps);
void Display_drawCircle(unsigned int x0, unsigned int y0, unsigned char r, unsigned int color);
void Display_drawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
void Display_drawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
void Display_drawPoint(unsigned int x, unsigned int y, unsigned int color);
void Display_drawPicture(unsigned int x, unsigned int y, unsigned int length, unsigned int width, const char pic[]);

#endif
#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "main.h"

#define DISPLAY_WIDTH 172
#define DISPLAY_HEIGHT 320
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
void Display_setPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void Display_clear(uint16_t bColor);
void Display_drawCharacter(uint8_t *font, uint8_t character, uint16_t x, uint16_t y, uint8_t fontSize,
                           uint16_t fontColor, uint16_t bgcolor);
void Display_drawText(Display_textProps *textProps);
void Display_drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void Display_drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void Display_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void Display_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void Display_drawPoint(uint16_t x, uint16_t y, uint16_t color);
void Display_drawPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]);

#endif
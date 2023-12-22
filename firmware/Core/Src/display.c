
#include <display.h>

void Display_sendDataByte(uint8_t data);
void Display_sendCmd(uint8_t cmd);
void Display_sendData(uint8_t DH, uint8_t DL);
void Display_sendDataHalfWord(uint16_t y);

uint8_t USE_HORIZONTAL = 0;  // 0,1 Vertical screen   2,3 Landscape screen

void Display_clear(uint16_t bColor) {
    uint16_t i, j;

    if ((USE_HORIZONTAL == 0) || (USE_HORIZONTAL == 1)) {
        Display_setPosition(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
    } else {
        Display_setPosition(0, 0, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH - 1);
    }

    for (i = 0; i < DISPLAY_HEIGHT; i++) {
        for (j = 0; j < DISPLAY_WIDTH; j++) {
            Display_sendDataHalfWord(bColor);
        }
    }
}

void Display_sendDataByte(uint8_t data) {
    uint8_t i;

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 0);
        HAL_GPIO_WritePin(DISPLAY_SDA_GPIO_Port, DISPLAY_SDA_Pin, data & 0x80 ? 1 : 0);
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 1);

        data = data << 1;
    }

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);
}

void Display_sendCmd(uint8_t cmd) {
    uint8_t i;

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 0);

    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 0);
        HAL_GPIO_WritePin(DISPLAY_SDA_GPIO_Port, DISPLAY_SDA_Pin, cmd & 0x80 ? 1 : 0);
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 1);

        cmd = cmd << 1;
    }

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);
}

void Display_sendData(uint8_t dataHigh, uint8_t dataLow) {
    uint8_t i;

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 0);
    HAL_GPIO_WritePin(DISPLAY_DC_GPIO_Port, DISPLAY_DC_Pin, 1);

    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 0);
        HAL_GPIO_WritePin(DISPLAY_SDA_GPIO_Port, DISPLAY_SDA_Pin, dataHigh & 0x80 ? 1 : 0);
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 1);

        dataHigh = dataHigh << 1;
    }

    for (i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 0);
        HAL_GPIO_WritePin(DISPLAY_SDA_GPIO_Port, DISPLAY_SDA_Pin, dataLow & 0x80 ? 1 : 0);
        HAL_GPIO_WritePin(DISPLAY_SCL_GPIO_Port, DISPLAY_SCL_Pin, 1);

        dataLow = dataLow << 1;
    }

    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);
}

void Display_sendDataHalfWord(uint16_t data) {
    uint8_t dataHigh = data >> 8;
    uint8_t dataLow = data;

    Display_sendData(dataHigh, dataLow);
}

void Display_init(void) {
    HAL_GPIO_WritePin(DISPLAY_CS_GPIO_Port, DISPLAY_CS_Pin, 1);

    HAL_Delay(5);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 0);
    HAL_Delay(10);
    HAL_GPIO_WritePin(DISPLAY_RESET_GPIO_Port, DISPLAY_RESET_Pin, 1);
    HAL_Delay(120);

    Display_sendCmd(0x11);
    Display_sendCmd(0x3A);
    Display_sendDataByte(0x05);

    Display_sendCmd(0xB2);
    Display_sendDataByte(0x0C);
    Display_sendDataByte(0x0C);
    Display_sendDataByte(0x00);
    Display_sendDataByte(0x33);
    Display_sendDataByte(0x33);

    Display_sendCmd(0xB7);
    Display_sendDataByte(0x35);

    Display_sendCmd(0xBB);
    Display_sendDataByte(0x35);

    Display_sendCmd(0xC0);
    Display_sendDataByte(0x2C);

    Display_sendCmd(0xC2);
    Display_sendDataByte(0x01);

    Display_sendCmd(0xC3);
    Display_sendDataByte(0x13);

    Display_sendCmd(0xC4);
    Display_sendDataByte(0x20);

    Display_sendCmd(0xC6);
    Display_sendDataByte(0x0F);

    Display_sendCmd(0xD0);
    Display_sendDataByte(0xA4);
    Display_sendDataByte(0xA1);

    Display_sendCmd(0xD6);
    Display_sendDataByte(0xA1);

    Display_sendCmd(0xE0);
    Display_sendDataByte(0xF0);
    Display_sendDataByte(0x00);
    Display_sendDataByte(0x04);
    Display_sendDataByte(0x04);
    Display_sendDataByte(0x04);
    Display_sendDataByte(0x05);
    Display_sendDataByte(0x29);
    Display_sendDataByte(0x33);
    Display_sendDataByte(0x3E);
    Display_sendDataByte(0x38);
    Display_sendDataByte(0x12);
    Display_sendDataByte(0x12);
    Display_sendDataByte(0x28);
    Display_sendDataByte(0x30);

    Display_sendCmd(0xE1);
    Display_sendDataByte(0xF0);
    Display_sendDataByte(0x07);
    Display_sendDataByte(0x0A);
    Display_sendDataByte(0x0D);
    Display_sendDataByte(0x0B);
    Display_sendDataByte(0x07);
    Display_sendDataByte(0x28);
    Display_sendDataByte(0x33);
    Display_sendDataByte(0x3E);
    Display_sendDataByte(0x36);
    Display_sendDataByte(0x14);
    Display_sendDataByte(0x14);
    Display_sendDataByte(0x29);
    Display_sendDataByte(0x32);

    Display_sendCmd(0x21);

    Display_sendCmd(0x11);
    HAL_Delay(120);
    Display_sendCmd(0x29);
    HAL_Delay(10);

    Display_clear(CONVERT_24BIT_COLOR(0xFFFFFF));

    HAL_GPIO_WritePin(DISPLAY_BLACKLIGHT_EN_GPIO_Port, DISPLAY_BLACKLIGHT_EN_Pin, 1);
}

void Display_setPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    Display_sendCmd(0x36);
    if (USE_HORIZONTAL == 0)
        Display_sendDataByte(0x00);
    else if (USE_HORIZONTAL == 1)
        Display_sendDataByte(0xC0);
    else if (USE_HORIZONTAL == 2)
        Display_sendDataByte(0x70);
    else
        Display_sendDataByte(0xA0);

    if (USE_HORIZONTAL == 0) {
        Display_sendCmd(0x2a);
        Display_sendDataHalfWord(x1 + 34);
        Display_sendDataHalfWord(x2 + 34);
        Display_sendCmd(0x2b);
        Display_sendDataHalfWord(y1);
        Display_sendDataHalfWord(y2);
        Display_sendCmd(0x2c);
    } else if (USE_HORIZONTAL == 1) {
        Display_sendCmd(0x2a);
        Display_sendDataHalfWord(x1 + 34);
        Display_sendDataHalfWord(x2 + 34);
        Display_sendCmd(0x2b);
        Display_sendDataHalfWord(y1);
        Display_sendDataHalfWord(y2);
        Display_sendCmd(0x2c);
    } else if (USE_HORIZONTAL == 2) {
        Display_sendCmd(0x2a);
        Display_sendDataHalfWord(x1);
        Display_sendDataHalfWord(x2);
        Display_sendCmd(0x2b);
        Display_sendDataHalfWord(y1 + 34);
        Display_sendDataHalfWord(y2 + 34);
        Display_sendCmd(0x2c);
    } else {
        Display_sendCmd(0x2a);
        Display_sendDataHalfWord(x1);
        Display_sendDataHalfWord(x2);
        Display_sendCmd(0x2b);
        Display_sendDataHalfWord(y1 + 34);
        Display_sendDataHalfWord(y2 + 34);
        Display_sendCmd(0x2c);
    }
}

void Display_drawCharacter(uint8_t *font, uint8_t character, uint16_t x, uint16_t y, uint8_t fontSize,
                           uint16_t fontColor, uint16_t bgcolor) {
    uint8_t i, j;
    uint8_t *temp = font;
    uint8_t fontWidth = 8 * fontSize;
    uint8_t fontHeight = 12 * fontSize;

    Display_setPosition(x, y, x + fontWidth - 1, y + fontHeight - 1);
    temp += (character - 32) * 12;
    for (j = 0; j < fontHeight; j++) {
        for (i = 0; i < fontWidth; i++) {
            if ((*temp & (1 << (7 - i / fontSize))) != 0) {
                Display_sendDataHalfWord(fontColor);
            } else {
                Display_sendDataHalfWord(bgcolor);
            }
        }

        if (j % fontSize == fontSize - 1) {
            temp++;
        }
    }
}

void Display_drawText(Display_textProps *textProps) {
    char *textPointer = textProps->text;
    uint16_t posX = textProps->posX;
    uint16_t posY = textProps->posY;
    uint8_t fontWidth = 8 * textProps->fontSize;

    while (*textPointer != '\0') {
        Display_drawCharacter(textProps->font, *textPointer, posX, posY, textProps->fontSize, textProps->fontColor,
                              textProps->backgroundColor);
        posX += fontWidth - 1;
        textPointer++;
    }
}

void Display_drawPoint(uint16_t x, uint16_t y, uint16_t color) {
    Display_setPosition(x, y, x, y);
    Display_sendDataHalfWord(color);
}

void Display_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    uint16_t t;
    int16_t xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int16_t incx, incy, uRow, uCol;
    delta_x = x2 - x1;
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)
        incx = 1;
    else if (delta_x == 0)
        incx = 0;
    else {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0;
    else {
        incy = -1;
        delta_y = -delta_x;
    }
    if (delta_x > delta_y)
        distance = delta_x;
    else
        distance = delta_y;
    for (t = 0; t < distance + 1; t++) {
        Display_drawPoint(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance) {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance) {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void Display_drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    Display_drawLine(x1, y1, x2, y1, color);
    Display_drawLine(x1, y1, x1, y2, color);
    Display_drawLine(x1, y2, x2, y2, color);
    Display_drawLine(x2, y1, x2, y2, color);
}

void Display_drawCircle(uint16_t x0, uint16_t y0, uint16_t r, uint16_t color) {
    int16_t a = 0;
    int16_t b = r;

    while (a <= b) {
        Display_drawPoint(x0 - b, y0 - a, color);  // 3
        Display_drawPoint(x0 + b, y0 - a, color);  // 0
        Display_drawPoint(x0 - a, y0 + b, color);  // 1
        Display_drawPoint(x0 - a, y0 - b, color);  // 2
        Display_drawPoint(x0 + b, y0 + a, color);  // 4
        Display_drawPoint(x0 + a, y0 - b, color);  // 5
        Display_drawPoint(x0 + a, y0 + b, color);  // 6
        Display_drawPoint(x0 - b, y0 + a, color);  // 7
        a++;

        if ((a * a + b * b) > (r * r)) {
            b--;
        }
    }
}

void Display_drawPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]) {
    uint16_t i, j;
    uint32_t k = 0;

    Display_setPosition(x, y, x + length - 1, y + width - 1);

    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            Display_sendData(pic[k * 2], pic[k * 2 + 1]);
            k++;
        }
    }
}
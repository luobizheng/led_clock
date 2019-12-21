#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "matrix_show.h"

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, 1, 1, PIN,
                                               NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE +
                                                   NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

const uint16_t red = matrix.Color(255, 0, 0);
const uint16_t green = matrix.Color(0, 255, 0);
const uint16_t blue = matrix.Color(0, 0, 255);
const uint16_t white = matrix.Color(255, 255, 255);

void off_show()
{
    matrix.fillScreen(0);
    matrix.show();
}

void show(char *str)
{
    int x = 0;
    int pos = strlen(str) * 4 /*5字符宽 - 1个字符串长度*/;

    while (x != -pos)
    {
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.setTextColor(red);
        matrix.print(str);
        matrix.show();
        if (pos < matrix.width())
            break;
        delay(100);
        x--;
    }
}

void show(char color, int delay_ms, int brightness, char *str)
{
    int x = 0;
    int pos = strlen(str) * 4/*5字符宽 - 1个字符串长度*/;

    while (x != -pos)
    {
        matrix.setBrightness(brightness);
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.setTextColor(color == 'R' ? red : color == 'G' ? green : color == 'B' ? blue : white);
        matrix.print(str);
        matrix.show();
        if (pos < matrix.width())
            break;
        delay(delay_ms);
        x--;
    }
}

void initMatrix()
{
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(100);
}

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <arduino.h>
#include "at_cmd.h"
#include "matrix_show.h"

struct ShowInfo
{
    int delay_ms;
    char color;
    int brightness;
    char str[128];
    bool is_show;
    bool is_clear;
};

extern ShowInfo info;

void initSerial();
bool parseInfo();

#endif
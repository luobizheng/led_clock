#include "serial.h"

ShowInfo info = {100, 'R', 10, "Hello"};
char buff[256];
int pos = 0;
bool is_ready = false;

void initSerial()
{
    Serial.begin(9600);
    memset(buff, 0, sizeof(buff));
    Serial.println("Hello");
}

void serialEvent()
{
    while (Serial.available())
    {
        buff[pos++] = (char)Serial.read();
        if (buff[pos - 2] == '\r' && buff[pos - 1] == '\n')
        {
            is_ready = true;
        }
    }
}

bool parseInfo()
{
    if (is_ready)
    {
        switch (get_at_message_type(buff))
        {
        case AT_UNKNOWN:
            break;
        case AT_REQUEST:
            if (IS_THAT_AT(buff, AT_REQUEST_ON))
            {
                info.is_show = true;
                Serial.print(AT_RESPONSE_ON);
            }
            else if (IS_THAT_AT(buff, AT_REQUEST_OFF))
            {
                Serial.print(AT_RESPONSE_OFF);
                info.is_clear = true;
            }
            else
            {
                char at_key[256] = {};
                char at_vaule[256] = {};
                get_at_message_key(buff, at_key);
                get_at_message_value(buff, at_vaule);

                if (strcmp(at_key, AT_COLOR) == 0)
                {
                    Serial.print(OK);
                    Serial.print(AT_COLOR);
                    Serial.print("=");
                    Serial.print(at_vaule);
                    Serial.print(TERMINATOR);
                    info.is_show = true;
                    info.color = *at_vaule;
                }
                else if (strcmp(at_key, AT_DELAY) == 0)
                {
                    Serial.print(OK);
                    Serial.print(AT_DELAY);
                    Serial.print("=");
                    Serial.print(at_vaule);
                    Serial.print(TERMINATOR);
                    info.is_show = true;
                    info.delay_ms = atoi(at_vaule);
                    if (info.delay_ms <= 0 || info.delay_ms > 10000)
                        info.delay_ms = 100;
                }
                else if (strcmp(at_key, AT_BRIGHTNESS) == 0)
                {
                    Serial.print(OK);
                    Serial.print(AT_BRIGHTNESS);
                    Serial.print("=");
                    Serial.print(at_vaule);
                    Serial.print(TERMINATOR);
                    info.is_show = true;
                    info.brightness = atoi(at_vaule);
                    if (info.brightness <= 0 || info.brightness > 100)
                        info.brightness = 20;
                }
                else if (strcmp(at_key, AT_STRING) == 0)
                {
                    Serial.print(OK);
                    Serial.print(AT_STRING);
                    Serial.print("=");
                    Serial.print(at_vaule);
                    Serial.print(TERMINATOR);
                    memset(info.str, 0, strlen(info.str));
                    memcpy(info.str, at_vaule, strlen(at_vaule));
                    info.is_show = true;
                }
            }
            break;
        case AT_RESPONSE:
            break;
        case AT_ERROR_RESPONSE:
            break;
        default:
            break;
        }

        is_ready = false;
        memset(buff, 0, sizeof(buff));
        pos = 0;
    }

    return true;
}
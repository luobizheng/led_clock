#ifndef __AT_CMD_H__
#define __AT_CMD_H__

////////////////////////////////////////////////////
#define AT              "AT+"   // 请求
#define OK              "OK+"   // 回应
#define ERR             "ERR+"  // 回应错误
#define TERMINATOR      "\r\n"

////////////////////////////////////////////////////
#define AT_REQUEST_ON       AT "ON"         TERMINATOR
#define AT_REQUEST_OFF      AT "OFF"        TERMINATOR
#define AT_RESPONSE_ON      OK "ON"         TERMINATOR
#define AT_RESPONSE_OFF     OK "OFF"        TERMINATOR

////////////////////////////////////////////////////
#define AT_COLOR        "COLOR"
#define AT_DELAY        "DELAY"
#define AT_STRING       "STRING"
#define AT_BRIGHTNESS   "BRIGHTNESS"

////////////////////////////////////////////////////
typedef enum {
    AT_UNKNOWN,
    AT_REQUEST,
    AT_RESPONSE,
    AT_ERROR_RESPONSE,
} ATMessageType;

////////////////////////////////////////////////////
ATMessageType get_at_message_type(const char *data);
char *get_at_message_key(const char *data, char *key);
char *get_at_message_value(const char *data, char *value);
////////////////////////////////////////////////////

#define IS_THAT_AT(__STR, __AT_CMD)  (strncmp(__STR, __AT_CMD, strlen(__AT_CMD)) == 0)
////////////////////////////////////////////////////


#endif
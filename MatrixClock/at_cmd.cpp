
#include "at_cmd.h"
#include <string.h>

ATMessageType get_at_message_type(const char *data)
{
    if (strncmp(data, AT, strlen(AT)) == 0) {
        return AT_REQUEST; 
    } else if (strncmp(data, OK, strlen(OK)) == 0) {
        return AT_RESPONSE;
    } else if (strncmp(data, ERR, strlen(ERR)) == 0) {
        return AT_ERROR_RESPONSE;
    } else {
        return AT_UNKNOWN;
    }
}


char *get_at_message_value(const char *data, char *value)
{
    if (AT_UNKNOWN == get_at_message_type(data)) {
        return NULL;
    }

    int start = 0, end = 0;
    int i = 0;
    for (; i < strlen(data); i++) {
        if ('=' == data[i])
            start = i;
        if ('\r' == data[i] || '\n' == data[i] || '\0' == data[i]) {
            end = i;
            break;
        }
    }

    if (0 == start || 0 == end) {
        return NULL;
    }

    memcpy(value, data + start + 1, end - start - 1);

    return value;
}

char *get_at_message_key(const char *data, char *key)
{
    if (AT_UNKNOWN == get_at_message_type(data)) {
        return NULL;
    }

    int start = 0, end = 0;
    int i = 0;
    for (; i < strlen(data); i++) {
        if ('+' == data[i])
            start = i;

        if ('=' == data[i]) {
            end = i;
            break;
        }
    }

    if (0 == start || 0 == end) {
        return NULL;
    }

    memcpy(key, data + start + 1, end - start - 1);

    return key;
}

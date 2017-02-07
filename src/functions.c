/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: functions.c
 */

#include <string.h>

#include "functions.h"

char* get_arg_value(char *args[], const int args_len, const char *arg) {
    // Gets the position in the array of the argument
    int pos = arg_exists(args, args_len, arg);

    // Gets the string length of the argument parameter
    int arg_len = strlen(arg);

    if (pos != -1) {
        // Returns the value of the argument and cuts 
        // off the argument and the equal sign
        return args[pos] + arg_len;
    } else {
        return "";
    }
}

/* Checks if argument arg starts with arg */
int arg_exists(char *args[], const int args_len, const char *arg) {
    int i;
    for (i = 1; i < args_len; i++) {
        if(str_starts_with(args[i], arg)) {
            return i;
        }
    }
    return 0;
}

/* Checks if string *str starts with string *pre */
int str_starts_with(const char *str, const char *pre) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

int divide_round_up(const int n, const int d) {
    return (n + (d - 1)) / d;
}

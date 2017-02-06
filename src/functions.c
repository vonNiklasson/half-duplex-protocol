/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: functions.c
 */

#include <string.h>
#include <stdlib.h>

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
int arg_exists(const char *args[], const int args_len, const char *arg) {
    int i;
    for (i = 1; i < args_len; i++) {
        if(str_starts_with(args[i], arg)) {
            return i;
        }
    }
    return 0;
}

/* Checks if string *str starts with string *pre */
int str_starts_with(const char *str, const char *pre)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

int divide_round_up(const int n, const int d) {
    return (n + (d - 1)) / d;
}

/* Converting data into binary */

unsigned char* convert_bits_to_binary(char* data_bits, int *ret_char_count) {
    // Number of characters that will be allocated
    int req_char_count = divide_round_up(strlen(data_bits), 8);
    unsigned char* r = malloc(req_char_count * sizeof(char));

    int i;               // Keeps track of outer loop
    int j;               // Keeps track of inner loop
    int bit_counter = 0; // Keeps track of the data bits
    int val;             // Holds the value of the current bit

    // Loops through the required characters
    for (i = 0; i < req_char_count; i++) {
        // Loops through the bits in each character in arg data_bits
        for (j = 7; j >= 0; j--) {

            val = 0; // Sets default value to 0
            // Gets the data value
            if (bit_counter < strlen(data_bits)) {
                // Try to see if the value is 1
                if (data_bits[bit_counter] == 0x31) {
                    val = 1;
                }
                bit_counter++;
            }
            // Starts at the highest bit position and work down to 0
            // and writes the value to r
            r[i] = r[i] | val << j;
        }
    }

    // Sets the required character count
    *ret_char_count = req_char_count;

    // Returns the binary code
    return r;
}






int* convert_bits_to_array(char* data_bits) {
    // Allocate memory for the data, + 1 byte for custom "nullbute"
    int* r = malloc(strlen(data_bits) * sizeof(int) + 1);

    int i;
    for (i = 0; i < strlen(data_bits); i++) {

        if (data_bits[i] == 0x31) {
            // If the char is "1", set to int 1
            r[i] = 1;
        } else {
            // Otherwise, always set 0 to avoid broken data
            r[i] = 0;
        }
    }

    // Sets the last bit to -1 to keep track if the last position
    r[i] = -1;

    return r;
}

int* convert_digits_to_array(char* data_digits) {

}

int* convert_chars_to_array(char* data_chars) {

}
/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: comm.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comm.h"

int * convert_bits_to_array(char* data_bits) {
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

int * convert_digits_to_array(char* data_digits) {

}

int * convert_chars_to_array(char* data_chars) {

}

int get_send_obj(
    int* bits,
    char* frequency,
    char* packet_low,
    char* packet_high)
{

}
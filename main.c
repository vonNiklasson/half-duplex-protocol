/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: main.c
 */

#include <stdio.h>
#include "comm.h"
#include "src/functions.h"

int main(int argc, char *argv[])
{    
    char* action;
    char* data_bits;
    char* data_digits;
    char* data_chars;
    char* frequency;
    char* packet_low;
    char* packet_high;

    int* bits; // For bits in array
    char* binary; // For bits as raw binary values

    int binary_char_count = 0;

    /* Gets type of action (send or listen/recieve) */
    if (arg_exists(argv, argc, "-a=")) {
        action = get_arg_value(argv, argc, "-a=");
    }

    /* Gets the data in bits that will be sent */
    if (arg_exists(argv, argc, "-b=")) {
        data_bits = get_arg_value(argv, argc, "-b=");

        bits = convert_bits_to_array(data_bits);
        binary = convert_bits_to_binary(data_bits, &binary_char_count);

        // Just test code to see that it works
        int i = 0;
        for (i = 0; i < binary_char_count; i++) {
            printf("%d", (*binary >> 7) & 1);
            printf("%d", (*binary >> 6) & 1);
            printf("%d", (*binary >> 5) & 1);
            printf("%d ", (*binary >> 4) & 1);
            printf("%d", (*binary >> 3) & 1);
            printf("%d", (*binary >> 2) & 1);
            printf("%d", (*binary >> 1) & 1);
            printf("%d ", (*binary >> 0) & 1);
            binary++;
        }
        printf("\n");
    }

    /* Gets the data in digits that will be sent */
    if (arg_exists(argv, argc, "-d=")) {
        data_digits = get_arg_value(argv, argc, "-d=");

        bits = convert_digits_to_array(data_bits);
    }

    /* Gets the data in chars that will be sent */
    if (arg_exists(argv, argc, "-c=")) {
        data_chars = get_arg_value(argv, argc, "-c=");

        bits = convert_chars_to_array(data_bits);
    }
    
    /* Gets the prefered frequency of bits per second */
    if (arg_exists(argv, argc, "-f=")) {
        frequency = get_arg_value(argv, argc, "-f=");
    }
    
    /* Get the location of the file that triggers a low value on packets */
    if (arg_exists(argv, argc, "-pl=")) {
        packet_low = get_arg_value(argv, argc, "-pl=");
    }
    
    /* Get the location of the file that triggers a high value on packets */
    if (arg_exists(argv, argc, "-ph=")) {
        packet_high = get_arg_value(argv, argc, "-ph=");
    }
}
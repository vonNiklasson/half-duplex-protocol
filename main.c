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

    int *bits;

    /* Gets type of action (send or listen/recieve) */
    if (arg_exists(argv, argc, "-a=")) {
        action = get_arg_value(argv, argc, "-a=");
    }

    /* Gets the data in bits that will be sent */
    if (arg_exists(argv, argc, "-b=")) {
        data_bits = get_arg_value(argv, argc, "-b=");

        int *bits = convert_bits_to_array(data_bits);
    }

    /* Gets the data in digits that will be sent */
    if (arg_exists(argv, argc, "-d=")) {
        data_digits = get_arg_value(argv, argc, "-d=");

        int *bits = convert_digits_to_array(data_bits);
    }

    /* Gets the data in chars that will be sent */
    if (arg_exists(argv, argc, "-c=")) {
        data_chars = get_arg_value(argv, argc, "-c=");

        int *bits = convert_chars_to_array(data_bits);
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
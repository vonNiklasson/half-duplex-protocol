/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "src/comm.h"
#include "src/convert.h"
#include "src/functions.h"

int main(int argc, char *argv[])
{    
    char* action;

    char* data_bits;
    char* data_digits;
    char* data_chars;

    int frequency = DEFAULT_TRANSMIT_FREQUENCY;
    int debug = DEFAULT_DEBUG;

    char* binary; // The binary data that will be sent

    /* Gets type of action (send or listen/recieve) */
    if (arg_exists(argv, argc, "-a=")) {
        action = get_arg_value(argv, argc, "-a=");
    }

    /* Gets the data in bits that will be sent */
    if (arg_exists(argv, argc, "-b=")) {
        data_bits = get_arg_value(argv, argc, "-b=");
        binary = convert_bits_to_binary(data_bits);
    }

    /* Gets the data in digits that will be sent */
    if (arg_exists(argv, argc, "-d=")) {
        data_digits = get_arg_value(argv, argc, "-d=");
        //binary = 
    }

    /* Gets the data in chars that will be sent */
    if (arg_exists(argv, argc, "-c=")) {
        data_chars = get_arg_value(argv, argc, "-c=");
        //binary = 
    }

    /* Gets the prefered frequency of bits per second */
    if (arg_exists(argv, argc, "-f=")) {
        char* f = get_arg_value(argv, argc, "-f=");
        frequency = atoi(f);
    }

    /* Gets the prefered debug of bits per second */
    if (arg_exists(argv, argc, "-l=")) {
        char* l = get_arg_value(argv, argc, "-l=");
        debug = atoi(l);
    }
}
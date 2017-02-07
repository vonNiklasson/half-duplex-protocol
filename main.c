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
    char* action = "s";

    char* binary; // The binary data that will be sent

    int frequency   = DEFAULT_TRANSMIT_FREQUENCY;
    int debug       = DEFAULT_DEBUG;
    int half_duplex = DEFAULT_EXPECT_HALF_DUPLEX;

    /* Gets type of action (send or listen/recieve) */
    if (arg_exists(argv, argc, "-a=")) {
        action = get_arg_value(argv, argc, "-a=");
    }

    /* Gets the data in bits that will be sent */
    if (arg_exists(argv, argc, "-b=")) {
        char* data = get_arg_value(argv, argc, "-b=");
        binary = convert_bits_to_binary(data);
    }

    /* Gets the data in digits that will be sent */
    if (arg_exists(argv, argc, "-d=")) {
        char* data = get_arg_value(argv, argc, "-d=");
        //binary = 
    }

    /* Gets the data in chars that will be sent */
    if (arg_exists(argv, argc, "-c=")) {
        char* data = get_arg_value(argv, argc, "-c=");
        //binary = 
    }

    /* Gets the prefered frequency of bits per second */
    if (arg_exists(argv, argc, "-f=")) {
        char* _frequency = get_arg_value(argv, argc, "-f=");
        frequency = atoi(_frequency);
    }

    /* If the program protocol will print a debug log during transmission */
    if (arg_exists(argv, argc, "-hd=")) {
        char* hd = get_arg_value(argv, argc, "-hd=");
        frequency = atoi(hd);
    }

    /* If the program protocol will print a debug log during transmission */
    if (arg_exists(argv, argc, "-l=")) {
        char* _debug = get_arg_value(argv, argc, "-l=");
        debug = atoi(_debug);
    }
}
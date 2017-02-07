/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: main.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/comm.h"
#include "src/convert.h"
#include "src/functions.h"

int main(int argc, char *argv[])
{    
    /* Default action is to send */
    char* action = "s";

    /* The binary data that will be sent */
    unsigned char* binary; 

    /* The length of the char array after binary assignment */
    int binary_byte_count = 0;


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
        binary = convert_bits_to_binary(data, &binary_byte_count);
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

    /* If the program will used half duplex */
    if (arg_exists(argv, argc, "-hd=")) {
        char* _half_duplex = get_arg_value(argv, argc, "-hd=");
        half_duplex = atoi(_half_duplex);
    }

    /* If the program protocol will print a debug log during transmission */
    if (arg_exists(argv, argc, "-l=")) {
        char* _debug = get_arg_value(argv, argc, "-l=");
        debug = atoi(_debug);
    }

    /* Validate data here */

    /* Compile the data into a struct object */
    SendObject sendObject = compile_send_object(
        binary,
        binary_byte_count,
        frequency,
        half_duplex,
        debug);

}
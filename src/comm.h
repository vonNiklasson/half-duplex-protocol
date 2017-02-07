/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: comm.h
 */

#ifndef COMM_H_INCLUDED
#define COMM_H_INCLUDED

#include "global.h"

typedef struct {
    /* The data that will be sent */
    unsigned char binary_data[DATA_BYTES_RESERVED];
    // Number of bytes that are used
    int binary_data_byte_count;
    /* The frequency of bits per second */
    int frequency;
    /* Wether to expect feedback from the reciever */
    int half_duplex;
    /* If the program shall print debug messages */
    int debug;
} SendObject;

typedef struct {
    unsigned char binary_handshake[DATA_HANDSHAKE_BITS_RESERVED];
    /* Doubled values because 0 will be sent as 01 and 1 will be sent as 10 */
    unsigned char binary_data[DATA_BYTES_RESERVED * 2];
    unsigned char binary_settings[DATA_SETTINGS_BYTES_RESERVED * 2];
    // Using int since 
    int binary_data_byte_count[DATA_BYTES_COUNT_RESERVED * 2];

    /* The frequency of bits per second */
    int frequency;
    /* Wether to expect feedback from the reciever */
    int half_duplex;
    /* If the program shall print debug messages */
    int debug;
} ComputedSendObject;

SendObject compile_send_object(
    unsigned char* binary_data,
    int byte_count,
    int frequency,
    int half_duplex,
    int debug);

#endif
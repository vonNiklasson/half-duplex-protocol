/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: comm.h
 */

#ifndef COMM_H_INCLUDED
#define COMM_H_INCLUDED

#include "global.h"

struct SendObject get_send_object(
    unsigned char binary,
    float frequency);

struct SendObject
{
    /* The data that will be sent */
    unsigned char binary[DATA_BYTES_RESERVED];
    /* Wether to expect feedback from the reciever */
    int half_duplex;
    /* The frequency of bits per second */
    float frequency;
};

struct ComputedSendObject
{   
    unsigned char binary_handshake[DATA_HANDSHAKE_BITS_RESERVED];
    /* Doubled values because 0 will be sent as 01 and 1 will be sent as 10 */
    unsigned char binary_data[DATA_BYTES_RESERVED * 2];
    unsigned char binary_data_byte_count[DATA_BYTES_COUNT_RESERVED * 2];
    unsigned char binary_settings[DATA_SETTINGS_BYTES_RESERVED * 2];
    float frequency;
};

#endif
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

struct StructuredSendObject
{   
    /* Doubled values because 0 will be sent as 01 and 1 will be sent as 10 */
    unsigned char binary[DATA_BYTES_RESERVED * 2];
    unsigned char settings[SETTINGS_BYTES_RESERVED * 2];
    unsigned char byte_count[PACKET_NUMBER_BYTES_RESERVED * 2];
    float frequency;
};

#endif
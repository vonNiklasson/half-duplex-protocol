/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: comm.c
 */

#include <stdio.h>
#include <string.h>
#include "comm.h"
#include "../platform/include.h"

// Compiles data to a SendObject
SendObject compile_send_object(
    unsigned char* binary_data,
    int byte_count,
    int frequency,
    int half_duplex,
    int debug)
{
    SendObject sendObject;

    /* Stores the plain values */
    sendObject.binary_data_byte_count = byte_count;
    sendObject.frequency = frequency;
    sendObject.half_duplex = half_duplex;
    sendObject.debug = debug;

    /* Copy over the binary data */
    int i = 0;
    for (i = 0; i < DATA_BYTES_RESERVED; i++) {
        sendObject.binary_data[i] = binary_data[i];
    }

    return sendObject;
}

/* Converts a SendObject to a ComputedSendObject */
ComputedSendObject compile_computed_send_object(
    SendObject send_object)
{
    ComputedSendObject cso;

    cso.frequency = send_object.frequency;

    return cso;
}
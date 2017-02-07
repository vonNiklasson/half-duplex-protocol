/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: comm.c
 */

#include <stdio.h>
#include <string.h>
#include "comm.h"

// Compiles data to a SendObject
SendObject get_send_object(
    unsigned char binary,
    float frequency)
{
    SendObject sendObject;

    return sendObject;
}

// Converts a SendObject to a ComputedSendObject
ComputedSendObject get_computed_send_object(
    SendObject send_obj)
{
    ComputedSendObject cso;

    cso.frequency = send_obj.frequency;

    return cso;
}
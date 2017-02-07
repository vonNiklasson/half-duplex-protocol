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
struct SendObject get_send_object(
    unsigned char binary,
    float frequency)
{
    struct SendObject sendObject;
}

// Converts a SendObject to a ComputedSendObject
struct ComputedSendObject get_structured_send_object(
    struct SendObject send_obj)
{
    struct ComputedSendObject cso;

    cso.frequency = send_obj.frequency;

    return cso;
}
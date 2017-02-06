/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: comm.h
 */

#ifndef COMM_H_INCLUDED
#define COMM_H_INCLUDED

int initialize_send_obj(
    int* bits,
    char* frequency,
    char* packet_low,
    char* packet_high);

struct send_obj
{
    /* The data that will be sent (not included the handshake etc) */
    int data_bits[32];
    /* The bits which is to represent the handshake */
    int handshake_bits[3];
    /* Wether to wait for the handshake confirmation */
    int handshake_confirm;
    /* The frequency of bits per second */
    float frequency;
    /* Location of the files that trigger a high and low value on packets */
    char *packet_low;
    char *packet_high;
};

#endif
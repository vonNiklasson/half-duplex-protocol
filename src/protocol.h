/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol.h
 */

#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED

#include <stdbool.h>

#include "protocol_platform.h"


/******************** Version specific values below ********************/

/* Version of the protocol */
#define PROTOCOL_VERSION "0.1"

/* Number of bytes that can be transmitted of the actual binary data */
#define DATA_BYTES_RESERVED 32
/* Number of bytes reserved for settings data */
#define SETTINGS_BYTES_RESERVED 1
/* Number of bytes reserved to tell how many bytes will be transmitted 
 * (Must be related with DATA_BYTES_RESERVED) */
#define DATA_BYTES_COUNT_RESERVED 1
/* Number of bytes that can me transmitted */
#define BITRATE_BITS_RESERVED 5


/******************** Default values below ********************/

/* The default bitrate if no bitrate is given */
#define DEFAULT_BITRATE 100
/* The default value of the transmission will expect to get feedback 
 * false=Simplex, true=Half duplex */
#define DEFAULT_HALF_DUPLEX false
/* Wether to show debug messages or not. Is a constant so it will be deoptimized if needed */
#define DEBUG true


/******************** Program variables below ********************/
/* Variables to be set by the caller (may have functions to cover as well) */

/* Send data */
unsigned char hdp_send_data[DATA_BYTES_RESERVED];
int hdp_bitrate;
bool hdp_half_duplex;

/* Recieve data */
unsigned char hdp_recieve_data[DATA_BYTES_RESERVED];

/******************** Functions to be used by the caller below ********************/

void hdp_initialize(void);

void hdp_transmit(void);
unsigned char hdp_recieve(void);

void hdp_data_set_bit(unsigned char *data, const int length, const int bit_position, const int bit);
void hdp_data_set_byte(unsigned char *data, const int length, const int byte_position, const int byte);
void hdp_data_clear(unsigned char *data, const int length);

int hdp_get_nearest_bitrate(const int bitrate);

#endif

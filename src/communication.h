/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/communication.h
 */

#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

#include <stdbool.h>

#include "functions.h"
#include "platform.h"


/******************** Version specific values below ********************/

/* Version of the protocol */
#define PROTOCOL_VERSION "0.1"

/* Number of bytes that can be transmitted of the actual binary data */
#define DATA_BYTES_RESERVED 32
/* Number of bytes reserved for settings data */
#define DATA_SETTINGS_BYTES_RESERVED 2
/* Number of bytes reserved to tell how many bytes will be transmitted 
 * (Must be related with DATA_BYTES_RESERVED) */
#define DATA_BYTES_COUNT_RESERVED 1
/* Number of bytes that can me transmitted */
#define DATA_HANDSHAKE_BITS_RESERVED 4


/******************** Default values below ********************/

/* The default frequency if no frequency is given */
#define DEFAULT_FREQUENCY 100
/* The default value of the transmission will expect to get feedback 
 * false=Simplex, true=Half duplex */
#define DEFAULT_HALF_DUPLEX false

/* Wether to show debug messages or not */
#define DEFAULT_DEBUG false


/******************** Default values below ********************/

/* Variables to be set by the caller */
unsigned char send_data[DATA_BYTES_RESERVED];
int frequency;
bool half_duplex;
bool debug;

/* Functions to be used by the caller */

void initialize(void);

void transmit(void);
void recieve(void);

void data_set_bit(unsigned char *data, const int length, const int bit_position, const int bit);
void data_set_byte(unsigned char *data, const int length, const int byte_position, const int byte);
void data_clear(unsigned char *data, const int length);

#endif

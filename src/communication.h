/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/communication.h
 */

#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

#include <stdbool.h>

#include "platform.h"


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
#define BITRATE_BITS_RESERVED 4


/******************** Default values below ********************/

/* The default bitrate if no bitrate is given */
#define DEFAULT_BITRATE 100
/* The default value of the transmission will expect to get feedback 
 * false=Simplex, true=Half duplex */
#define DEFAULT_HALF_DUPLEX false
/* Wether to show debug messages or not */
#define DEFAULT_DEBUG false


/******************** Program variables below ********************/

/* Variables to be set by the caller */
unsigned char send_data[DATA_BYTES_RESERVED];
int bitrate;
bool half_duplex;
bool debug;

unsigned char _settings[SETTINGS_BYTES_RESERVED];
unsigned char _data_count[DATA_BYTES_COUNT_RESERVED];

/******************** Functions to be used by the caller below ********************/

void initialize(void);

void transmit(void);
int recieve(void);

void data_set_bit(unsigned char *data, const int length, const int bit_position, const int bit);
void data_set_byte(unsigned char *data, const int length, const int byte_position, const int byte);
void data_clear(unsigned char *data, const int length);

#endif

/******************** Internal functions below ********************/

int _count_bytes_in_use(const unsigned char *data, const int length);
int _get_increased_bit(char bit, const int offset);
void _set_gpio_with_increased_bit(const char bit, const int delay);
void _set_gpio(const char bit, const int delay);

int _divide_round_up(const int n, const int d);

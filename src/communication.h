/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/communication.h
 */

#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

#include "global.h"
#include "functions.h"
#include "../platform/include.h"

unsigned char binary_data[DATA_BYTES_RESERVED];

void data_send(void);

void data_set_bit(const int bit_position, const int bit);
void data_set_byte(const int byte_position, const int byte);

#endif

/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/communication.c
 */

#include "communication.h"

/******************** Sending data functions ********************/

void initialize(void) {
    /* Clears the data */
    data_clear(send_data, DATA_BYTES_RESERVED);
    data_clear(_settings, SETTINGS_BYTES_RESERVED);
    data_clear(_data_count, DATA_BYTES_COUNT_RESERVED);

    /* Sets the default values unless changed */
    frequency = DEFAULT_FREQUENCY;
    half_duplex = DEFAULT_HALF_DUPLEX;
    debug = DEFAULT_DEBUG;
}

void transmit(void) {
    /* Setup the gpio and pull gpio to low */
    platform_gpio_setup();
    platform_gpio_set_low();
}



/******************** Modifying data array ********************/

void data_set_bit(unsigned char *data, const int length, const int bit_position, const int bit) {
    int bit_pos = bit_position;
    int byte_pos = 0;

    /* "Klättra" ner till rätt position för bit respektive byte */
    while (bit_pos > 7) {
        bit_pos -= 8;
        byte_pos++;
    }

    /* Om positionen för byte är större än vad som ryms, avbryt */
    if (byte_pos >= length) {
        return;
    }

    if (bit == 1) {
        /* Om biten är en 1:a, använd | (eller) */
        data[byte_pos] = data[byte_pos] | (1 << (7 - bit_pos));
    } else {
        /* Om biten är en 1:a, använd & (och) samt ~ (invertera) */
        data[byte_pos] = data[byte_pos] & ~(1 << (7 - bit_pos));
    }
}

void data_set_byte(unsigned char *data, const int length, const int byte_position, const int byte) {
    /* Om positionen för byte är större än vad som ryms, avbryt */
    if (byte_position >= length) {
        return;
    }
    
    data[byte_position] = byte;
}

/* Perhaps fix later, not very important right now
void data_fill_from_position(const int start_position, const int data) {
    if (byte_position >= DATA_BYTES_RESERVED) {
        return;
    }

    int base_bit_pos = byte_position * 8;

    int i;
    for (i = 0; i < 8; i++) {
        printf("%d\n", i);
    }
}
*/

void data_clear(unsigned char *data, const int length) {
    int i;
    for (i = 0; i < length; i++) {
        *(data + i) = 0;
    }
}
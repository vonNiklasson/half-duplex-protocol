/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/communication.c
 */

#include "communication.h"

/*
 * Sending data
 */

void initialize(void) {
    /* Clears the data */
    data_clear();
    /* Set debug to default value */
    debug = DEFAULT_DEBUG;
}

void data_send(void) {
    platform_gpio_setup();
    platform_gpio_set_low();
}



/*
 * Modifying the data array
 */

void data_set_bit(const int bit_position, const int bit) {
    int bit_pos = bit_position;
    int byte_pos = 0;

    /* "Klättra" ner till rätt position för bit respektive byte */
    while (bit_pos > 7) {
        bit_pos -= 8;
        byte_pos++;
    }

    /* Om positionen för byte är större än vad som ryms, avbryt */
    if (byte_pos >= DATA_BYTES_RESERVED) {
        return;
    }

    if (bit == 1) {
        /* Om biten är en 1:a, använd | (eller) */
        binary_data[byte_pos] = binary_data[byte_pos] | (1 << (7 - bit_pos));
    } else {
        /* Om biten är en 1:a, använd & (och) samt ~ (invertera) */
        binary_data[byte_pos] = binary_data[byte_pos] & ~(1 << (7 - bit_pos));
    }
}

void data_set_byte(const int byte_position, const int byte) {
    /* Om positionen för byte är större än vad som ryms, avbryt */
    if (byte_position >= DATA_BYTES_RESERVED) {
        return;
    }
    
    binary_data[byte_position] = byte;
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

void data_clear(void) {
    int i;
    for (i = 0; i < DATA_BYTES_RESERVED; i++) {
        binary_data[i] = 0;
    }
}
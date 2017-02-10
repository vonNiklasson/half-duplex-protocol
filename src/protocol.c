/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol.c
 */

#include "protocol.h"

/******************** Sending data functions ********************/

void initialize(void) {
    platform_delay_setup();
    platform_gpio_setup();

    /* Clears the data */
    data_clear(send_data, DATA_BYTES_RESERVED);
    data_clear(_settings, SETTINGS_BYTES_RESERVED);
    data_clear(_data_count, DATA_BYTES_COUNT_RESERVED);

    /* Sets the default values unless changed */
    bitrate = DEFAULT_BITRATE;
    half_duplex = DEFAULT_HALF_DUPLEX;
    debug = DEFAULT_DEBUG;
}

void transmit(void) {
    /* Setup the gpio & delay and pull gpio to low */
    platform_delay_pre_transfer(false);
    platform_gpio_pre_transfer(false);
    platform_gpio_set_low();

    /* Set the _data_count array to correct bits */
    unsigned char byte_count = _count_bytes_in_use(send_data, DATA_BYTES_RESERVED);
    data_set_byte(_data_count, DATA_BYTES_COUNT_RESERVED, 0, byte_count);

    /* Gets the delay per bit */
    int delay_per_bit = (int)(1000000.0 / (bitrate));

    /*** Starts transmitting below ***/

    /* Starts the bitrate initialization */
    int i;
    int j;
    char bit;

    for (i = 0; i < BITRATE_BITS_RESERVED; i++) {
        if (i % 2 == 0) {
            _set_gpio(1, delay_per_bit);
        } else {
            _set_gpio(0, delay_per_bit);
        }
    }

    /* Send the settings as increased bits */
    for (i = 0; i < SETTINGS_BYTES_RESERVED; i++) {
        for (j = 7; j >= 0; j--) {
            bit = (_settings[i] >> j) & 1;
            _set_gpio_with_increased_bit(bit, delay_per_bit);
        }
    }

    /* Send the number as increased bits of bytes that will be sent in the next step */
    for (i = 0; i < DATA_BYTES_COUNT_RESERVED; i++) {
        for (j = 7; j >= 0; j--) {
            bit = (byte_count >> j) & 1;
            _set_gpio_with_increased_bit(bit, delay_per_bit);
        }
    }

    /* Send the data as increased bits */
    for (i = 0; i < byte_count; i++) {
        for (j = 7; j >= 0; j--) {
            bit = (send_data[i] >> j) & 1;
            _set_gpio_with_increased_bit(bit, delay_per_bit);
        }
    }

    /* Sets the gpio to low after transmit */
    platform_gpio_set_low();
    platform_gpio_post_transfer(false);
    platform_delay_post_transfer(false);
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


/******************** Internal functions below ********************/

/* Counts the number of bytes that are used */
int _count_bytes_in_use(const unsigned char *data, const int length) {
    int i;
    for(i = length - 1; i >= 0; i--) {
        if (data[i] != 0) {
            return i + 1;
        }
    }
    return 0;
}

/* Takes one bit (or byte) and increases it with 1 and
 * returns the value of the offset from right */
int _get_increased_bit(char bit, const int offset) {
    bit = bit + 1;
    return (bit >> offset) & 1;
}

void _set_gpio(const char bit, const int delay) {
    if (bit == 1) {
        platform_gpio_set_high();
    } else {
        platform_gpio_set_low();
    }
    platform_delay(delay);
}

void _set_gpio_with_increased_bit(const char bit, const int delay) {
    char offset_bit;
    offset_bit = _get_increased_bit(bit, 1);
    _set_gpio(offset_bit, delay);
    offset_bit = _get_increased_bit(bit, 0);
    _set_gpio(offset_bit, delay);
}

int _divide_round_up(const int n, const int d) {
    return (n + (d - 1)) / d;
}

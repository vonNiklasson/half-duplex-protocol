/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol.c
 */

#include "protocol.h"

/******************** Internal functions declaration below ********************/

unsigned char _settings[SETTINGS_BYTES_RESERVED];
unsigned char _data_count[DATA_BYTES_COUNT_RESERVED];

int _count_bytes_in_use(const unsigned char *data, const int length);
int _get_increased_bit(char bit, const int offset);
void _transmit_to_gpio_with_increased_bit(const char bit, const int delay);
void _transmit_to_gpio(const char bit, const int delay);

int _divide_round_up(const int n, const int d);

void _transmit_bytes(const unsigned char *data, const int length, const int delay_per_bit);


/******************** Sending data functions ********************/

void hdp_initialize(void) {
    platform_delay_setup();
    platform_gpio_setup();

    /* Clears the data */
    hdp_data_clear(hdp_send_data, DATA_BYTES_RESERVED);
    hdp_data_clear(_settings, SETTINGS_BYTES_RESERVED);
    hdp_data_clear(_data_count, DATA_BYTES_COUNT_RESERVED);

    /* Sets the default values unless changed */
    hdp_bitrate = DEFAULT_BITRATE;
    hdp_half_duplex = DEFAULT_HALF_DUPLEX;
    hdp_debug = DEFAULT_DEBUG;
}

void hdp_transmit(void) {
    /* Setup the gpio & delay and pull gpio to low */
    platform_delay_pre_transfer(false);
    platform_gpio_pre_transfer(false);
    platform_gpio_set_low();

    /* Set the _data_count array to correct bits */
    unsigned char byte_count = _count_bytes_in_use(hdp_send_data, DATA_BYTES_RESERVED);
    hdp_data_set_byte(_data_count, DATA_BYTES_COUNT_RESERVED, 0, byte_count);

    /* Gets the delay per bit */
    int delay_per_bit = (int)(1000.0 / (hdp_bitrate));

    /*** Starts transmitting below ***/

    /* Starts the bitrate initialization */
    int i;

    for (i = 0; i < BITRATE_BITS_RESERVED; i++) {
        if (i % 2 == 0) {
            _transmit_to_gpio(1, delay_per_bit);
        } else {
            _transmit_to_gpio(0, delay_per_bit);
        }
    }

    /* Send the settings as increased bits */
    _transmit_bytes(_settings, SETTINGS_BYTES_RESERVED, delay_per_bit);

    /* Send the number as increased bits of bytes that will be sent in the next step */
    _transmit_bytes(&byte_count, 1, delay_per_bit);

    /* Send the data as increased bits */
    _transmit_bytes(hdp_send_data, byte_count, delay_per_bit);

    /* Sets the gpio to low after transmit */
    platform_gpio_set_low();
    platform_gpio_post_transfer(false);
    platform_delay_post_transfer(false);
}

int hdp_recieve(void) {
    return 0;
}


/******************** Modifying data array ********************/

void hdp_data_set_bit(unsigned char *data, const int length, const int bit_position, const int bit) {
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

void hdp_data_set_byte(unsigned char *data, const int length, const int byte_position, const int byte) {
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

void hdp_data_clear(unsigned char *data, const int length) {
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

void _transmit_to_gpio(const char bit, const int delay) {
    if (bit == 1) {
        platform_gpio_set_high();
    } else {
        platform_gpio_set_low();
    }
    platform_delay(delay);
}

void _transmit_to_gpio_with_increased_bit(const char bit, const int delay) {
    char offset_bit;
    offset_bit = _get_increased_bit(bit, 1);
    _transmit_to_gpio(offset_bit, delay);
    offset_bit = _get_increased_bit(bit, 0);
    _transmit_to_gpio(offset_bit, delay);
}

int _divide_round_up(const int n, const int d) {
    return (n + (d - 1)) / d;
}

void _transmit_bytes(const unsigned char *data, const int length, const int delay_per_bit) {
    char bit;
    int i, j;
    for (i = 0; i < length; i++) {
        for (j = 7; j >= 0; j--) {
            bit = (data[i] >> j) & 1;
            _transmit_to_gpio_with_increased_bit(bit, delay_per_bit);
        }
    }
}

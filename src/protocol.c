/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol.c
 */

#include "protocol.h"

/******************** Internal functions declaration below ********************/

/* Variables for sending */
unsigned char _send_settings[SETTINGS_BYTES_RESERVED];
unsigned char _send_data_count[DATA_BYTES_COUNT_RESERVED];

/* Variables for recieving */
int _recieve_delay_per_bit;
unsigned char _recieve_settings[SETTINGS_BYTES_RESERVED];
unsigned char _recieve_data_count[DATA_BYTES_COUNT_RESERVED];

int _count_bytes_in_use(const unsigned char *data, const int length);
int _get_increased_bit(unsigned char bit, const int offset);
void _transmit_to_gpio_with_increased_bit(const unsigned char bit, const int delay);
void _transmit_to_gpio(const unsigned char bit, const int delay);

int _divide_round_up(const int n, const int d);

void _transmit_bytes(const unsigned char *data, const int length, const int delay_per_bit);

unsigned char _read_byte(const int predelay, const int delay);
int _read_increased_bit(const int delay);

/******************** Sending data functions ********************/

void hdp_initialize(void) {
    platform_delay_setup();
    platform_gpio_setup();

    /* Clears the data */
    hdp_data_clear(hdp_send_data, DATA_BYTES_RESERVED);
    hdp_data_clear(_send_settings, SETTINGS_BYTES_RESERVED);
    hdp_data_clear(_send_data_count, DATA_BYTES_COUNT_RESERVED);

    hdp_data_clear(hdp_recieve_data, DATA_BYTES_RESERVED);
    hdp_data_clear(_recieve_settings, SETTINGS_BYTES_RESERVED);
    hdp_data_clear(_recieve_data_count, DATA_BYTES_COUNT_RESERVED);

    /* Sets the default values unless changed */
    hdp_bitrate = DEFAULT_BITRATE;
    hdp_half_duplex = DEFAULT_HALF_DUPLEX;

    _recieve_delay_per_bit = 0;
}

void hdp_transmit(void) {
    /* Setup the gpio & delay and pull gpio to low */
    platform_delay_pre_transfer(false);
    platform_gpio_pre_transfer(false);
    platform_gpio_set_low();

    /* Set the _send_data_count array to correct bits */
    unsigned char byte_count = _count_bytes_in_use(hdp_send_data, DATA_BYTES_RESERVED);
    hdp_data_set_byte(_send_data_count, DATA_BYTES_COUNT_RESERVED, 0, byte_count);

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
    _transmit_bytes(_send_settings, SETTINGS_BYTES_RESERVED, delay_per_bit);

    /* Send the number as increased bits of bytes that will be sent in the next step */
    _transmit_bytes(&byte_count, 1, delay_per_bit);

    /* Send the data as increased bits */
    _transmit_bytes(hdp_send_data, byte_count, delay_per_bit);

    /* Sets the gpio to low after transmit */
    platform_gpio_set_low();
    platform_gpio_post_transfer(false);
    platform_delay_post_transfer(false);
}

unsigned char hdp_recieve(void) {
    /* Setup the gpio & delay to low */
    platform_delay_pre_transfer(true);
    platform_gpio_pre_transfer(true);

    /* Resets the delay per bit */
    _recieve_delay_per_bit = 0;

    /* Sets local variables to determine the bitrate */
    int bitrate_previous_bit = 0;
    int i;

    if (DEBUG) { platform_debug("Waiting for first bit", 0); }
    /* Wait for the first bit before entering the loop to determine the bitrate */
    while (platform_gpio_read() == 0);

    for (i = 0; i < BITRATE_BITS_RESERVED - 1; i++) {
        /* Wait for the bit to change (or enter immediately if it's the first bit) */
        while (platform_gpio_read() != bitrate_previous_bit) {
            platform_delay(1); // Delay with 1 millisecond
            _recieve_delay_per_bit++;
        }
        //if (DEBUG) { platform_debug("Current delay", _recieve_delay_per_bit); }
        /* Inverts the bit */
        bitrate_previous_bit = !bitrate_previous_bit;
    }

    /* Calculate the avarage delay per bit */
    _recieve_delay_per_bit = _recieve_delay_per_bit / (BITRATE_BITS_RESERVED - 1);

    _recieve_delay_per_bit = (1000/_recieve_delay_per_bit);
    _recieve_delay_per_bit = 1000 / _recieve_delay_per_bit;

    if (DEBUG) { platform_debug("Delay per bit", _recieve_delay_per_bit); }
    if (DEBUG) { platform_debug("Bitrate", (1000/_recieve_delay_per_bit)); }

    /* Start reading bits from the transmitted data  below */
    platform_delay(_recieve_delay_per_bit);
    platform_delay(_recieve_delay_per_bit / 2);
    unsigned char val;
    for (i = 0; i < 7; i++) {
        val = _read_byte(0, _recieve_delay_per_bit);
        if (DEBUG) { platform_debug("Byte", val); }
    }

    /* Desetup the gpio & delay to low */
    platform_gpio_post_transfer(true);
    platform_delay_post_transfer(true);

    return val;
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
int _get_increased_bit(unsigned char bit, const int offset) {
    bit = bit + 1;
    return (bit >> offset) & 1;
}

void _transmit_to_gpio(const unsigned char bit, const int delay) {
    if (bit == 1) {
        platform_gpio_set_high();
    } else {
        platform_gpio_set_low();
    }
    platform_delay(delay);
}

void _transmit_to_gpio_with_increased_bit(const unsigned char bit, const int delay) {
    unsigned char offset_bit;
    offset_bit = _get_increased_bit(bit, 1);
    _transmit_to_gpio(offset_bit, delay);
    offset_bit = _get_increased_bit(bit, 0);
    _transmit_to_gpio(offset_bit, delay);
}

int _divide_round_up(const int n, const int d) {
    return (n + (d - 1)) / d;
}

void _transmit_bytes(const unsigned char *data, const int length, const int delay_per_bit) {
    unsigned char bit;
    int i, j;
    for (i = 0; i < length; i++) {
        for (j = 7; j >= 0; j--) {
            bit = (data[i] >> j) & 1;
            _transmit_to_gpio_with_increased_bit(bit, delay_per_bit);
        }
    }
}

unsigned char _read_byte(const int predelay, const int delay) {
    if (predelay) {
        platform_delay(predelay);
    }
    unsigned char r = 0;
    int i;
    for (i = 7; i >= 0; i--) {
        r |= _read_increased_bit(delay) << i;
        /* Wait further */
        platform_delay(delay);
    }
    return r;
}

int _read_increased_bit(const int delay) {
    int bit = 0;
    /* Read first bit, but multiply by 2 */
    bit += (platform_gpio_read() << 1);
    platform_delay(delay);
    /* Read next bit as normal */
    bit += platform_gpio_read();
    /* Subtract 1 from the bit */
    if (DEBUG) { platform_debug("Bit set to ", bit - 1); }
    return bit - 1;
}
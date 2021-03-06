/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol.c
 */

#include "protocol.h"

/******************** Internal functions declaration below ********************/

/* List of valid bitrates */
int _bitrates[16] = { 1, 2, 4, 5, 8, 10, 20, 25, 40, 50, 100, 125, 200, 250, 500, 1000 };

/* Variables for sending */
unsigned char _send_settings[SETTINGS_BYTES_RESERVED];
unsigned char _send_data_count[DATA_BYTES_COUNT_RESERVED];

/* Variables for recieving */
int _recieve_delay_per_bit;
unsigned char _recieve_settings[SETTINGS_BYTES_RESERVED];
unsigned char _recieve_data_count[DATA_BYTES_COUNT_RESERVED];

int _count_bytes_in_use(const unsigned char *data, const int length);
int _abs(int number);
int _get_increased_bit(unsigned char bit, const int offset);
void _transmit_to_gpio_with_increased_bit(const unsigned char bit, const int delay);
void _transmit_to_gpio(const unsigned char bit, const int delay);

int _divide_round_up(const int n, const int d);

void _transmit_bytes(const unsigned char *data, const int length, const int delay_per_bit);

unsigned char _read_byte(const int delay);
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
    int delay_per_bit = (int)((float)BITRATE_BASE / (hdp_bitrate));

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
    float temp_delay = 0;
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
            platform_delay(1); // Delay with 2 milliseconds
            temp_delay += 1;
        }
        /* Inverts the bit */
        bitrate_previous_bit = !bitrate_previous_bit;
    }

    /* Calculate the avarage delay per bit */
    if (DEBUG) { platform_debug("Total delay", temp_delay); }

    temp_delay = temp_delay / (BITRATE_BITS_RESERVED - 1);

    if (DEBUG) { platform_debug("Avarage delay", temp_delay); }

    int assumed_bitrate = hdp_get_nearest_bitrate((float)BITRATE_BASE / temp_delay);
    int assumed_delay = hdp_get_nearest_delay(temp_delay);

    if (DEBUG) { platform_debug("Assumed bitrate", assumed_bitrate); }
    if (DEBUG) { platform_debug("Assumed delay", assumed_delay); }

    _recieve_delay_per_bit = assumed_delay;

    /* Start reading bits from the transmitted data  below */
    platform_delay(_recieve_delay_per_bit);
    unsigned char temp_byte;

    /* Read settings */
    for (i = 0; i < SETTINGS_BYTES_RESERVED; i++) {
        temp_byte = _read_byte(_recieve_delay_per_bit);
        /* Do a validity check here */
        _recieve_settings[i] = temp_byte;
    }

    /* Get byte count */
    for (i = 0; i < DATA_BYTES_COUNT_RESERVED; i++) {
        temp_byte = _read_byte(_recieve_delay_per_bit);
        /* Do a validity check here too */
        _recieve_data_count[i] = temp_byte;
    }

    if (DEBUG) { platform_debug("Byte count", _recieve_data_count[0]); }

    /* Read the actual data */
    for (i = 0; i < _recieve_data_count[0]; i++) {
        temp_byte = _read_byte(_recieve_delay_per_bit);
        /* Do a validity check here too */
        hdp_recieve_data[i] = temp_byte;
        if (DEBUG) { platform_debug("Byte", temp_byte); }
    }

    /* Desetup the gpio & delay to low */
    platform_gpio_post_transfer(true);
    platform_delay_post_transfer(true);

    return 1;
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

void hdp_data_clear(unsigned char *data, const int length) {
    int i;
    for (i = 0; i < length; i++) {
        *(data + i) = 0;
    }
}

/* Gets the closest bitrate from input bitrate */
int hdp_get_nearest_bitrate(const float bitrate) {
    float tempDistance = _abs(_bitrates[0] - bitrate);
    float newDistance;
    int k = 0;
    int i;
    for(i = 1; i < sizeof(_bitrates)/sizeof(_bitrates[0]); i++){
        newDistance = _abs(_bitrates[i] - bitrate);
        if(newDistance < tempDistance){
            k = i;
            tempDistance = newDistance;
        }
    }
    return _bitrates[k];
}

/* Gets the closest delay from accepted bitrate */
int hdp_get_nearest_delay(const float delay) {
    /* Since the array is mirrored for use of a bitrate under 1MHz or less,
     * nearest bitrate works for nearest delay too */
    return (int)hdp_get_nearest_bitrate(delay);
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

/* Return the absolute value */
int _abs(int number) {
    int const mask = number >> ((sizeof(int) * 8) - 1);
    return (number + mask) ^ mask;
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

unsigned char _read_byte(const int delay) {
    unsigned char r = 0;
    int i;
    for (i = 7; i >= 0; i--) {
        r |= _read_increased_bit(delay) << i;
        /* Wait further */
        platform_delay_or_gpio_change(delay);
    }
    return r;
}

int _read_increased_bit(const int delay) {
    int bit = 0;
    /* Read first bit, but multiply by 2 */
    bit += (platform_gpio_read() << 1);
    platform_delay_or_gpio_change(delay);
    /* Read next bit as normal */
    bit += platform_gpio_read();
    /* Subtract 1 from the bit */
    return bit - 1;
}

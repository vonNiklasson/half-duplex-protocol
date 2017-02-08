/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: convert.c
 */

#include "convert.h"

#include <string.h>

#include "functions.h"
#include "global.h"

/* Converting data into binary */

unsigned char* convert_bits_to_binary(char* data_bits, int* binary_length) {
    // Number of characters that will be used
    int req_char_count = divide_round_up(strlen(data_bits), 8);
    static unsigned char binary[DATA_BYTES_RESERVED];

    int i;               // Keeps track of outer loop
    int j;               // Keeps track of inner loop
    int bit_counter = 0; // Keeps track of the data bits
    int val;             // Holds the value of the current bit

    // Loops through the required characters
    for (i = 0; i < req_char_count; i++) {
        binary[i] = 0;
        // Loops through the bits in each character in arg data_bits
        for (j = 7; j >= 0; j--) {

            val = 0; // Sets default value to 0
            // Make sure we don't try to access data outside the input data
            if (bit_counter < strlen(data_bits)) {
                // Check if the value is 1, will otherwise default to 0
                if (data_bits[bit_counter] == 0x31) {
                    val = 1;
                }
                bit_counter++;
            }
            // Starts at the highest bit position and work down to 0
            // and writes the value to binary
            binary[i] = binary[i] | val << j;
        }
    }

    *binary_length = req_char_count;
    // Returns the binary data
    return binary;
}

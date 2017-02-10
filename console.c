/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: main.c
 */

#include <stdio.h>
#include "src/protocol.h"

int main(int argc, char *argv[])
{
    initialize();

    bitrate = 10;
    data_set_byte(send_data, DATA_BYTES_RESERVED, 0, 'j');
    data_set_byte(send_data, DATA_BYTES_RESERVED, 1, 'o');
    data_set_byte(send_data, DATA_BYTES_RESERVED, 2, 'h');
    data_set_byte(send_data, DATA_BYTES_RESERVED, 3, 'a');
    data_set_byte(send_data, DATA_BYTES_RESERVED, 4, 'n');
    transmit();

    return 0;
}

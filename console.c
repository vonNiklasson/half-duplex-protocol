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
    int transmit = 0;

    hdp_initialize();

    if (transmit) {
        hdp_bitrate = 10;

        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 0, 'j');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 1, 'o');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 2, 'h');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 3, 'a');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 4, 'n');

        hdp_transmit();

    } else {
        unsigned char c = hdp_recieve();
        printf("Value: %c\n", c);
    }


    return 0;
}

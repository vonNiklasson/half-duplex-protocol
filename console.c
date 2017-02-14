/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: main.c
 */

#include <stdio.h>
#include "src/protocol.h"

int round_up_to_max_pow10(int n);
int main(int argc, char *argv[])
{
    int transmit = 0;

    hdp_initialize();

    if (transmit) {
        hdp_bitrate = hdp_get_nearest_bitrate(500);

        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 0, 'j');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 1, 'o');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 2, 'h');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 3, 'a');
        hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 4, 'n');

        hdp_transmit();

    } else {
        hdp_recieve();
        printf("Value: %s\n", hdp_recieve_data);
    }


    return 0;
}
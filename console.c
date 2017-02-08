/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: main.c
 */

#include <stdio.h>
#include "src/communication.h"

int main(int argc, char *argv[])
{
    bitrate = 10;
    data_set_byte(send_data, DATA_BYTES_RESERVED, 0, 0x15);
    transmit();

    return 0;
}

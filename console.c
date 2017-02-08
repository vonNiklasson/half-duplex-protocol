/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: main.c
 */

#include <stdio.h>
#include "src/global.h"
#include "src/functions.h"
#include "src/communication.h"

int main(int argc, char *argv[])
{
    data_set_byte(1, 512);
    printf("Reading value om pos %d: %d\n\n", 0, binary_data[0]);
    printf("Reading value om pos %d: %d\n\n", 1, binary_data[1]);

    return 0;
}

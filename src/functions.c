/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/functions.c
 */

#include "functions.h"

int divide_round_up(const int n, const int d) {
    return (n + (d - 1)) / d;
}

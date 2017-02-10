/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: protocol_platform.h
 */

#ifndef PROTOCOL_PLATFORM_H_INCLUDED
#define PROTOCOL_PLATFORM_H_INCLUDED

#include <stdbool.h>

void platform_delay_setup();
void platform_delay_pre_transfer(bool recieve);
void platform_delay_post_transfer(bool recieve);
void platform_delay(int microseconds);

void platform_gpio_setup(void);
void platform_gpio_pre_transfer(bool recieve);
void platform_gpio_post_transfer(bool recieve);
void platform_gpio_set_high(void);
void platform_gpio_set_low(void);

int platform_gpio_read(void);

#endif
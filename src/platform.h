/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: platform.h
 */

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

void platform_delay_setup();
void platform_delay(int microseconds);

void platform_gpio_setup(void);
void platform_gpio_set_high(void);
void platform_gpio_set_low(void);

int platform_gpio_read(void);

#endif

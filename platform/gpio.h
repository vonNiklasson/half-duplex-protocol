/*
 * Name: <Your name here>
 * Project: Half duplex protocol
 *
 * Source: platform/gpio.h
 */

#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

int platform_gpio_setup(void);
int platform_gpio_set_high(void);
int platform_gpio_set_low(void);

#endif
/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol_platform_pic32mx.c
 */

#include "protocol_platform.h"
#include <pic32mx.h>

/******************** Delay functions below ********************/

#define TMR2PERIOD ((80000000 / 64) / 1000)
#if TMR2PERIOD > 0xffff
#error "Timer period is too big."
#endif

/* Define a delay setup here (will be called when protocol inits, may be more than once) */
void platform_delay_setup() {
  /* Set the prescaling to 64:1
   * bit 4-6 decides the prescaling
   * 0x60 == 01100000 */
    T2CON = 0x60;
    /* Count from 0 */
    TMR2 = 0x00;
    /* Count to period set above */
    PR2 = TMR2PERIOD;
}

/* Define a delay pre transfer here (will be called before transfer starts)
 * recieve: false=sending data, true=recieving data */
void platform_delay_pre_transfer(const bool recieve) {
    /* Starts Timer 2 */
    T2CONSET = 0x8000;
    return;
}

/* Define a delay post transfer here (will be called after transfer is done)
 * recieve: false=sending data, true=recieving data */
void platform_delay_post_transfer(const bool recieve) {
    /* Stops Timer 2 */
    T2CONCLR = 0x8000;
    return;
}

/* Define a delay here */
void platform_delay(const int milliseconds) {
    int i;
    for (i = 0; i < milliseconds; i++) {
        while ((IFS(0) & 0x100) == 0);
        IFSCLR(0) = 0x100;
    }
    return;
}


/******************** GPIO functions below ********************/

/* Setup gpio ports here */
void platform_gpio_setup(void) {
    /* Set GPIO 26 (also LED) to output */
    TRISECLR = 0x1;
    PORTECLR = 0x1;
    /* Set the buttons to input */
    TRISDSET = 0x800;
    return;
}

/* Define a gpio pre transfer here (will be called before transfer starts)
 * recieve: false=sending data, true=recieving data */
void platform_gpio_pre_transfer(const bool recieve) {
    return;
}

/* Define a gpio post transfer here (will be called after transfer is done)
 * recieve: false=sending data, true=recieving data */
void platform_gpio_post_transfer(const bool recieve) {
    return;
}

/* Doesn't need modification */
void platform_gpio_set(int state) {
    if (state) {
        platform_gpio_set_high();
    } else {
        platform_gpio_set_low();
    }
}

/* Setup procedure on gpio high here */
void platform_gpio_set_high(void) {
    PORTESET = 1;
    return;
}

/* Setup procedure on gpio low here */
void platform_gpio_set_low(void) {
    PORTECLR = 1;
    return;
}


/* Setup procedure on reading the gpio here */
int platform_gpio_read(void) {
    return (PORTD >> 5) & 0x7;
}


/******************** DEBUG functions below ********************/

/* Setup eventual function to debug */
void platform_debug(char *str, char val) {
    return;
}

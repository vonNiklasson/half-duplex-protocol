/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol_platform_console.c
 */

#include <stdio.h>
#include "protocol_platform.h"

/******************** Delay functions below ********************/

/* Define a delay setup here (will be called when protocol inits, may be more than once) */
void platform_delay_setup() {
    return;
}

/* Define a delay pre transfer here (will be called before transfer starts)
 * recieve: false=sending data, true=recieving data */
void platform_delay_pre_transfer(const bool recieve) {
    return;
}

/* Define a delay post transfer here (will be called after transfer is done)
 * recieve: false=sending data, true=recieving data */
void platform_delay_post_transfer(const bool recieve) {
    return;
}

/* Define a delay here */
void platform_delay(const int milliseconds) {
    /* Dummy function here */
    int i, j, k;
    for(i = 0; i < milliseconds; i++)
    {
        for(j = 0; j < 800; j++)
        {
            for(k = 0; k < 635; k++)
            {
               // waste function, volatile makes sure it is not being optimized out by compiler
                int volatile t = 120 * j * i + k;
                t = t + 5;
            }
        }
    }
}


/******************** GPIO functions below ********************/

/* Setup gpio ports here */
void platform_gpio_setup(void) {
    setbuf(stdout, NULL);
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

/* Setup procedure on gpio high here */
void platform_gpio_set_high(void) {
    printf("1");
}

/* Setup procedure on gpio low here */
void platform_gpio_set_low(void) {
    printf("0");
}


/* Setup procedure on reading the gpio here */
int platform_gpio_read(void) {
    return 0;
}

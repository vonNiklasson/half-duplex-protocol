/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/platform.c
 */

#include <stdio.h>
#include "platform.h"

/* Define a delay setup here */
void platform_delay_setup() {

}

/* Define a delay here */
void platform_delay(int microseconds) {
    /* Dummy function here */
    int i, j, k;
    for(i = 0; i < microseconds; i++)
    {
        for(j = 0; j < 8; j++)
        {
            for(k = 0; k < 60; k++)
            {
               // waste function, volatile makes sure it is not being optimized out by compiler
                int volatile t = 120 * j * i + k;
                t = t + 5;
            }
        }
    }
}


/* Setup gpio ports here */
void platform_gpio_setup(void) {
    setbuf(stdout, NULL);
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

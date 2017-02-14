/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol_platform_template.c
 */

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
    return;
}

/* Define a delay here that also check for state change on the gpio input port */
void platform_delay_or_gpio_change(const int milliseconds) {
    int initial_state = platform_gpio_read();
    int i;
    for (i = 0; i < milliseconds; i++) {
        platform_delay(1);
        if (initial_state != platform_gpio_read()) {
            return;
        }
    }
    return;
}


/******************** GPIO functions below ********************/

/* Setup gpio ports here */
void platform_gpio_setup(void) {
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
void platform_gpio_set(const int state) {
    if (state) {
        platform_gpio_set_high();
    } else {
        platform_gpio_set_low();
    }
}

/* Setup procedure on gpio high here */
void platform_gpio_set_high(void) {
    return;
}

/* Setup procedure on gpio low here */
void platform_gpio_set_low(void) {
    return;
}


/* Setup procedure on reading the gpio here */
int platform_gpio_read(void) {
    return 0;
}


/******************** DEBUG functions below ********************/

/* Setup eventual function to debug */
void platform_debug(const char *str, const int val) {
    return;
}

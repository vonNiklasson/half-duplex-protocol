/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: src/protocol_platform_wiringpi.c
 */

#include "protocol_platform.h"
#include <wiringPi.h>

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
    delay(milliseconds);
    return;
}


/******************** GPIO functions below ********************/

/* Wiring Pi uses another pin number system than BCM.
 * A guide can be found here:
 * http://pinout.xyz/pinout/
 */
int INPUT_PIN = 7; // BCM Input 4
int OUTPUT_PIN = 0; // BCM Input 17

/* Setup gpio ports here */
void platform_gpio_setup(void) {
    wiringPiSetup();    
}

/* Define a gpio pre transfer here (will be called before transfer starts)
 * recieve: false=sending data, true=recieving data */
void platform_gpio_pre_transfer(const bool recieve) {
    pinMode(INPUT_PIN, INPUT);
    pinMode(OUTPUT_PIN, OUTPUT);
}

/* Define a gpio post transfer here (will be called after transfer is done)
 * recieve: false=sending data, true=recieving data */
void platform_gpio_post_transfer(const bool recieve) {
    return;
}

/* Setup procedure on gpio high here */
void platform_gpio_set_high(void) {
    digitalWrite(OUTPUT_PIN, 1);
}

/* Setup procedure on gpio low here */
void platform_gpio_set_low(void) {
    digitalWrite(OUTPUT_PIN, 0);
}


/* Setup procedure on reading the gpio here */
int platform_gpio_read(void) {
    return digitalRead(INPUT_PIN);
}

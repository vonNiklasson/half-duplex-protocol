/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: global.h
 */

/* Version specific values below */

/* Version of the protocol */
#define PROTOCOL_VERSION "0.1"

/* Number of bytes that can me transmitted */
#define DATA_BYTES_RESERVED 32
/* Number of bytes reserved for settings data */
#define DATA_SETTINGS_BYTES_RESERVED 2
/* Number of bytes reserved to tell how many bytes will be transmitted 
 * (Must be related with DATA_BYTES_RESERVED) */
#define DATA_BYTES_COUNT_RESERVED 1
/* Number of bytes that can me transmitted */
#define DATA_HANDSHAKE_BITS_RESERVED 4

/* Default values below */

/* The default frequency if no frequency is given */
#define DEFAULT_TRANSMIT_FREQUENCY 100
/* The default value of the transmission will expect to get feedback 
 * 0=Simplex, 1=Half duplex */
#define DEFAULT_EXPECT_HALF_DUPLEX 0

/* Wether to show debug messages or not */
#define DEFAULT_DEBUG 0
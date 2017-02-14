# half-duplex-protocol
A digital communication protocol, using a one output for sending data, and an input for receiving data.

More info coming soon.

## Bitrate/Frequency
At the current state the protocol can only read 500hz to 1MHz (depending on how precise the timers on the device can be). This is because the program uses milliseconds as base time. May be upgraded in the future.

## Usage

### Send data

```c
#include "protocol.h"
...
hdp_initialize();

/* You can set a bitrate manually but it's 
 * prefered to use this in case more bitrates get added */
hdp_bitrate = hdp_get_nearest_bitrate(500);

hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 0, 'h');
hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 1, 'e');
hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 2, 'l');
hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 3, 'l');
hdp_data_set_byte(hdp_send_data, DATA_BYTES_RESERVED, 4, 'o');

hdp_transmit();
```

You can also modify `hdp_send_data` directly or use `hdp_data_set_bit` where you can set bits through the entire transmit data. e.g.
```c
/* Set bit index 43 (from left) to 1. 
 * Also bit no 5 (from least significatnt bit) in byte no 5 */
hdp_data_set_bit(hdp_send_data, DATA_BYTES_RESERVED, 43, 1);
```

### Recieve data
To recieve data, the code below can be used:

```c
#include "protocol.h"
...
hdp_initialize();
hdp_recieve();
printf("Data: %s\n", hdp_recieve_data);
```

The code will stall until it gets a response. A timeout timer may be added in the future.

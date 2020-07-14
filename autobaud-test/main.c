/* Wirepas Oy licensed under Apache License, Version 2.0
 *
 * See file LICENSE for full license details.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "wpc.h"

#define LOG_MODULE_NAME "Main"
#define MAX_LOG_LEVEL INFO_LOG_LEVEL
#include "logger.h"

// Default serial port
char * port_name = "/dev/ttyACM0";

int main(int argc, char * argv[])
{
    unsigned long bitrate = DEFAULT_BITRATE;

    if (argc > 1)
    {
        port_name = argv[1];
    }

    if (argc > 2)
    {
        bitrate = strtoul(argv[2], NULL, 0);
    }

    if (WPC_initialize(port_name, 115200) == APP_RES_OK)
    {
        LOGI("Found baud rate 115200\n");
        return 115200;
    }
    else if (WPC_initialize(port_name, 125000) == APP_RES_OK)
    {
        LOGI("Found baud rate 125000\n");
        return 125000;
    }
    else if (WPC_initialize(port_name, 1000000) == APP_RES_OK)
    {
        LOGI("Found baud rate 1000000\n");
        return 1000000;
    }
    else if (WPC_initialize(port_name, bitrate) == APP_RES_OK) //Tries 115200 again if this was not set
    {
        LOGI("Found baud rate %lu\n", bitrate);
        return bitrate;
    }
    else
    {
        LOGE("No baud rate found.\n");
        return -1;
    }

}

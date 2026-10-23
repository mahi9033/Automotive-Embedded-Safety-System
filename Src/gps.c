#include "gps.h"

uint8_t gps_data[100];
uint8_t gps_index = 0;
volatile uint8_t gps_ready = 0;

void gps_buffer(uint8_t data)
{
    if (gps_ready) return;

    if (data == '$')
        gps_index = 0;

    if (gps_index < 99)
        gps_data[gps_index++] = data;
    else
        gps_index = 0;

    if (data == '\n')
    {
        gps_data[gps_index] = '\0';
        gps_index = 0;
        gps_ready = 1;
    }
}

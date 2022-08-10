#ifndef __HSC_PRESSURE_H
#define __HSC_PRESSURE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define HSC_PRESSURE_ADDR               0x28

#define PRESSURE_SENSOR_MAX_PRESSURE    15.0f         // This is depending on the sensor you use (this one was a differential sensor -1 -> +1PSI)
#define PRESSURE_SENSOR_MIN_PRESSURE    -15.0f        // This is depending on the sensor you use (this one was a differential sensor -1 -> +1PSI)
#define PRESSURE_SENSOR_MIN_COUNTS      1638.0f      // 10% of the total counts the sensor can give - ie, they only promise accuracy in a 80% window
#define PRESSURE_SENSOR_MAX_COUNTS      14745.0f     // 90% of the total counts the sensor can give - ie, they only promise accuracy in a 80% window


void hsc_read_pressure (float* pressure);


#ifdef __cplusplus
}
#endif

#endif 


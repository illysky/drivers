
// C Standard
#include <stdint.h>
#include <string.h>

#include "nrf_log.h"

#include "hsc_pressure.h"
#include "hal.h"

// Pressure Sensor is on I2C0
// Address: HSC_PRESSURE_ADDR = 0x28
#define HAL_I2C     0

void hsc_read_pressure (float* pressure)
{
	NRF_LOG_INFO("Pressure read");
	uint8_t buf[4] = {0}; 

    // Read 4 bytes (oh look! - an example of i2c not needing to set address before reading!)
	int32_t result = hal_i2c_read (HAL_I2C, HSC_PRESSURE_ADDR, buf, 4);
	if (result != 0) {
		NRF_LOG_INFO("We have a problem!");
	}     	

    // Endian! with I2C it is usually MSB first so we need to swap the byte order for this raw variable (int16_t),
	int16_t counts = ((uint16_t) buf[1]); 	    // i2c MSB -> counts LSB 
	counts |= ((uint16_t) buf[0]) << 8; 		// i2c LSB -> counts MSB
	counts &= counts & 0x3FFF; 					// Mask off because some bits from sensor we dont need. 

	// Lets convert the sensor reading to PSI (from datasheet)
    float raw_pressure = (((((float)counts) - PRESSURE_SENSOR_MIN_COUNTS) * (PRESSURE_SENSOR_MAX_PRESSURE - (PRESSURE_SENSOR_MIN_PRESSURE))) / (PRESSURE_SENSOR_MAX_COUNTS - PRESSURE_SENSOR_MIN_COUNTS)) + (PRESSURE_SENSOR_MIN_PRESSURE); 
	
    // Lets convert the PSI for the ME engineers at Chiaro (mmHg) ;) 
    raw_pressure *= 51.7149; 
	
	// yes, fecking pointers - I know you want to pass back pressure as the return variable, but nah... save this for status feedback
	*pressure = raw_pressure; // Here we move our working register into our pointer 
} 
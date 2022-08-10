/************************************************************************************************************************************* 
 * @file  	
 * @brief 	
 *************************************************************************************************************************************/
#include "aw9110.h" 
#include "hal.h"

static uint8_t device = 0x00; 
static uint8_t instance = 0x00; 

/************************************************************************************** 
 * @brief	
 * 	
 **************************************************************************************/
int32_t aw9110btqr_init (uint8_t i2c, uint8_t addr) 
{
    int32_t result = 0;
    uint8_t dummy; 
    device = addr;                          // Set I2C address
    instance = i2c; 
    result = hal_i2c_write (instance, device, &dummy, 1, false);
    return result; 
}

/************************************************************************************** 
 * @brief	
 * 	
 **************************************************************************************/
int32_t aw9110btqr_write_reg (uint8_t reg, uint8_t value) 
{
	uint8_t buf[3]; 
    int32_t result = 0;
	buf[0] = reg; 
	buf[1] = value; 
	result = hal_i2c_write (instance, device, buf, 2, false); 
    return result; 
}





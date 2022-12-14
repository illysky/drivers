/************************************************************************************************************************************* 
 * @file  	
 * @brief 	
 *************************************************************************************************************************************/
#include "mcp4728.h" 
#include "hal.h"
 
// DAC is on I2C0
// Address: MCP4728_DFLT_ADDR = 0x60
#define HAL_I2C   0

/************************************************************************************** 
 * @brief	
 * 	
 **************************************************************************************/
int32_t mcp4728_init (uint8_t i2c, uint8_t device) 
{
    uint8_t buf=0;
    
    return hal_i2c_read (i2c, device, &buf, 1); 
}

/************************************************************************************** 
 * @brief	
 * 	
 **************************************************************************************/
int32_t mcp4728_config_channel (uint8_t i2c, uint8_t device, uint8_t channel, uint8_t vref, uint8_t gain, uint8_t pd, uint16_t value) 
{
    uint8_t buf[3];

    value = value & 0x0FFF;  
    
    buf[0] = (MCP4728_CMD_INPUT<<5) | (MCP4728_CMD_WR_MULTI<<3) | (channel<<1) | MCP4728_UDAC_LATCH; 
    buf[1] = (vref<<7) | (pd<<5) | (gain<<4) | ((value >> 8) & 0x0F); 
    buf[2] = (value & 0xFF); 
    
    return hal_i2c_write (i2c, device, buf, 3, false); 
}

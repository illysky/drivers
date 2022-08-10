/************************************************************************************************************************************* 
 * @file  	
 * @brief 	
 *************************************************************************************************************************************/
#ifndef PCAL6416_H
#define PCAL6416_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define PCAL6416_ADDR               0x21

#define PCAL6416_REG_IN_P0          0x00
#define PCAL6416_REG_IN_P1          0x01
#define PCAL6416_REG_OUT_P0         0x02
#define PCAL6416_REG_OUT_P1         0x03
#define PCAL6416_REG_INV_P0         0x04
#define PCAL6416_REG_INV_P1         0x05
#define PCAL6416_REG_CONF_P0        0x06
#define PCAL6416_REG_CONF_P1        0x07
#define PCAL6416_REG_DRV0_P0        0x40
#define PCAL6416_REG_DRV1_P0        0x41
#define PCAL6416_REG_DRV0_P1        0x42
#define PCAL6416_REG_DRV1_P1        0x43
#define PCAL6416_REG_LAT0           0x44
#define PCAL6416_REG_LAT1           0x45
#define PCAL6416_REG_PUPD_EN_0      0x46
#define PCAL6416_REG_PUPD_EN_1      0x47
#define PCAL6416_REG_PUPD_SEL_0     0x48
#define PCAL6416_REG_PUPD_SEL_1     0x49
#define PCAL6416_REG_INTMASK0       0x4A
#define PCAL6416_REG_INTMASK1       0x4B
#define PCAL6416_REG_INTSTAT0       0x4C
#define PCAL6416_REG_INTSTAT1       0x4D
#define PCAL6416_REG_OUT_CONF       0x4F


// IO EXPANDER
// TMC
#define TMC_EN_2                0   // Port 0  Pin 0  
#define TMC_EN_1                1   // Port 0  Pin 1
#define TMC_EN_0                2   // Port 0  Pin 2

// Enable
#define SOL_EN                  4   // Port 0  Pin 4
#define MOTOR_EN                5   // Port 0  Pin 5
#define BOOST_EN                11   // Port 1  Pin 3

// LEDs
#define LED_R                   7   // Port 0  Pin 7
#define LED_G                   10   // Port 1  Pin 2


int32_t pcal6416_init (uint8_t i2c, uint8_t device); 
int32_t pcal6416_conf(uint8_t i2c, uint8_t device, uint16_t config); 
int32_t pcal6416_set_out(uint8_t i2c, uint8_t device, uint16_t out); 
int32_t pcal6416_get_out(uint8_t i2c, uint8_t device, uint16_t* out); 
int32_t pcal6416_write_gpio(uint8_t i2c, uint8_t device, uint8_t bit, uint8_t value); 

#ifdef __cplusplus
}
#endif

#endif //MCP4728_H
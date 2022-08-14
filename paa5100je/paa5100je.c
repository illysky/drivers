/********************************************************************************************************
* @file:			paa5100je.c
* @overview:		A driver file for PAA5100JE
* @date:			08/11/2022 14:33:55
* @author:		    Illysky CodeCrafter v1.0.0
********************************************************************************************************/

/*** Typedefs ***/
#include "paa5100je.h"

/*** Variables ***/
static const uint8_t config_addr1[5] = {0x7F, 0x55, 0x50, 0x7F, 0x43};
static const uint8_t config_data1[5] = {0x00, 0x01, 0x07, 0x0E, 0x10};
static const uint8_t config_addr2[5] = {0x7F, 0x51, 0x50, 0x55, 0x7F};
static const uint8_t config_data2[5] = {0x00, 0x7B, 0x00, 0x00, 0x0E};
static const uint8_t config_addr3[67] = {0x7F, 0x61, 0x7F, 0x40, 0x7F, 0x41, 0x43, 0x45, 0x5F, 0x7B, 0x5E, 0x5B, 0x6D, 0x45, 0x70, 0x71, 0x7F, 0x44, 0x40, 0x4E, 0x7F, 0x66, 0x65, 0x6A, 0x61, 0x62, 0x7F, 0x4F, 0x5F, 0x48, 0x49, 0x57, 0x60, 0x61, 0x62, 0x63, 0x7F, 0x45, 0x7F, 0x4D, 0x55, 0x74, 0x75, 0x4A, 0x4B, 0x44, 0x45, 0x64, 0x65, 0x7F, 0x65, 0x66, 0x63, 0x6F, 0x7F, 0x48, 0x7F, 0x41, 0x43, 0x4B, 0x45, 0x44, 0x4C, 0x7F, 0x5B, 0x7F, 0x40};
static const uint8_t config_data3[67] = {0x00, 0xAD, 0x03, 0x00, 0x05, 0xB3, 0xF1, 0x14, 0x34, 0x08, 0x34, 0x11, 0x11, 0x17, 0xE5, 0xE5, 0x06, 0x1B, 0xBF, 0x3F, 0x08, 0x44, 0x20, 0x3A, 0x05, 0x05, 0x09, 0xAF, 0x40, 0x80, 0x80, 0x77, 0x78, 0x78, 0x08, 0x50, 0x0A, 0x60, 0x00, 0x11, 0x80, 0x21, 0x1F, 0x78, 0x78, 0x08, 0x50, 0xFF, 0x1F, 0x14, 0x67, 0x08, 0x70, 0x1C, 0x15, 0x48, 0x07, 0x0D, 0x14, 0x0E, 0x0F, 0x42, 0x80, 0x10, 0x02, 0x07, 0x41};
static const uint8_t config_addr4[16] = {0x7F, 0x32, 0x7F, 0x40, 0x7F, 0x68, 0x69, 0x7F, 0x48, 0x6F, 0x7F, 0x5B, 0x4E, 0x5A, 0x40, 0x73};
static const uint8_t config_data4[16] = {0x00, 0x00, 0x07, 0x40, 0x06, 0xF0, 0x00, 0x0D, 0xC0, 0xD5, 0x00, 0xA0, 0xA8, 0x90, 0x80, 0x1F};

static double m_cpi_coeffient[PAA5100JE_MAX_INSTANCE] = {0}; 
static bool m_instance_ready [PAA5100JE_MAX_INSTANCE] = {0}; 
/*** Functions ***/

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_PROD_ID register
********************************************************************************************************/
int32_t paa5100je_read_prod_id (uint32_t instance, paa5100je_prod_id_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_PROD_ID_ADDR, data, PAA5100JE_PROD_ID_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_REV_ID register
********************************************************************************************************/
int32_t paa5100je_read_rev_id (uint32_t instance, paa5100je_rev_id_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_REV_ID_ADDR, data, PAA5100JE_REV_ID_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_INV_PROD_ID register
********************************************************************************************************/
int32_t paa5100je_read_inv_prod_id (uint32_t instance, paa5100je_inv_prod_id_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_INV_PROD_ID_ADDR, data, PAA5100JE_INV_PROD_ID_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_MOTION register
********************************************************************************************************/
int32_t paa5100je_read_motion (uint32_t instance, paa5100je_motion_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_MOTION_ADDR, data, PAA5100JE_MOTION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_MOTION register
********************************************************************************************************/
int32_t paa5100je_write_motion (uint32_t instance, paa5100je_motion_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_MOTION_ADDR, data, PAA5100JE_MOTION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_DELTA_XL register
********************************************************************************************************/
int32_t paa5100je_read_delta_xl (uint32_t instance, paa5100je_delta_xl_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_DELTA_XL_ADDR, data, PAA5100JE_DELTA_XL_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_DELTA_XH register
********************************************************************************************************/
int32_t paa5100je_read_delta_xh (uint32_t instance, paa5100je_delta_xh_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_DELTA_XH_ADDR, data, PAA5100JE_DELTA_XH_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_DELTA_YL register
********************************************************************************************************/
int32_t paa5100je_read_delta_yl (uint32_t instance, paa5100je_delta_yl_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_DELTA_YL_ADDR, data, PAA5100JE_DELTA_YL_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_DELTA_YH register
********************************************************************************************************/
int32_t paa5100je_read_delta_yh (uint32_t instance, paa5100je_delta_yh_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_DELTA_YH_ADDR, data, PAA5100JE_DELTA_YH_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_SQUAL register
********************************************************************************************************/
int32_t paa5100je_read_squal (uint32_t instance, paa5100je_squal_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_SQUAL_ADDR, data, PAA5100JE_SQUAL_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_RAW_DATA_SUM register
********************************************************************************************************/
int32_t paa5100je_read_raw_data_sum (uint32_t instance, paa5100je_raw_data_sum_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_RAW_DATA_SUM_ADDR, data, PAA5100JE_RAW_DATA_SUM_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_MAXIMUM_RAWDATA register
********************************************************************************************************/
int32_t paa5100je_read_maximum_rawdata (uint32_t instance, paa5100je_maximum_rawdata_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_MAXIMUM_RAWDATA_ADDR, data, PAA5100JE_MAXIMUM_RAWDATA_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_MINIMUM_RAWDATA register
********************************************************************************************************/
int32_t paa5100je_read_minimum_rawdata (uint32_t instance, paa5100je_minimum_rawdata_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_MINIMUM_RAWDATA_ADDR, data, PAA5100JE_MINIMUM_RAWDATA_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_SHUTTER_L register
********************************************************************************************************/
int32_t paa5100je_read_shutter_l (uint32_t instance, paa5100je_shutter_l_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_SHUTTER_L_ADDR, data, PAA5100JE_SHUTTER_L_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_SHUTTER_H register
********************************************************************************************************/
int32_t paa5100je_read_shutter_h (uint32_t instance, paa5100je_shutter_h_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_SHUTTER_H_ADDR, data, PAA5100JE_SHUTTER_H_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_OBSERVATION register
********************************************************************************************************/
int32_t paa5100je_read_observation (uint32_t instance, paa5100je_observation_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_OBSERVATION_ADDR, data, PAA5100JE_OBSERVATION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_OBSERVATION register
********************************************************************************************************/
int32_t paa5100je_write_observation (uint32_t instance, paa5100je_observation_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_OBSERVATION_ADDR, data, PAA5100JE_OBSERVATION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_MOTION_BURST register
********************************************************************************************************/
int32_t paa5100je_read_motion_burst (uint32_t instance, paa5100je_motion_burst_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_MOTION_BURST_ADDR, data, PAA5100JE_MOTION_BURST_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_POWER_UP_RESET register
********************************************************************************************************/
int32_t paa5100je_write_power_up_reset (uint32_t instance, paa5100je_power_up_reset_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_POWER_UP_RESET_ADDR, data, PAA5100JE_POWER_UP_RESET_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_SHUTDOWN register
********************************************************************************************************/
int32_t paa5100je_write_shutdown (uint32_t instance, paa5100je_shutdown_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_SHUTDOWN_ADDR, data, PAA5100JE_SHUTDOWN_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_RESOLUTION register
********************************************************************************************************/
int32_t paa5100je_read_resolution (uint32_t instance, paa5100je_resolution_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_RESOLUTION_ADDR, data, PAA5100JE_RESOLUTION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_RESOLUTION register
********************************************************************************************************/
int32_t paa5100je_write_resolution (uint32_t instance, paa5100je_resolution_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_RESOLUTION_ADDR, data, PAA5100JE_RESOLUTION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_RAWDATA_GRAB register
********************************************************************************************************/
int32_t paa5100je_read_rawdata_grab (uint32_t instance, paa5100je_rawdata_grab_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_RAWDATA_GRAB_ADDR, data, PAA5100JE_RAWDATA_GRAB_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_RAWDATA_GRAB register
********************************************************************************************************/
int32_t paa5100je_write_rawdata_grab (uint32_t instance, paa5100je_rawdata_grab_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_RAWDATA_GRAB_ADDR, data, PAA5100JE_RAWDATA_GRAB_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_RAWDATA_GRAB_STATUS register
********************************************************************************************************/
int32_t paa5100je_read_rawdata_grab_status (uint32_t instance, paa5100je_rawdata_grab_status_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_RAWDATA_GRAB_STATUS_ADDR, data, PAA5100JE_RAWDATA_GRAB_STATUS_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_ORIENTATION register
********************************************************************************************************/
int32_t paa5100je_read_orientation (uint32_t instance, paa5100je_orientation_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_ORIENTATION_ADDR, data, PAA5100JE_ORIENTATION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_ORIENTATION register
********************************************************************************************************/
int32_t paa5100je_write_orientation (uint32_t instance, paa5100je_orientation_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_ORIENTATION_ADDR, data, PAA5100JE_ORIENTATION_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_TEST register
********************************************************************************************************/
int32_t paa5100je_read_test (uint32_t instance, paa5100je_test_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_TEST_ADDR, data, PAA5100JE_TEST_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_TEST register
********************************************************************************************************/
int32_t paa5100je_write_test (uint32_t instance, paa5100je_test_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_TEST_ADDR, data, PAA5100JE_TEST_SIZE);     
}

/********************************************************************************************************
* @overview: Function to read from PAA5100JE_LARGE register
********************************************************************************************************/
int32_t paa5100je_read_large (uint32_t instance, paa5100je_large_t* data)
{
    return paa5100je_reg_read (instance, PAA5100JE_LARGE_ADDR, data, PAA5100JE_LARGE_SIZE);     
}

/********************************************************************************************************
* @overview: Function to write to PAA5100JE_LARGE register
********************************************************************************************************/
int32_t paa5100je_write_large (uint32_t instance, paa5100je_large_t* data)
{
    return paa5100je_reg_write (instance, PAA5100JE_LARGE_ADDR, data, PAA5100JE_LARGE_SIZE);     
}


/********************************************************************************************************
* @overview: Stub to write to PAA5100JE
********************************************************************************************************/
int32_t paa5100je_reg_write (uint32_t instance, uint8_t addr, void* data, uint32_t size)
{
    // Stub to access the IC. Look, I can't do EVERYTHING for you, so you'll need to add some code here. SPI or I2C
    // instance: if you want more than one instance of the driver handle it here with this variable
    // addr: Address the register, this has been sized for you based on the width
    // data: treat the data as 8bit
    // size: size of data
    int32_t result = 0; 
    addr |= 0x80u; // Clear Write Flag
    hal_gpio_config_output(20,0); // CS 
    hal_delay_us(1); 
    result = hal_spi_transfer(instance, &addr, 1, NULL, 0); 
    result = hal_spi_transfer(instance, data, size, NULL, 0); 
    hal_delay_us(5); 
    hal_gpio_config_output(20,1); // CS 
    hal_delay_us(5); 

    return result; // Return 0 for good, or <0 for something bad.
}

/********************************************************************************************************
* @overview: Stub to read from PAA5100JE
********************************************************************************************************/
int32_t paa5100je_reg_read (uint32_t instance, uint8_t addr, void* data, uint32_t size)
{
    // Stub to access the IC. Look, I can't do EVERYTHING for you, so you'll need to add some code here. SPI or I2C
    // instance: if you want more than one instance of the driver handle it here with this variable
    // addr: Address the register, this has been sized for you based on the width
    // data: treat the data as 8bit
    // size: size of data
    int32_t result = 0; 
    addr &= ~0x80u; // Clear Write Flag
    hal_gpio_config_output(20,0); // CS 
    hal_delay_us(1); 
    result = hal_spi_transfer(instance, &addr, 1, NULL, 0); 
    hal_delay_us(5); 
    result = hal_spi_transfer(instance, NULL, 1, data, size); 
    hal_delay_us(1);
    hal_gpio_config_output(20,1); // CS 
    hal_delay_us(5); 
    return result; // Return 0 for good, or <0 for something bad.
}

/********************************************************************************************************
* @overview: 
********************************************************************************************************/
int32_t paa5100je_set_working_height (int32_t instance, double height)
{
    if (height < 12.5 || height > 37.5) return -1;
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1; 
    height /= 1000; // from mm to m
    m_cpi_coeffient[instance] = 11.914 * (1 / (height));     // PixArt approximation formula from height to CPI
    return 0; 
}

/********************************************************************************************************
* @overview: 
********************************************************************************************************/
int32_t paa5100je_set_resolution (int32_t instance, uint8_t resolution)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == false)  return -1; // Not initialised
    if (resolution >= 0xA8) resolution = 0xA8;
    paa5100je_resolution_t paa5100je_resolution = {.val = resolution}; 
    return paa5100je_write_resolution (instance, &paa5100je_resolution);
}

/********************************************************************************************************
* @overview: 
********************************************************************************************************/
int32_t paa5100je_set_orientation (int32_t instance, bool invert_x, bool invert_y, bool swap_xy)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == false)  return -1; // Not initialised
    
    uint8_t val = 0x00;

    if (invert_x)  val |= 0x20; 
    if (invert_y)  val |= 0x40; 
    if (swap_xy)   val |= 0x80; 

    paa5100je_orientation_t paa5100je_orientation = {val = val}; 
    return paa5100je_write_orientation (instance, &paa5100je_orientation);
}

/********************************************************************************************************
* @overview: 
********************************************************************************************************/
int32_t paa5100je_get_surface_quality (int32_t instance, int32_t* sq)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == false)  return -1; // Not initialised

    paa5100je_squal_t paa5100je_squal = {0}; 
    int32_t result = 0; 
    result = paa5100je_read_squal (instance, &paa5100je_squal);
    *sq = paa5100je_squal.val * 4; 
    return result; 
}

/********************************************************************************************************
* @overview: 
********************************************************************************************************/
int32_t paa5100je_get_observation (int32_t instance, uint8_t* observation)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == false)  return -1; // Not initialised
    
    int32_t result = 0; 
    paa5100je_observation_t paa5100je_observation = {0}; 
    result = paa5100je_read_observation (instance, &paa5100je_observation);
    *observation = paa5100je_observation.val;
    return result; 
}

/********************************************************************************************************
* @overview: 
********************************************************************************************************/
int32_t paa5100je_get_motion (int32_t instance, int16_t* delta_x, int16_t* delta_y)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == false)  return -1; // Not initialised
   
    paa5100je_motion_t paa5100je_motion = {0}; 
    paa5100je_read_motion (instance, &paa5100je_motion); 
    paa5100je_motion.val &= 0x80; 
    if (paa5100je_motion.val != 0x80)
    {   
        *delta_x = 0; 
        *delta_y = 0; 
        return 0;       // Not motion, but all good.    
    } 
    else 
    {
        paa5100je_delta_xl_t paa5100je_delta_xl = {0};      paa5100je_read_delta_xl (instance, &paa5100je_delta_xl); 
        paa5100je_delta_xh_t paa5100je_delta_xh = {0};      paa5100je_read_delta_xh (instance, &paa5100je_delta_xh); 
        paa5100je_delta_yl_t paa5100je_delta_yl = {0};      paa5100je_read_delta_yl (instance, &paa5100je_delta_yl); 
        paa5100je_delta_yh_t paa5100je_delta_yh = {0};      paa5100je_read_delta_yh (instance, &paa5100je_delta_yh); 
        paa5100je_squal_t    paa5100je_squal =    {0};      paa5100je_read_squal (instance, &paa5100je_squal);
        paa5100je_shutter_l_t paa5100je_shutter_l = {0};    paa5100je_read_shutter_l (instance, &paa5100je_shutter_l); 

        if (paa5100je_squal.val < 0x19 || paa5100je_shutter_l.val == 0x1F) 
        {
            return -2; 
        }
        else
        {
            *delta_x = ((int16_t) paa5100je_delta_xh.val << 8) | paa5100je_delta_xl.val;
            *delta_y = ((int16_t) paa5100je_delta_yh.val << 8) | paa5100je_delta_yl.val;
            return 0; 
        }
    }
}

/********************************************************************************************************
* @overview: 
********************************************************************************************************/
int32_t paa5100je_get_motion_burst (int32_t instance, int16_t* delta_x, int16_t* delta_y)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == false)  return -1; // Not initialised

    uint8_t buf[12] = {0};
    paa5100je_reg_read (instance, PAA5100JE_MOTION_BURST_ADDR, buf, sizeof(buf)); 
    
    // Parse
    if (buf[6] < 0x19 || buf[10] == 0x1F)
    {
        return false;
    }
    else
    {
        *delta_x = ((int16_t)buf[3] << 8) | buf[2];
        *delta_y = ((int16_t)buf[5] << 8) | buf[4];
        return true;
    }
}

/********************************************************************************************************
* @overview: Shutdown the sensor
********************************************************************************************************/
int32_t paa5100je_get_distance (int32_t instance, double* delta_x, double* delta_y, bool burst)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == false)  return -1; // Not initialised

    int16_t x = 0; 
    int16_t y = 0; 
    int32_t result = 0; 

    if (burst)
    {
        result = paa5100je_get_motion_burst (instance, &x, &y); 
        if (result != 0)
        {
            return result;  // 
        }
    }
    else
    {
        result = paa5100je_get_motion (instance, &x, &y); 
        if (result != 0)
        {
            return result;  // 
        }
    }

    *delta_x = ((double) x) * (PAA5100JE_INCH_TO_MM / m_cpi_coeffient[instance]);
    *delta_y = ((double) y) * (PAA5100JE_INCH_TO_MM / m_cpi_coeffient[instance]);

    return 0; 
}


/********************************************************************************************************
* @overview: Shutdown the sensor
********************************************************************************************************/
int32_t paa5100je_shutdown (uint32_t instance)
{
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    paa5100je_power_up_reset_t paa5100je_power_up_reset = {.val = 0xB6}; 
    return paa5100je_write_power_up_reset (instance, &paa5100je_power_up_reset);
    m_instance_ready[instance] = false; 
}

/********************************************************************************************************
* @overview: PixArt specific start up sequence
********************************************************************************************************/
int32_t paa5100je_config (uint32_t instance)
{  
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    
    uint8_t data = 0;
    int32_t c1 = 0; 
    int32_t c2 = 0;
    
    // Buffer 1
    for (int i = 0; i < sizeof(config_addr1); i++) paa5100je_reg_write (instance, (uint8_t) config_addr1[i], (uint8_t*) &config_data1[i], 1);

    // This? WTF
    paa5100je_reg_read (instance, 0x67, &data, 1);
    data = data & 0x80u;
    if (data == 0x80u)  data = 0x04; 
    else                data = 0x02; 
    paa5100je_reg_write (instance,0x48, &data, 1);

    // Buffer 2
    for (int i = 0; i < sizeof(config_addr2); i++) paa5100je_reg_write (instance, (uint8_t) config_addr2[i], (uint8_t*) &config_data2[i], 1);

    // Then this:
    paa5100je_reg_read (instance, 0x73, &data, 1);
    if (data == 0x00)
    {
        paa5100je_reg_read (instance, 0x70, &data, 1);
        c1 = (int32_t)  data;
        if (c1 <= 28)   c1 += 14;
        else            c1 += 11;
        if (c1 > 63) c1 = 63;

        paa5100je_reg_read (instance, 0x71, &data, 1);
        c2 = (int32_t)  data;
        c2 = (c2 * 45) / 100;
        data = 0x00;    paa5100je_reg_write (instance, 0x7F, &data, 1);
        data = 0xAD;    paa5100je_reg_write (instance, 0x61, &data, 1);
        data = 0x70;    paa5100je_reg_write (instance, 0x51, &data, 1);
        data = 0x0E;    paa5100je_reg_write (instance, 0x7F, &data, 1);
        paa5100je_reg_write (instance, 0x70, &c1, 1);
        paa5100je_reg_write (instance, 0x71, &c2, 1);
    }

    // Then this, a big one! 
    for (int i = 0; i < sizeof(config_addr3); i++) paa5100je_reg_write (instance, (uint8_t) config_addr3[i], (uint8_t*) &config_data3[i], 1);
    hal_delay_ms(10);
    for (int i = 0; i < sizeof(config_addr4); i++) paa5100je_reg_write (instance, (uint8_t) config_addr4[i], (uint8_t*) &config_data4[i], 1);
    hal_delay_ms(10);
    data = 0x00;     paa5100je_reg_write (instance, 0x73, &data, 1);
    return 0; 
}


/********************************************************************************************************
* @overview: Stub to initialise the PAA5100JE
********************************************************************************************************/
int32_t paa5100je_init (uint32_t instance)
{
    
    if (instance > PAA5100JE_MAX_INSTANCE-1) return -1;  // Overflow on the instances
    if (m_instance_ready[instance] == true)  return -1;  // Already initialised

    // Reset?
    hal_delay_ms(1); 
    hal_gpio_write(20, 1); 
    hal_delay_ms(1); 
    hal_gpio_write(20, 0); 
    hal_delay_ms(1); 
    hal_gpio_write(20, 1); 
    
    // Power Up
    paa5100je_power_up_reset_t paa5100je_power_up_reset = {.val = 0x5A}; 
    paa5100je_write_power_up_reset (instance, &paa5100je_power_up_reset);
    hal_delay_ms(100);

    // Read IDs
    paa5100je_prod_id_t paa5100je_prod_id = {0};            paa5100je_read_prod_id (instance, &paa5100je_prod_id); 
    paa5100je_inv_prod_id_t paa5100je_inv_prod_id = {0};    paa5100je_read_inv_prod_id (instance, &paa5100je_inv_prod_id); 
    if (paa5100je_prod_id.val != 0x49 || paa5100je_inv_prod_id.val != 0xB6) return -1; 

    // Read and clear (?) all the motion data
    paa5100je_motion_t paa5100je_motion = {0}; paa5100je_read_motion (instance, &paa5100je_motion ); 
    paa5100je_delta_xl_t paa5100je_delta_xl = {0}; paa5100je_read_delta_xl (instance, &paa5100je_delta_xl); 
    paa5100je_delta_xh_t paa5100je_delta_xh = {0}; paa5100je_read_delta_xh (instance, &paa5100je_delta_xh); 
    paa5100je_delta_yl_t paa5100je_delta_yl = {0}; paa5100je_read_delta_yl (instance, &paa5100je_delta_yl); 
    paa5100je_delta_yh_t paa5100je_delta_yh = {0}; paa5100je_read_delta_yh (instance, &paa5100je_delta_yh); 

    paa5100je_config (instance); 


    m_instance_ready[instance] = true; 

    return 0; // Return 0 for good, or <0 for something bad.

}


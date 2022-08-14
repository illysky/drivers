/********************************************************************************************************
* @file:			paa5100je.h
* @overview:		A driver file for PAA5100JE
* @date:			08/11/2022 14:33:55
* @author:		    Illysky CodeCrafter v1.0.0
********************************************************************************************************/
#ifndef PAA5100JE_H
#define PAA5100JE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <hal.h>


#define PAA5100JE_MAX_INSTANCE 4
#define PAA5100JE_INCH_TO_MM 25.4

/*** Typedefs ***/
#define PAA5100JE_PROD_ID_ADDR 0x00
#define PAA5100JE_PROD_ID_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned id:8;
    }; 
} paa5100je_prod_id_t;

#define PAA5100JE_REV_ID_ADDR 0x01
#define PAA5100JE_REV_ID_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned id:8;
    }; 
} paa5100je_rev_id_t;

#define PAA5100JE_INV_PROD_ID_ADDR 0x5F
#define PAA5100JE_INV_PROD_ID_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned id:8;
    }; 
} paa5100je_inv_prod_id_t;

#define PAA5100JE_MOTION_ADDR 0x02
#define PAA5100JE_MOTION_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned motion:8;
    }; 
} paa5100je_motion_t;

#define PAA5100JE_DELTA_XL_ADDR 0x03
#define PAA5100JE_DELTA_XL_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned delta_l:8;
    }; 
} paa5100je_delta_xl_t;

#define PAA5100JE_DELTA_XH_ADDR 0x04
#define PAA5100JE_DELTA_XH_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned delta_h:8;
    }; 
} paa5100je_delta_xh_t;

#define PAA5100JE_DELTA_YL_ADDR 0x05
#define PAA5100JE_DELTA_YL_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned delta_l:8;
    }; 
} paa5100je_delta_yl_t;

#define PAA5100JE_DELTA_YH_ADDR 0x06
#define PAA5100JE_DELTA_YH_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned delta_h:8;
    }; 
} paa5100je_delta_yh_t;

#define PAA5100JE_SQUAL_ADDR 0x07
#define PAA5100JE_SQUAL_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned sq:8;
    }; 
} paa5100je_squal_t;

#define PAA5100JE_RAW_DATA_SUM_ADDR 0x08
#define PAA5100JE_RAW_DATA_SUM_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned sum:8;
    }; 
} paa5100je_raw_data_sum_t;

#define PAA5100JE_MAXIMUM_RAWDATA_ADDR 0x09
#define PAA5100JE_MAXIMUM_RAWDATA_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned max:8;
    }; 
} paa5100je_maximum_rawdata_t;

#define PAA5100JE_MINIMUM_RAWDATA_ADDR 0x0A
#define PAA5100JE_MINIMUM_RAWDATA_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned min:8;
    }; 
} paa5100je_minimum_rawdata_t;

#define PAA5100JE_SHUTTER_L_ADDR 0x0B
#define PAA5100JE_SHUTTER_L_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned shutter_l:8;
    }; 
} paa5100je_shutter_l_t;

#define PAA5100JE_SHUTTER_H_ADDR 0x0C
#define PAA5100JE_SHUTTER_H_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned shutter_h:8;
    }; 
} paa5100je_shutter_h_t;

#define PAA5100JE_OBSERVATION_ADDR 0x15
#define PAA5100JE_OBSERVATION_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned observation:8;
    }; 
} paa5100je_observation_t;

#define PAA5100JE_MOTION_BURST_ADDR 0x16
#define PAA5100JE_MOTION_BURST_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned motion_burst:8;
    }; 
} paa5100je_motion_burst_t;

#define PAA5100JE_POWER_UP_RESET_ADDR 0x3A
#define PAA5100JE_POWER_UP_RESET_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned power_up_reset:8;
    }; 
} paa5100je_power_up_reset_t;

#define PAA5100JE_SHUTDOWN_ADDR 0x3B
#define PAA5100JE_SHUTDOWN_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned shutdown:8;
    }; 
} paa5100je_shutdown_t;

#define PAA5100JE_RESOLUTION_ADDR 0x4E
#define PAA5100JE_RESOLUTION_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned resolution:8;
    }; 
} paa5100je_resolution_t;

#define PAA5100JE_RAWDATA_GRAB_ADDR 0x58
#define PAA5100JE_RAWDATA_GRAB_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned rawdata_grab:8;
    }; 
} paa5100je_rawdata_grab_t;

#define PAA5100JE_RAWDATA_GRAB_STATUS_ADDR 0x59
#define PAA5100JE_RAWDATA_GRAB_STATUS_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned rawdata_grab_status:8;
    }; 
} paa5100je_rawdata_grab_status_t;

#define PAA5100JE_ORIENTATION_ADDR 0x5B
#define PAA5100JE_ORIENTATION_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned orientation:8;
    }; 
} paa5100je_orientation_t;

#define PAA5100JE_TEST_ADDR 0xFF
#define PAA5100JE_TEST_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned out:1;
        unsigned sl:2;
        unsigned reserved:5;
    }; 
} paa5100je_test_t;

#define PAA5100JE_LARGE_ADDR 0x88
#define PAA5100JE_LARGE_SIZE 1
typedef union
{
    uint8_t val;
    struct
    {
        unsigned out:1;
        unsigned sl:2;
        unsigned large:5;
        unsigned big:8;
    }; 
} paa5100je_large_t;

/*** Prototypes ***/
int32_t paa5100je_read_prod_id (uint32_t instance, paa5100je_prod_id_t* data);
int32_t paa5100je_read_rev_id (uint32_t instance, paa5100je_rev_id_t* data);
int32_t paa5100je_read_inv_prod_id (uint32_t instance, paa5100je_inv_prod_id_t* data);
int32_t paa5100je_read_motion (uint32_t instance, paa5100je_motion_t* data);
int32_t paa5100je_write_motion (uint32_t instance, paa5100je_motion_t* data);
int32_t paa5100je_read_delta_xl (uint32_t instance, paa5100je_delta_xl_t* data);
int32_t paa5100je_read_delta_xh (uint32_t instance, paa5100je_delta_xh_t* data);
int32_t paa5100je_read_delta_yl (uint32_t instance, paa5100je_delta_yl_t* data);
int32_t paa5100je_read_delta_yh (uint32_t instance, paa5100je_delta_yh_t* data);
int32_t paa5100je_read_squal (uint32_t instance, paa5100je_squal_t* data);
int32_t paa5100je_read_raw_data_sum (uint32_t instance, paa5100je_raw_data_sum_t* data);
int32_t paa5100je_read_maximum_rawdata (uint32_t instance, paa5100je_maximum_rawdata_t* data);
int32_t paa5100je_read_minimum_rawdata (uint32_t instance, paa5100je_minimum_rawdata_t* data);
int32_t paa5100je_read_shutter_l (uint32_t instance, paa5100je_shutter_l_t* data);
int32_t paa5100je_read_shutter_h (uint32_t instance, paa5100je_shutter_h_t* data);
int32_t paa5100je_read_observation (uint32_t instance, paa5100je_observation_t* data);
int32_t paa5100je_write_observation (uint32_t instance, paa5100je_observation_t* data);
int32_t paa5100je_read_motion_burst (uint32_t instance, paa5100je_motion_burst_t* data);
int32_t paa5100je_write_power_up_reset (uint32_t instance, paa5100je_power_up_reset_t* data);
int32_t paa5100je_write_shutdown (uint32_t instance, paa5100je_shutdown_t* data);
int32_t paa5100je_read_resolution (uint32_t instance, paa5100je_resolution_t* data);
int32_t paa5100je_write_resolution (uint32_t instance, paa5100je_resolution_t* data);
int32_t paa5100je_read_rawdata_grab (uint32_t instance, paa5100je_rawdata_grab_t* data);
int32_t paa5100je_write_rawdata_grab (uint32_t instance, paa5100je_rawdata_grab_t* data);
int32_t paa5100je_read_rawdata_grab_status (uint32_t instance, paa5100je_rawdata_grab_status_t* data);
int32_t paa5100je_read_orientation (uint32_t instance, paa5100je_orientation_t* data);
int32_t paa5100je_write_orientation (uint32_t instance, paa5100je_orientation_t* data);
int32_t paa5100je_read_test (uint32_t instance, paa5100je_test_t* data);
int32_t paa5100je_write_test (uint32_t instance, paa5100je_test_t* data);
int32_t paa5100je_read_large (uint32_t instance, paa5100je_large_t* data);
int32_t paa5100je_write_large (uint32_t instance, paa5100je_large_t* data);
int32_t paa5100je_reg_write (uint32_t instance, uint8_t addr, void* data, uint32_t size);
int32_t paa5100je_reg_read (uint32_t instance, uint8_t addr, void* data, uint32_t size);
int32_t paa5100je_init (uint32_t instance);
int32_t paa5100je_shutdown (uint32_t instance); 
int32_t paa5100je_set_working_height (int32_t instance, double height); 
int32_t paa5100je_config (uint32_t instance); 
int32_t paa5100je_set_resolution (int32_t instance, uint8_t resolution); 
int32_t paa5100je_set_orientation (int32_t instance, bool invert_x, bool invert_y, bool swap_xy);
int32_t paa5100je_get_surface_quality (int32_t instance, int32_t* sq); 
int32_t paa5100je_get_motion (int32_t instance, int16_t* delta_x, int16_t* delta_y); 
int32_t paa5100je_get_motion_burst (int32_t instance, int16_t* delta_x, int16_t* delta_y); 
int32_t paa5100je_get_distance (int32_t instance, double* delta_x, double* delta_y, bool burst);


#ifdef __cplusplus
}
#endif
#endif // PAA5100JE_H
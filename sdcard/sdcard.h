
#ifndef SDCARD_H__
#define SDCARD_H__

/*** Include ***/
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "ff.h"
#include "diskio_blkdev.h"
#include "app_config.h"

SD_DATA     SdData;

int32_t sdcard_init (void);
bool sdcard_ready (void);
void sdcard_new_file (void);
void sdcard_buffer (uint8_t* data, uint32_t size);
void sdcard_transfer (void);


#ifdef __cplusplus
}
#endif

#endif 

/** @} */

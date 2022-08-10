/** 
 * sd_card.c
 * Chiaro Technology
 * 24 February 2020
 **/

#include "sdcard.h"
#include "custom_board.h"
#include "stdlib.h"

#include "nrf.h"
#include "bsp.h"
#include "nrf_block_dev_sdc.h"
#include "nrf_log.h"

FATFS 		Fs;
FIL 		Datafile;
TX_DATA 	TxData;

#define SDC_SECTOR_SIZE             512     ///< Size of a single SD card block in bytes.
NRF_BLOCK_DEV_SDC_DEFINE(
        m_block_dev_sdc,
        NRF_BLOCK_DEV_SDC_CONFIG(
                SDC_SECTOR_SIZE,
                APP_SDCARD_CONFIG(SPI0_MOSI_IO, SPI0_MISO_IO, SPI0_SCK_IO, SD_CS_IO)
         ),
         NFR_BLOCK_DEV_INFO_CONFIG("Nordic", "SDC", "1.00")
);

#define DATA_FILE_HEADER 	"Device ID: %08X\nPressure, Value\n"

WCHAR ff_convert (WCHAR wch, UINT dir) {
    if (wch < 0x80) {
        // ASCII Char
        return wch;
    }
    // I don't support unicode it is too big!
    return 0;
}

WCHAR ff_wtoupper (WCHAR wch) {
    if (wch < 0x80) {
        // ASCII Char
        if (wch >= 'a' && wch <= 'z') {
            wch &= ~0x20;
        }
        return wch;
    }
    // I don't support unicode it is too big!
    return 0; 
}

int32_t sdcard_init (void) {
   
	FRESULT ff_result;
	DSTATUS disk_state = STA_NOINIT;
	
	SdData.sdMounted = false;
	SdData.sdCapacity = 0; 
		
	// Initialize FATFS disk I/O interface by providing the block device.
	static diskio_blkdev_t drives[] = {
        DISKIO_BLOCKDEV_CONFIG(NRF_BLOCKDEV_BASE_ADDR(m_block_dev_sdc, block_dev), NULL)
    };

    diskio_blockdev_register(drives, ARRAY_SIZE(drives));

	// when it tries to do this disk_init, and it goes the the diskio_blkdev.c file, it doesnt just fail
	// it also crashes teh prog and takes me to that timeout page thing

    NRF_LOG_INFO("Initializing disk 0 (SDC)...");
    for (uint32_t retries = 3; retries && disk_state; --retries) {
        disk_state = disk_initialize(0);
    }
    if (disk_state) {
        NRF_LOG_INFO("Disk initialization failed.");
		drives[0].state = 0; 
		disk_uninitialize(0); 
		return -1; 
    }
		
	// Get details about the SD Card
	uint32_t blocks_per_mb = (1024uL * 1024uL) / m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_size;
    uint32_t capacity = m_block_dev_sdc.block_dev.p_ops->geometry(&m_block_dev_sdc.block_dev)->blk_count / blocks_per_mb;
    NRF_LOG_INFO("Capacity: %d MB", capacity);

	// Mount SD Card
	ff_result = f_mount(&Fs, "", 1);
	if (ff_result) return -1;

	SdData.sdMounted = true; 
	SdData.sdCapacity = capacity; 
		
	return 0; 
}

bool sdcard_ready (void) {
	if (SdData.sdMounted == true && SD_CD_STATE  == SD_CD_PRESENT) {
		return true; 
	} else {
		SdData.sdMounted = 0; 
		return false; 
	}
}

void sdcard_new_file (void) {

	//FRESULT ff_result;
	uint32_t bytesW = 0; 
	char filename[128]; 
	char buffer[256]; 
	
	if (sdcard_ready() == false) return; 
	
	sprintf(filename, "Pressure_%05lu.csv", AppData.currentSession);
	
	NRF_LOG_INFO("File: %s", filename);
	// Create File
	if(f_open(&Datafile, filename, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK) {
		sprintf(buffer, SD_CARD_CSV_HEADER_PRESSURE);
		f_write(&Datafile, buffer, strlen((const char*)buffer), (void *)&bytesW);
		f_close(&Datafile);
	}
}

void sdcard_buffer (uint8_t* data, uint32_t size) {
	if (sdcard_ready() == false) return; 

	// Check we arent overflowing - if we are, dont save data
	if (SdData.sdDataSize <  APP_SD_BUFFER_WATER_LEVEL){ 
		
		// Add data to sd buffer
		memcpy(&SdData.sdDataBuffer[SdData.sdBufferIndex][SdData.sdDataSize], data, size); 
		SdData.sdDataSize += size; 
		SdData.currentSamples++; 
	
		// Swap buffers and signal tranfer
		if (SdData.currentSamples >= SdData.transferSize && SdData.transferBuffer == false) {

			// Prep our transfer buffer
			SdData.transferBuffer = true; 							// Set Flag to TX Buffer to SD Card
			SdData.pendingBufferIndex = SdData.sdBufferIndex;  		// Set Buffer to TX
			SdData.pendingBufferSize = SdData.sdDataSize;			// Set Buffer Size
			SdData.pendingSamples = SdData.currentSamples; 			// Set Samples 
			SdData.pendingInterval = SdData.currentInterval; 		// Set Start Interval
			SdData.currentInterval += SdData.currentSamples; 		// Accumulate Interval counter
		
			// Change buffer pointer 
			SdData.sdBufferIndex++; 
			SdData.sdDataSize = 0; 
			SdData.currentSamples = 0; 			
			if (SdData.sdBufferIndex == APP_SD_BUFFER_COUNT) {
				SdData.sdBufferIndex = 0; 
			}
		}
	}
}

void sdcard_transfer (void) {
	
	FRESULT ff_result;
	uint32_t bytesW = 0; 
	char filename[128]; 
	uint8_t 	csvBuff [4096]; 
	uint32_t 	csvSize = 0; 
	uint32_t 	sampleIndex = 0; 
	//bool result = false;
	PRESSURE_DATA pressureData; 
	uint32_t interval = 0; 
	
	if (AppData.status == APP_DATA_STATUS_IDLE){
		return;
	}
	if (sdcard_ready() == false) {
		return;
	}
	
	if (SdData.transferBuffer == true) {
		// Pressure Mode
		sprintf(filename, "Pressure_%05lu.csv", AppData.currentSession);	
		ff_result = f_open(&Datafile, filename, FA_READ | FA_WRITE | FA_OPEN_APPEND); 
		if (ff_result == FR_OK ){
				while (SdData.pendingSamples) {
					csvSize = 0; 	
					while (1) {
						// Extract Data
						memcpy(&pressureData, &SdData.sdDataBuffer[SdData.pendingBufferIndex][sampleIndex], sizeof(PRESSURE_DATA)); 
						csvSize += sprintf ((char*) csvBuff+csvSize, "%lu,%.1f\n", (SdData.pendingInterval+interval) * AppData.currentInterval, pressureData.pressure);
						sampleIndex+=sizeof(PRESSURE_DATA); 
						SdData.pendingSamples--;
						AppData.samplesProcessed++;
						interval++;
						if (csvSize > 2048) break; 									// CSV Buffer is full -> Write
						if (SdData.pendingSamples == 0) break; 			// Samples are all processed
					}
					ff_result = f_write(&Datafile, (const char*) csvBuff, csvSize, (void *)&bytesW);
					__NOP(); 
				}
				f_close(&Datafile);
			}
		SdData.transferBuffer = false;  
	}
}

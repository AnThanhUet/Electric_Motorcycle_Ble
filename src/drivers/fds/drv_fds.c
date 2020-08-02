/**
 * @file drv_fds.c
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "drv_fds.h"
#include "fds.h"
#define NRF_LOG_MODULE_NAME drv_fds
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
static void fds_evt_handler(fds_evt_t const * p_evt)
{
    switch (p_evt->id)
    {
        case FDS_EVT_INIT:
        if (p_evt->result != FDS_SUCCESS)
        {
            // Initialization failed.
        }
        break;
		case FDS_EVT_WRITE:
		if (p_evt->result == FDS_SUCCESS)
		{
			NRF_LOG_FLUSH();
			NRF_LOG_INFO("write flash success");
		}
		break;
        default:
        break;
    }
}

uint32_t drv_fds_init (void)
{
	uint32_t ret = fds_register(fds_evt_handler);
	if (ret != FDS_SUCCESS)
	{
		return ret;	
	}
	ret = fds_init();
	if (ret != FDS_SUCCESS)
	{
		return ret;
	}
	
	return NRF_SUCCESS;
}

uint32_t drv_fds_read (uint16_t drv_file_id, 
                        uint16_t drv_rec_key, 
                        uint32_t *data_store)
{
	fds_flash_record_t  flash_record;
	fds_record_desc_t   record_desc;
	fds_find_token_t    ftok ={0};
	uint32_t *data;
	uint32_t err_code;
	
	// Loop until all records with the given key and file ID have been found.
	while (fds_record_find(drv_file_id, drv_rec_key, &record_desc, &ftok) == FDS_SUCCESS)
	{
		err_code = fds_record_open(&record_desc, &flash_record);
		if ( err_code != FDS_SUCCESS)
		{
			return err_code;		
		}
		
		data = (uint32_t *) flash_record.p_data;
		for (uint8_t i=1; i <flash_record.p_header->length_words ; i++)
		{
			// NRF_LOG_FLUSH();
            // NRF_LOG_INFO("data[%d] = %x",i,data[i]);
			data_store[i-1] = data[i];
		}
		// Access the record through the flash_record structure.
		// Close the record when done.
		err_code = fds_record_close(&record_desc);
		if (err_code != FDS_SUCCESS)
		{
			return err_code;	
		}
		return NRF_SUCCESS;
	}
	return NRF_ERROR_NOT_FOUND;
}

uint32_t drv_fds_write ( uint16_t drv_file_id, 
                         uint16_t drv_rec_key,
                         uint32_t *data,     
                         uint16_t len)
{
	ret_code_t ret;
	fds_record_t        record;
	fds_record_desc_t   record_desc;
	uint32_t *data_ing = (uint32_t*)malloc((len+1)*sizeof(uint32_t));
	data_ing[0] = 0;
	for (uint8_t i = 1; i < len + 1; i ++)
	{
		data_ing[i] = data[i-1];
	}
	// Set up record.
	record.file_id              = drv_file_id;
	record.key              	= drv_rec_key;
	record.data.p_data          = data_ing;
	record.data.length_words    = len+1;

	ret = drv_fds_delete(drv_file_id,drv_rec_key);
	if (ret != NRF_SUCCESS)
	{
		return ret;
	}				
	ret = fds_record_write(&record_desc, &record);
	if (ret != FDS_SUCCESS)
	{
		return ret;
	}
	
	return NRF_SUCCESS;
}

uint32_t drv_fds_delete(uint16_t drv_file_id, uint16_t drv_rec_key)
{
    fds_record_desc_t   record_desc;
	fds_find_token_t    ftok;

	ftok.page=0;
	ftok.p_addr=NULL;
	// Loop and find records with same ID and rec key and mark them as deleted. 
	while (fds_record_find(drv_file_id, drv_rec_key, &record_desc, &ftok) == FDS_SUCCESS)
	{
		fds_record_delete(&record_desc);
	}
	// call the garbage collector to empty them, don't need to do this all the time, this is just for demonstration
	ret_code_t ret = fds_gc();
	if (ret != FDS_SUCCESS)
	{
		return ret;
	}
	return NRF_SUCCESS;
}


/******************************** End of file *********************************/

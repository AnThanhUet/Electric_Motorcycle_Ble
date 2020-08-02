/**
 * @file drv_fds.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __DRV_FDS_H__
#define __DRV_FDS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "stdint.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t drv_fds_init (void);

uint32_t drv_fds_read (uint16_t _file_id, 
                        uint16_t _rec_key, 
                        uint32_t *data_store);

uint32_t drv_fds_write ( uint16_t _file_id, 
                         uint16_t _rec_key,
                         uint32_t *data,     
                         uint16_t len);

uint32_t drv_fds_delete(uint16_t _file_id, uint16_t _rec_key);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_FDS_H__ */

/******************************** End of file *********************************/

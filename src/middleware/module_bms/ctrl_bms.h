/**
 * @file ctrl_bms.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CTRL_BMS_H__
#define __CTRL_BMS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
typedef enum
{
    CTRL_BMS_SUCCESS
}ctrl_bms_evt_t;

typedef void (*ctrl_bms_hander_t)(ctrl_bms_evt_t evt);
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t ctrl_bms_init();

uint32_t ctrl_bms_uninit();

uint32_t ctrl_bms_getValue();

#ifdef __cplusplus
}
#endif

#endif /* __CTRL_BMS_H__ */

/******************************** End of file *********************************/

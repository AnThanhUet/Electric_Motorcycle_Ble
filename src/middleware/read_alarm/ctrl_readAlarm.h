/**
 * @file ctrl_readAlarm.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CTRL_READALARM_H__
#define __CTRL_READALARM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "drv_gpio.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
#define PIN_ECU_RESP_LOCKED 13
#define PIN_READ_ALARM      14
#define PIN_CTRL_LOCK_WEEL  15
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t ctrl_readAlarm_init(drv_gpio_handler_t read_alarm_handler);

void ctrl_read_Alarm_uninit();

#ifdef __cplusplus
}
#endif

#endif /* __CTRL_READALARM_H__ */

/******************************** End of file *********************************/

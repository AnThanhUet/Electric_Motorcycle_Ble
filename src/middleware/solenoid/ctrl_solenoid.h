/**
 * @file ctrl_solenoid.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CTRL_SOLENOID_H__
#define __CTRL_SOLENOID_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "drv_gpiote_irq.h"
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
    CTRL_SEN_OFF = 0,
    CTRL_SEN_ON
    
}ctrl_solenoid_evt_t;

typedef void (*ctrl_solenoid_handler_t)(ctrl_solenoid_evt_t evt);
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t ctrl_solenoid_init(ctrl_solenoid_handler_t solendoid_handler);

uint32_t ctrl_solenoid_on();

uint32_t ctrl_solenoid_off();

uint32_t ctrl_solenoid_getSatatus();

#ifdef __cplusplus
}
#endif

#endif /* __CTRL_SOLENOID_H__ */

/******************************** End of file *********************************/

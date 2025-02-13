/**
 * @file drv_pwm.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "nrf_delay.h"
#include "app_pwm.h"
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
uint32_t drv_pwm_init();

uint32_t drv_pwm_start();

uint32_t drv_pwm_stop();

#ifdef __cplusplus
}
#endif

#endif /* __DRV_PWM_H__ */

/******************************** End of file *********************************/

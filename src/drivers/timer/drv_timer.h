/**
 * @file drv_timer.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-26
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "nrf_drv_timer.h"
#include "app_error.h"
#include "nrf_gpio.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
static const nrf_drv_timer_t OPEN_SMK_ZIN_TIMER = NRF_DRV_TIMER_INSTANCE(2);
#define BIT_SHORT_SMK   nrf_drv_timer_us_to_ticks(&OPEN_SMK_ZIN_TIMER, 419)
#define BIT_LONG_SMK    nrf_drv_timer_us_to_ticks(&OPEN_SMK_ZIN_TIMER, 840)
#define WAIT_PKG        nrf_drv_timer_ms_to_ticks(&OPEN_SMK_ZIN_TIMER,5)
#define VALUE_IMPORTANT nrf_drv_timer_us_to_ticks(&OPEN_SMK_ZIN_TIMER,9)
#define BUZZER_DIS_BE nrf_drv_timer_us_to_ticks(&OPEN_SMK_ZIN_TIMER,500)
#define BUZZER_DIS_TO nrf_drv_timer_us_to_ticks(&OPEN_SMK_ZIN_TIMER,150)
// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
void drv_timer_init();

void drv_timer_start(uint32_t timer_ticks);

void drv_timer_stop();


#ifdef __cplusplus
}
#endif

#endif /* __DRV_TIMER_H__ */

/******************************** End of file *********************************/

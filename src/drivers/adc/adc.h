/**
 * @file gpio.h
 * @author TienTD (ductien.savy@gmail.com)
 * @brief 
 * @version 0.1
 * @date 24-07-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/

/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
#include "nrf_saadc.h"
#include "nrf_drv_saadc.h"
#include "stdint.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "sdk_errors.h"
// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/

void adc_event_init(nrf_drv_timer_t m_timer,nrf_ppi_channel_t m_ppi_channel);

void adc_channel_init(void);

void saadc_sampling_event_enable(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H__ */

/******************************** End of file *********************************/

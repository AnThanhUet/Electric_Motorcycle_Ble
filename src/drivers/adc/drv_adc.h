/**
 * @file drv_adc.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "nrf_drv_saadc.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
#define MAX_CHANNEL_CONFIG_ADC 3
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t drv_adc_init(uint8_t *adc_pins,
                    uint8_t     adc_count);

uint32_t drv_adc_samp_event_init();

uint32_t drv_adc_samp_enable();

uint32_t drv_adc_get_value();


#ifdef __cplusplus
}
#endif

#endif /* __DRV_ADC_H__ */

/******************************** End of file *********************************/

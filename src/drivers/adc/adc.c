/**
 * @file adc.c
 * @author TienTD (ductien.savy@gmail.com)
 * @brief 
 * @version 0.1
 * @date 24-07-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "adc.h"
#include "nrf_saadc.h"
#include "nrf_drv_saadc.h"
#include "stdint.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "sdk_errors.h"

#define NRF_LOG_MODULE_NAME adc
#include "nrf_log.h"
#include "status.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
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
void adc_channel_init()
{
    uint32_t ret;
    nrf_saadc_channel_config_t channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN4);
    channel_config.gain = NRF_SAADC_GAIN1_2;
    ret = nrf_drv_saadc_channel_init(4,&channel_config);
    APP_ERROR_CHECK_SAVY(ret);
}
/******************************** End of file *********************************/

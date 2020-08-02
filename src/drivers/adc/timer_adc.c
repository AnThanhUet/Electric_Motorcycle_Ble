/**
 * @file timer_adc.c
 * @author TienTD (ductien.savy@gmail.com)
 * @brief 
 * @version 0.1
 * @date 02-08-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "app_timer.h"
#include "app_util_platform.h"
#include "gap.h"
#include "gatt.h"
#include "boards.h"
#include "nrf_delay.h"
#include "timer_adc.h"
#include "adc.h"
#define NRF_LOG_MODULE_NAME timer_adc
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
#define SAADC_SAMPLE_RATE		        250
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
static const nrf_drv_timer_t   m_timer = NRF_DRV_TIMER_INSTANCE(3);
static nrf_ppi_channel_t       m_ppi_channel;
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
void timer_handler(nrf_timer_event_t event_type, void* p_context)
{

}

void timer_adc_ppi_event_enable()
{
    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);
    APP_ERROR_CHECK_SAVY(err_code);
}


void timer_adc_event_init()
{
    ret_code_t err_code;
    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK_SAVY(err_code);
    
    nrf_drv_timer_config_t timer_config = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_config.frequency = NRF_TIMER_FREQ_31250Hz;
    err_code = nrf_drv_timer_init(&m_timer, &timer_config, timer_handler);
    APP_ERROR_CHECK_SAVY(err_code);

    /* setup m_timer for compare event */
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer,SAADC_SAMPLE_RATE);
    nrf_drv_timer_extended_compare(&m_timer, NRF_TIMER_CC_CHANNEL0, 
                                    ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, false);
    nrf_drv_timer_enable(&m_timer);

    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer, NRF_TIMER_CC_CHANNEL0);
    uint32_t saadc_sample_event_addr = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    APP_ERROR_CHECK_SAVY(err_code);
    
    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel, 
                                        timer_compare_event_addr, 
                                        saadc_sample_event_addr);
    APP_ERROR_CHECK_SAVY(err_code);
}

void timer_adc_start()
{
    //timer_adc_event_init();
    timer_adc_ppi_event_enable();
}

void timer_adc_stop()
{
    nrf_drv_ppi_channel_disable(m_ppi_channel);
}
/******************************** End of file *********************************/

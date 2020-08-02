/**
 * @file drv_timer.c
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-26
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "drv_timer.h"
#define NRF_LOG_MODULE_NAME drv_timer
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/
// config timer hard
static nrf_drv_timer_config_t timer_cfg = {
        .frequency          = 2,
        .mode               = 0,          
        .bit_width          = 0,
        .interrupt_priority = 3,                    
        .p_context          = NULL                                                  
};
/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * @brief : function drv timer us
 * 
 * @param open_smk_zin_timer_handler 
 */
void drv_timer_init(nrf_timer_event_handler_t open_smk_zin_timer_handler)
{
    uint32_t err_code;
    err_code = nrf_drv_timer_init(&OPEN_SMK_ZIN_TIMER, &timer_cfg, 
                            open_smk_zin_timer_handler);
    APP_ERROR_CHECK_SAVY(err_code);
}

/**
 * @brief : function start timer 
 * 
 * @param timer_ticks 
 */
void drv_timer_start(uint32_t timer_ticks)
{
    // set CC channel for timer
    nrf_drv_timer_extended_compare(
         &OPEN_SMK_ZIN_TIMER, NRF_TIMER_CC_CHANNEL0, timer_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
    // enable timer
    nrf_drv_timer_enable(&OPEN_SMK_ZIN_TIMER);
}

/**
 * @brief : function stop timer
 * 
 */
void drv_timer_stop()
{
    nrf_drv_timer_disable(&OPEN_SMK_ZIN_TIMER);
}

/******************************** End of file *********************************/

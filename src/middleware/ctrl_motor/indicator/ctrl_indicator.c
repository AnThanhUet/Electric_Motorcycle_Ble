/**
 * @file ctrl_indicator.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "drv_gpio.h"
#include "drv_uart.h"
#include "timer.h"
#include "ctrl_motor.h"
#include "ctrl_indicator.h"
#define NRF_LOG_MODULE_NAME ctrl_indicator
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
APP_TIMER_DEF(id_indicator);
#define PIN_CTRL_IND         17
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
static uint8_t ind_times = 0;  // times loop
static uint8_t ind_count = 0; // counter loop
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
/**
 * @brief : function config output ind
 * 
 */
static inline void ctrl_ind_cfg()
{
    drv_gpio_cfg_out(PIN_CTRL_IND);
}     

/**
 * @brief : function ind active
 * 
 */
static inline void ctrl_ind_high()
{
    drv_gpio_clear(PIN_CTRL_IND);
}

/**
 * @brief : function ind stop
 * 
 */
static inline void ctrl_ind_low()
{
    drv_gpio_set(PIN_CTRL_IND);
}

static void timer_ind_handler(void *p_context)
{
    static uint8_t status_b = 0;

    if (status_b == 0)
    {
        status_b = 1;
        ctrl_ind_high();
    }
    else
    {
        status_b = 0;
        ind_count ++;
        if (ind_count == ind_times)
        {
            // stop
            ctrl_ind_close();
        }
        else
        {
            ctrl_ind_low();
        }   
    }
}

uint32_t ctrl_ind_init()
{
    uint32_t ret;

    ctrl_ind_cfg();
    // timer init
    ret = timer_create(id_indicator, APP_TIMER_MODE_REPEATED, timer_ind_handler);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

uint32_t ctrl_ind_open(ctrl_motor_cfg_param_t ind)
{
    uint32_t ret;
    
    ind_times = ind.times;

    if (ind.enable == 1)
    {
        // timer start
        ret = timer_start(id_indicator, ind.period);
        RETURN_IF_ERROR(ret);
    }
    else
    {
        // nothing
    }

    return NRF_SUCCESS;
}

uint32_t ctrl_ind_close()
{
    uint32_t ret;
    ret = timer_stop(id_indicator);
    RETURN_IF_ERROR(ret);
    // reset counter
    ind_count = 0;
    //
    ctrl_ind_low();
    return NRF_SUCCESS;
}

/******************************** End of file *********************************/

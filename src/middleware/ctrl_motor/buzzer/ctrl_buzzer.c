/**
 * @file ctrl_buzzer.c
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
#include "ctrl_buzzer.h"
#define NRF_LOG_MODULE_NAME ctrl_buzzer
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
APP_TIMER_DEF(id_buzzer);
#define PIN_CTRL_BUZZZER         20
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
static uint8_t buzzer_times = 0;  // times loop
static uint8_t buzzer_count = 0; // counter loop
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * @brief : function config output buzzer
 * 
 */
static inline void ctrl_buzzer_cfg()
{
    drv_gpio_cfg_out(PIN_CTRL_BUZZZER);
}     

/**
 * @brief : function buzzer active
 * 
 */
static inline void ctrl_buzzer_high()
{
    drv_gpio_clear(PIN_CTRL_BUZZZER);
}

/**
 * @brief : function buzzer stop
 * 
 */
static inline void ctrl_buzzer_low()
{
    drv_gpio_set(PIN_CTRL_BUZZZER);
}

static void timer_buzzer_handler(void *p_context)
{
    static uint8_t status_b = 0;
    // NRF_LOG_FLUSH();
    // NRF_LOG_INFO("buzzer ");
    if (status_b == 0)
    {
        status_b = 1;
        ctrl_buzzer_high();
    }
    else
    {
        status_b = 0;
        ctrl_buzzer_low();
        buzzer_count ++;
        if (buzzer_count == buzzer_times)
        {
            // stop
            ctrl_buzzer_close();
            // reset counter
            buzzer_count = 0;
        }
        else
        {

        }   
    }
}

uint32_t ctrl_buzzer_init()
{
    uint32_t ret;
    ctrl_buzzer_cfg();
    // timer init
    ret = timer_create(id_buzzer, APP_TIMER_MODE_REPEATED, timer_buzzer_handler);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

uint32_t ctrl_buzzer_open(ctrl_motor_cfg_param_t buzzer)
{
    uint32_t ret;
    
    buzzer_times = buzzer.times;

    if (buzzer.enable == 1)
    {
        // timer start
        ret = timer_start(id_buzzer, buzzer.period);
        RETURN_IF_ERROR(ret);
    }
    else
    {
        // nothing
    }

    return NRF_SUCCESS;
}

uint32_t ctrl_buzzer_close()
{
    uint32_t ret;
    ret = timer_stop(id_buzzer);
    RETURN_IF_ERROR(ret);
    // reset counter
    buzzer_count = 0;
    //
    ctrl_buzzer_low();
    return NRF_SUCCESS;
}



/******************************** End of file *********************************/

/**
 * @file ctrl_motor.c
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
#include "ctrl_buzzer.h"
#include "ctrl_wheel.h"
#define NRF_LOG_MODULE_NAME ctrl_motor
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
static uint8_t ctrl_motor_activeLevel = 0; 
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
uint32_t ctrl_motor_init()
{
    uint32_t ret;
    ret = ctrl_wheel_init();
    RETURN_IF_ERROR(ret);

    ret = ctrl_ind_init();
    RETURN_IF_ERROR(ret);

    ret = ctrl_buzzer_init();
    RETURN_IF_ERROR(ret);

    return NRF_SUCCESS;
}

static uint32_t ctrl_motor_noActive()
{
    uint32_t ret;

    ret = ctrl_ind_close();
    RETURN_IF_ERROR(ret);

    ret = ctrl_buzzer_close();
    RETURN_IF_ERROR(ret);

    return NRF_SUCCESS;
}

static uint32_t ctrl_motor_active(ctrl_motor_cfg_t motor)
{
    uint32_t ret;

    // stop 
    ctrl_motor_noActive();

    ret = ctrl_ind_open(motor.indicator);
    RETURN_IF_ERROR(ret);

    ret = ctrl_buzzer_open(motor.buzzer);
    RETURN_IF_ERROR(ret);

    return NRF_SUCCESS;
}

uint32_t ctrl_motor_respFind()
{
    uint32_t ret;
    static ctrl_motor_cfg_t motor_respFind = {
        .buzzer = {2,500,1},
        .indicator = {2,500,1}
    };
    
    ctrl_motor_activeLevel = 1;

    ret = ctrl_motor_active(motor_respFind);
    RETURN_IF_ERROR(ret);

    return NRF_SUCCESS;
}

uint32_t ctrl_motor_respAlarm()
{
    uint32_t ret;
    static ctrl_motor_cfg_t motor_respAlarm = {
        .buzzer = {10,500,1},
        .indicator = {10,500,1}
    };

    ctrl_motor_activeLevel = 2;
    
    ret = ctrl_motor_active(motor_respAlarm);
    RETURN_IF_ERROR(ret);

    return NRF_SUCCESS;
}

uint32_t ctrl_motor_respWarning()
{
    uint32_t ret;
    static ctrl_motor_cfg_t motor_respWarning = {
        .buzzer = {20,200,1},
        .indicator = {20,200,1}
    };

    ctrl_motor_activeLevel = 3;
    
    ret = ctrl_motor_active(motor_respWarning);
    RETURN_IF_ERROR(ret);

    return NRF_SUCCESS;
}

/******************************** End of file *********************************/

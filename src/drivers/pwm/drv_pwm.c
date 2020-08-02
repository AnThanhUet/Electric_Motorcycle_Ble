/**
 * @file drv_pwm.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "drv_pwm.h"
#include "status.h"
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
APP_PWM_INSTANCE(PWM1,1);                   // Create the instance "PWM1" using TIMER1.
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

void pwm_ready_callback(uint32_t pwm_id)    // PWM callback function
{
    // ready_flag = true;
}

uint32_t drv_pwm_init()
{
    uint32_t err_code;
    app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_1CH(200, 1);

    /* Switch the polarity of the second channel. */
    pwm1_cfg.pin_polarity[0] = APP_PWM_POLARITY_ACTIVE_HIGH;

    /* Initialize and enable PWM. */
    err_code = app_pwm_init(&PWM1,&pwm1_cfg,pwm_ready_callback);
    RETURN_IF_ERROR(err_code);
    app_pwm_enable(&PWM1);

    return 0;
}

uint32_t drv_pwm_start()
{
    while(app_pwm_channel_duty_set(&PWM1, 0, 10) == NRF_ERROR_BUSY);
    return 0;
}

uint32_t drv_pwm_stop()
{
    while(app_pwm_channel_duty_set(&PWM1, 0, 0) == NRF_ERROR_BUSY);
    return 0;
}


/******************************** End of file *********************************/

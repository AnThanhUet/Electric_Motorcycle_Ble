/**
 * @file drv_gpiote.c
 * @author LamPT (phanthelam.savy@gamil.com)
 * @brief 
 * @version 0.1
 * @date 02-08-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "drv_gpio.h"
#include <stdio.h>
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#define NRF_LOG_MODULE_NAME drv_gpio_input
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
#define MAX_USER 1
#define DETECTION_DELAY 50
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
uint32_t drv_gpio_init (drv_gpio_cfg_t *gpio, uint8_t gpio_counter)
{
    uint32_t status;
    APP_GPIOTE_INIT(MAX_USER);
    status = app_button_init (gpio, gpio_counter, DETECTION_DELAY);
    RETURN_IF_ERROR(status);
    status = app_button_enable();
    RETURN_IF_ERROR(status);
    return NRF_SUCCESS;
}

/**
 * @brief : function diable gpio (app_button)
 * 
 */
void drv_gpio_uninit()
{
    app_button_disable();
}

/**
 * @brief : function config gpio output
 * 
 * @param pin_num 
 */
void drv_gpio_cfg_out (uint32_t pin_num)
{
    nrf_gpio_cfg_output (pin_num);
}

/**
 * @brief : function config gpio input
 * 
 * @param pin_num : 
 * @param pull_config 
 */
void drv_gpio_cfg_in (uint32_t pin_num, drv_gpio_pin_pull_t pull_config)
{
    nrf_gpio_cfg_input(pin_num, pull_config);
}

/**
 * @brief : function 
 * 
 * @param pin_num 
 */
void drv_gpio_set (uint32_t pin_num)
{
    nrf_gpio_pin_set(pin_num);
}

/**
 * @brief :
 * 
 * @param pin_num 
 */
void drv_gpio_clear (uint32_t pin_num)
{
    nrf_gpio_pin_clear(pin_num);
}

/**
 * @brief :
 * 
 * @param pin_num 
 * @return uint32_t 
 */
uint32_t drv_gpio_read (uint32_t pin_num)
{
    return nrf_gpio_pin_read(pin_num);
}

/**
 * @brief :
 * 
 * @param pin_num 
 */
void drv_gpio_toggle(uint32_t pin_num)
{
    nrf_drv_gpiote_out_toggle(pin_num);
}
/******************************** End of file *********************************/

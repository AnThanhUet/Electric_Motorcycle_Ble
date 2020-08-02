/**
 * @file drv_gpiote.h
 * @author LamPT (phanthelam.savy@gamil.com)
 * @brief 
 * @version 0.1
 * @date 02-08-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __DRV_GPIOTE_H__
#define __DRV_GPIOTE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "app_gpiote.h"
#include "nrf_drv_gpiote.h"
#include "app_button.h"
#include "app_timer.h"
#include "stdio.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
#define drv_gpio_pin_pull_t     nrf_gpio_pin_pull_t 
#define drv_gpio_cfg_t        app_button_cfg_t
#define drv_gpio_handler_t    app_button_handler_t

#define DRV_GPIO_ACTIVE_LOW   APP_BUTTON_ACTIVE_LOW
#define DRV_GPIO_ACTIVE_HIGH  APP_BUTTON_ACTIVE_HIGH
#define DRV_GPIO_PUSH         APP_BUTTON_PUSH
#define DRV_GPIO_RELEASE      APP_BUTTON_RELEASE

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
typedef enum
{
    DRV_GPIO_NO_PULL = NRF_GPIO_PIN_NOPULL,
    DRV_GPIO_PULLUP = NRF_GPIO_PIN_PULLUP,
    DRV_GPIO_PULLDOWN = NRF_GPIO_PIN_PULLDOWN
}drv_gpio_pull_t;
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t drv_gpio_init (drv_gpio_cfg_t *gpio, uint8_t gpio_counter);

void drv_gpio_uninit();

void drv_gpio_cfg_out (uint32_t pin_num);

void drv_gpio_cfg_in (uint32_t pin_num, drv_gpio_pin_pull_t pull_config);

void drv_gpio_set (uint32_t pin_num);

void drv_gpio_clear (uint32_t pin_num);

uint32_t drv_gpio_read (uint32_t pin_num);

void drv_gpio_toggle(uint32_t pin_num);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIOTE_INPUT_H__ */

/******************************** End of file *********************************/

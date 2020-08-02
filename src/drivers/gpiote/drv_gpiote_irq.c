/**
 * @file drv_gpiote_irq.c
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "drv_gpiote_irq.h"
#include "drv_gpio.h"
#define NRF_LOG_MODULE_NAME drv_gpiote_irq
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

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
uint32_t drv_gpiote_irq_init(void)
{
    uint32_t err_code;
    
    if (!nrf_drv_gpiote_is_init())
    {
        err_code = nrf_drv_gpiote_init();
        RETURN_IF_ERROR(err_code);
    }
    return NRF_SUCCESS;
}

uint32_t drv_gpiote_irq_enable(uint32_t pin, drv_gte_irq_handler_t handler)
{
    uint32_t err_code;
    drv_gte_irq_in_config_t config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(false);
    config.pull = NRF_GPIO_PIN_PULLUP;

    err_code = nrf_drv_gpiote_in_init(pin, &config, handler);
    RETURN_IF_ERROR(err_code);
    nrf_drv_gpiote_in_event_enable(pin, true);
    return NRF_SUCCESS;
}


void drv_gpiote_irq_disable(uint32_t pin)
{
    nrf_drv_gpiote_in_event_disable(pin);
}

/******************************** End of file *********************************/

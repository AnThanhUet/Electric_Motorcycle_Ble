/**
 * @file ctrl_solenoid.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "ctrl_solenoid.h"
#include "drv_gpiote_irq.h"
#include "drv_gpio.h"
#define NRF_LOG_MODULE_NAME ctrl_solenoid
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
#define CTRL_SEN_PIN_OUT    ECU_SEN_OUT
#define CTRL_SEN_PIN_IN     ECU_SEN_IN
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
static ctrl_solenoid_handler_t main_func = NULL;
static bool status_solenoid_cur = 0;
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

void solenoid_gte_handler(drv_gte_irq_pint_t pin, drv_gte_irq_polarity_t action)
{
    if (action == DRV_GTE_TOGGLE)
    {
        if(drv_gpio_read(pin) == DRV_GTE_PUSH)
        {
            status_solenoid_cur = CTRL_SEN_ON;
            if (main_func != NULL)
            {
                main_func(CTRL_SEN_ON);
            }
        }
        else
        {
            status_solenoid_cur = CTRL_SEN_OFF;
            if (main_func != NULL)
            {
                main_func(CTRL_SEN_OFF);
            }
        }
    }
}

static void ctrl_solenoid_checkStatus()
{
    if (drv_gpio_read(CTRL_SEN_PIN_IN) == DRV_GTE_PUSH)
    {
        status_solenoid_cur = CTRL_SEN_ON;
        if (main_func != NULL)
        {
            main_func(CTRL_SEN_ON);
        }
    }
    else
    {
        status_solenoid_cur = CTRL_SEN_OFF;
        if (main_func != NULL)
        {
            main_func(CTRL_SEN_OFF);
        }
    }
}

/**
 * @brief : function initialized solend
 * 
 * @param solendoid_handler 
 * @return uint32_t 
 */
uint32_t ctrl_solenoid_init(ctrl_solenoid_handler_t solendoid_handler)
{
    if (solendoid_handler == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint32_t ret;

    ret = drv_gpiote_irq_init();
    RETURN_IF_ERROR(ret);
    ret = drv_gpiote_irq_enable(CTRL_SEN_PIN_IN, solenoid_gte_handler);
    RETURN_IF_ERROR(ret);

    main_func = solendoid_handler;
    // config solenoid
    drv_gpio_cfg_out(CTRL_SEN_PIN_OUT);

    ctrl_solenoid_checkStatus();

    return NRF_SUCCESS;
}

/**
 * @brief : disable solenoid irq
 * 
 */
void ctrl_solenoid_uninit()
{
    drv_gpiote_irq_disable(CTRL_SEN_PIN_IN);
}

/**
 * @brief : controll sen on
 * 
 * @return uint32_t 
 */
uint32_t ctrl_solenoid_on()
{
    if (status_solenoid_cur == CTRL_SEN_ON)
    {
        // nothing
        NRF_LOG_FLUSH();
        NRF_LOG_INFO(" Status is on ");
    }
    else
    {
        drv_gpio_clear(CTRL_SEN_PIN_OUT);
    }
    
    return NRF_SUCCESS;
}

/**
 * @brief : controll sen off
 * 
 * @return uint32_t 
 */
uint32_t ctrl_solenoid_off()
{
    if (status_solenoid_cur == CTRL_SEN_ON)
    {
        drv_gpio_set(CTRL_SEN_PIN_OUT);
    }
    else
    {
        // nothing
        NRF_LOG_FLUSH();
        NRF_LOG_INFO(" Status is off ");
    }
    
    return NRF_SUCCESS;
}

/**
 * @brief : function get status solenoid
 * 
 * @return uint32_t 
 */
uint32_t ctrl_solenoid_getSatatus()
{
    return status_solenoid_cur;
}

/******************************** End of file *********************************/

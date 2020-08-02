/**
 * @file ctrl_readAlarm.c
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
#include "ctrl_readAlarm.h"
#define NRF_LOG_MODULE_NAME ctrl_readA
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
static drv_gpio_cfg_t pin_alarm[] = {
    {PIN_ECU_RESP_LOCKED, DRV_GPIO_ACTIVE_LOW, DRV_GPIO_PULLUP, NULL},
    {PIN_READ_ALARM, DRV_GPIO_ACTIVE_LOW, DRV_GPIO_PULLUP, NULL}
};
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

uint32_t ctrl_readAlarm_init(drv_gpio_handler_t read_alarm_handler)
{
    uint32_t ret;
    // assigned func handler
    for (uint8_t i = 0; i < sizeof(pin_alarm)/sizeof(pin_alarm[0]) ; i++)
    {
        pin_alarm[i].button_handler = read_alarm_handler;
    }

    ret = drv_gpio_init(pin_alarm, sizeof(pin_alarm)/sizeof(pin_alarm[0]));
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

void ctrl_read_Alarm_uninit()
{
    drv_gpio_uninit();
}

/******************************** End of file *********************************/

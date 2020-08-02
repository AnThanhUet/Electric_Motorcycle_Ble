/**
 * @file app_sol.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config_pega.h"
#if PEGA_ESH
#include "ctrl_solenoid.h"
#include "phone.h"
#include "app_sol.h"
#define NRF_LOG_MODULE_NAME app_sol
#include "status.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
#define HEADER_APP_SOL 0x1234
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
void app_sol_handler(ctrl_solenoid_evt_t evt)
{
    switch(evt)
    {
        case APP_SOL_OFF:
            NRF_LOG_FLUSH();
            NRF_LOG_INFO("OFF");
            // phone_sendData();
            break;
        case APP_SOL_ON:
            NRF_LOG_FLUSH();
            NRF_LOG_INFO("ON");
            // phone_sendData();
            break;
        default:
            NRF_LOG_FLUSH();
            NRF_LOG_INFO("warning evt = %d ",evt);
            break;
    }
}

void app_sol_phone_handler(uint8_t *data, uint16_t len)
{
    if (len == 1)
    {
        if (data[0] == 0x01)
        {
            ctrl_solenoid_on();
        }
        else if (data[0] == 0x00)
        {   
            ctrl_solenoid_off();
        }
        else
        {
            NRF_LOG_FLUSH();
            NRF_LOG_INFO("syntax wrong %d",data[0]);
        }
    }
    else
    {
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("syntax wrong %d",len);
    }   
}

void app_sol_init()
{
    char *app_name = "app sold";
    uint32_t err_code;
    err_code = ctrl_solenoid_init(app_sol_handler);
    APP_ERROR_CHECK_SAVY(err_code);
    // register id received data
    phone_add_id(app_name, HEADER_APP_SOL, app_sol_phone_handler);
}

void app_sol_open()
{
    uint32_t err_code;

    err_code = ctrl_solenoid_on();
    APP_ERROR_CHECK_SAVY(err_code);
}

void app_sol_close()
{
    uint32_t err_code;

    err_code = ctrl_solenoid_off();
    APP_ERROR_CHECK_SAVY(err_code);
}

#endif
/******************************** End of file *********************************/

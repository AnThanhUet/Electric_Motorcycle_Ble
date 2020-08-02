/**
 * @file app_sim.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config_pega.h"
#if APP_SIM
#include "app_sim.h"
#include "ctrl_sim.h"
#define NRF_LOG_MODULE_NAME app_sim
#include "status.h"
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

void app_sim_uart_handler(drv_uart_evt_t * p_event)
{
    static uint8_t data_array[100];
    static uint8_t index = 0;
    switch (p_event->evt_type)
    {
    case APP_UART_DATA_READY:
        app_uart_get(&data_array[index]); // received data
        // SEGGER_RTT_printf(0,"%c",data_array[index]); // printf quickly
        
        // if (data_array[index++] == '\n')
        // {
        //     if (str_cmp((char*)data_array,"NRF:",4) != 0)
        //     {
        //         for (uint8_t i = 0; i < index; i++)
        //         {
        //             SEGGER_RTT_printf(0,"%c",data_array[i]);
        //         }
        //     }
        //     index = 0;
        // }
        
        
        break;
    case APP_UART_COMMUNICATION_ERROR:
        break;
    case APP_UART_FIFO_ERROR:
        break;
    default:
        break;
    }
}

void app_sim_init()
{
    uint32_t err_code;
    err_code = ctrl_sim_open(115200, app_sim_uart_handler);
    APP_ERROR_CHECK_SAVY(err_code);
}

#endif
/******************************** End of file *********************************/

/**
 * @file Display_controller.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief s
 * @version 0.1
 * @date 2020-03-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "Display_controll.h"
#include "drv_uart.h"
#define NRF_LOG_MODULE_NAME Display_controll
#include "bsp_pega.h"
#include "status.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
#define TX_DISPLAY  11
#define RX_DISPLAY  12
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

uint32_t Display_controll_open(uint32_t baudRate, drv_uart_handler_t uart_handler)
{
    uint32_t err_code;
    drv_uart_config_t config = {
        .baudRate = baudRate,
        .tx_pin = TX_DISPLAY,
        .rx_pin = RX_DISPLAY,
    };

    err_code = drv_uart_init(config,uart_handler);
    RETURN_IF_ERROR(err_code);
    return NRF_SUCCESS;
}

uint32_t Display_controll_send(char *data, uint16_t len)
{
    uint32_t err_code;

    err_code = drv_uart_write(data,len);
    RETURN_IF_ERROR(err_code);
    return NRF_SUCCESS;
}

uint32_t Display_controll_close()
{
    uint32_t err_code;
    err_code = drv_uart_uninit();
    RETURN_IF_ERROR(err_code);
    return NRF_SUCCESS;
}

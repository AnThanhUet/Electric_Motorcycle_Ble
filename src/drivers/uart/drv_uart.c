/**
 * @file drv_uart.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 13-09-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */

/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "app_uart.h"
#include "nrf_uart.h"
#include "drv_uart.h"
#define NRF_LOG_MODULE_NAME drv_uart
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
#define RTS_DEFAULT 1
#define CTS_DEFAULT 0
#define UART_RX_BUF_SIZE 256
#define UART_TX_BUF_SIZE 256
#define BAUD_RATE_H 269 
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
static uint32_t drv_uart_compute_baudrate(uint32_t baudrate)
{
    return BAUD_RATE_H*baudrate;
}

/**
 * @brief : initalized uart
 * 
 * @param baudrate 
 * @param uart_event_handle 
 * @return uint32_t 
 */
uint32_t drv_uart_init(drv_uart_config_t uart_config, drv_uart_handler_t uart_sim_handler)
{
    uint32_t                     err_code;
    uint32_t                    nrf_baudrate;
    nrf_baudrate = drv_uart_compute_baudrate(uart_config.baudRate);
    app_uart_comm_params_t const comm_params =
    {
        .rx_pin_no    = uart_config.rx_pin,
        .tx_pin_no    = uart_config.tx_pin,
        .rts_pin_no   = RTS_DEFAULT,
        .cts_pin_no   = CTS_DEFAULT,
        .flow_control = APP_UART_FLOW_CONTROL_DISABLED,
        .use_parity   = false,
        .baud_rate    = nrf_baudrate
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_sim_handler,
                       APP_IRQ_PRIORITY_LOW,
                       err_code);
    RETURN_IF_ERROR(err_code);
    return NRF_SUCCESS;
}

/**
 * @brief : send data 
 * 
 * @param data 
 * @param len 
 * @return uint32_t 
 */
uint32_t drv_uart_write(char *data, uint16_t len)
{
    uint32_t err_code;
    for (uint8_t i = 0; i < len; i++)
    {
        err_code = app_uart_put(data[i]);
        RETURN_IF_ERROR(err_code);
    }
    return NRF_SUCCESS;
}

/**
 * @brief : close uart
 * 
 * @return uint32_t 
 */
uint32_t drv_uart_uninit()
{
    uint32_t err_code;
    err_code = app_uart_flush();
    RETURN_IF_ERROR(err_code);
    err_code =  app_uart_close();
    RETURN_IF_ERROR(err_code);
    return NRF_SUCCESS;
}


/******************************** End of file *********************************/

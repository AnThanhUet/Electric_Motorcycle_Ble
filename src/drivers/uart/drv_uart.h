/**
 * @file drv_uart.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 13-09-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "stdint.h"
#include "app_uart.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
#define drv_uart_handler_t  app_uart_event_handler_t
#define drv_uart_evt_t      app_uart_evt_t
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
typedef struct 
{
    uint32_t baudRate;
    uint32_t tx_pin;
    uint32_t rx_pin;
}drv_uart_config_t;
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t drv_uart_init(drv_uart_config_t uart_config, drv_uart_handler_t uart_handler);

uint32_t drv_uart_write(char *data, uint16_t len);

uint32_t drv_uart_uninit();

#ifdef __cplusplus
}
#endif

#endif /* __DRV_UART_H__ */

/******************************** End of file *********************************/

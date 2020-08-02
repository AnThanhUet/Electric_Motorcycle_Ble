/**
 * @file ctrl_sim.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CTRL_SIM_H__
#define __CTRL_SIM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "drv_uart.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t ctrl_sim_open(uint32_t baudRate, drv_uart_handler_t uart_handler);;

uint32_t ctrl_sim_send(char *data, uint16_t len);

uint32_t ctrl_sim_close();


#ifdef __cplusplus
}
#endif

#endif /* __CTRL_SIM_H__ */

/******************************** End of file *********************************/

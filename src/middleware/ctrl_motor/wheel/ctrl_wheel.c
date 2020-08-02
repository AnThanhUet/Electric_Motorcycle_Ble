/**
 * @file ctrl_wheel.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "drv_gpio.h"
#include "drv_uart.h"
#include "timer.h"
#include "ctrl_motor.h"
#include "ctrl_wheel.h"
#define NRF_LOG_MODULE_NAME ctrl_wheel
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
uint32_t ctrl_wheel_init()
{
    
    return NRF_SUCCESS;
}

uint32_t ctrl_wheel_lock()
{

    return NRF_SUCCESS;
}

uint32_t ctrl_wheel_unlock()
{

    return NRF_SUCCESS;
}

/******************************** End of file *********************************/

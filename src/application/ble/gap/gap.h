/**
 * @file gap.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-07-24
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */

#ifndef __GAP_H__
#define __GAP_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "nrf.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "app_timer.h"
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
void log_init(void);

void gap_params_init(void);

void advertising_init(void);

void adv_start();

void adv_stop();
    
#ifdef __cplusplus
}
#endif

#endif /* __GAP_H__ */

/******************************** End of file *********************************/

/**
 * @file gatt.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-07-24
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */

#ifndef __GATT_H__
#define __GATT_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "app_timer.h"
#include "app_util_platform.h"
#include "service_pega.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
#define APP_BLE_CONN_CFG_TAG            1                                           /**< A tag identifying the SoftDevice BLE configuration. */
// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
BLE_ADVERTISING_DEF(m_advertising);
extern bool isConnectDevice;
extern uint16_t   m_conn_handle;
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
void ble_stack_init(void);

void services_init(void);

void gatt_init(void);

void conn_params_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __GATT_H__ */

/******************************** End of file *********************************/

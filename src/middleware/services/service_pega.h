/**
 * @file service_pega.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SERVICE_PEGA_H__
#define __SERVICE_PEGA_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
#define UUID_SERVICE_PEGA      0x0010
#define PEGA_MAX_DATA_LEN       20
#define PEGA_DEF(_name)                                      \
sPega_t _name;                                                         \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                         \
                     2,                                                     \
                     sPega_on_ble_evt, &_name) 
// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

typedef enum
{
    PEGA_EVT_RX_DATA,           /**< Data received. */
    PEGA_EVT_TX_RDY,            /**< Service is ready to accept new data to be transmitted. */
    PEGA_EVT_COMM_STARTED,      /**< Notification has been enabled. */
    PEGA_EVT_COMM_STOPPED,      /**< Notification has been disabled. */
}sPega_evt_type_t;

typedef struct sPega_s sPega_t;

typedef struct 
{
    uint8_t const *p_data;
    uint16_t        len;
}sPega_evt_rx_data_t;

typedef struct 
{
    sPega_evt_type_t type;
    sPega_t          *p_sPega;
    union 
    {
        sPega_evt_rx_data_t rx_data;
    }params;
}sPega_evt_t;

typedef void (*sPega_data_handler_t)(sPega_evt_t *p_evt);

typedef struct 
{
    sPega_data_handler_t sPega_handler;
}sPega_init_t;

struct sPega_s
{
    uint8_t                     uuid_type;              
    uint16_t                    service_handle;          
    ble_gatts_char_handles_t    tx_handles;              
    ble_gatts_char_handles_t    rx_handles;              
    uint16_t                    conn_handle;             
    bool                        is_notification_enabled; 
    sPega_data_handler_t        sPega_handler;            
};

extern sPega_t main_sPega;
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t sPega_init(sPega_t * p_sPega, sPega_init_t const * p_sPega_init);

uint32_t sPega_sendData(sPega_t *p_sPega, uint8_t *data, uint16_t len);

void sPega_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);

#ifdef __cplusplus
}
#endif

#endif /* __SERVICE_PEGA_H__ */

/******************************** End of file *********************************/

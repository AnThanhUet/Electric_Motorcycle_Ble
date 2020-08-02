/**
 * @file service_pega.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "service_pega.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#define NRF_LOG_MODULE_NAME service_pega
#include "status.h"
#include "bsp_pega.h"
#include "config_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
#define UUID_PEGA_RECEIVED_CHARACTERISTIC    0x0012
#define UUID_PEGA_SEND_CHARACTERISTIC        0x0011
#define PEGA_MAX_RECV_DATA_LEN               PEGA_MAX_DATA_LEN
#define PEGA_MAX_SEND_DATA_LEN               PEGA_MAX_DATA_LEN
PEGA_DEF(main_sPega); 
#define PEGA_BASE_UUID                                                                                     \
    {                                                                                                      \
        {                                                                                                  \
            0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x00, 0x00, 0x40, 0x6E \
        }                                                                                                  \
    } /**< Used vendor specific UUID. */
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
static void on_connect(sPega_t *p_sPega,ble_evt_t const *p_ble_evt)
{
    p_sPega->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

static void on_disconnect (sPega_t *p_sPega, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_sPega->conn_handle = BLE_CONN_HANDLE_INVALID;
}

static void on_write(sPega_t *p_sPega, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    sPega_evt_t evt;
    evt.p_sPega = p_sPega;
    if (   (p_evt_write->handle == p_sPega->tx_handles.cccd_handle)
        && (p_evt_write->len == 2))
    {
        if (ble_srv_is_notification_enabled(p_evt_write->data))
        {
            p_sPega->is_notification_enabled = true;
            evt.type = PEGA_EVT_COMM_STARTED;
        }
        else
        {
            p_sPega->is_notification_enabled = false;
            evt.type = PEGA_EVT_COMM_STOPPED;
        }
        p_sPega->sPega_handler(&evt);
    }
    else if (   (p_evt_write->handle == p_sPega->rx_handles.value_handle)
             && (p_sPega->sPega_handler != NULL))
    {
        evt.params.rx_data.p_data = p_evt_write->data;
        evt.params.rx_data.len = p_evt_write->len;
        evt.type = PEGA_EVT_RX_DATA;
        p_sPega->sPega_handler(&evt);
    }
    else
    {
        // Do Nothing. This event is not relevant for this service.
    }
}

static uint32_t sPega_received_char(sPega_t * p_sPega, sPega_init_t const * p_sPega_init)
{
    /**@snippet [Adding proprietary characteristic to the SoftDevice] */
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&cccd_md, 0, sizeof(cccd_md));
    // #if APP_BOND_SECURITY
    // BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&cccd_md.read_perm);
    // BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&cccd_md.write_perm);
    // #else
    // BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    // BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    // #endif
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&cccd_md.write_perm);

    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.notify = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = &cccd_md;
    char_md.p_sccd_md         = NULL;

    ble_uuid.type = p_sPega->uuid_type;
    ble_uuid.uuid = UUID_PEGA_RECEIVED_CHARACTERISTIC;

    memset(&attr_md, 0, sizeof(attr_md));
    #if APP_BOND_SECURITY
    BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&attr_md.write_perm);
    #else
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    #endif
    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen    = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = PEGA_MAX_RECV_DATA_LEN;

    return sd_ble_gatts_characteristic_add(p_sPega->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_sPega->tx_handles);
    /**@snippet [Adding proprietary characteristic to the SoftDevice] */
}

static uint32_t sPega_send_char(sPega_t * p_sPega, const sPega_init_t * p_sPega_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.write         = 1;
    char_md.char_props.write_wo_resp = 1;
    char_md.p_char_user_desc         = NULL;
    char_md.p_char_pf                = NULL;
    char_md.p_user_desc_md           = NULL;
    char_md.p_cccd_md                = NULL;
    char_md.p_sccd_md                = NULL;

    ble_uuid.type = p_sPega->uuid_type;
    ble_uuid.uuid = UUID_PEGA_SEND_CHARACTERISTIC;

    memset(&attr_md, 0, sizeof(attr_md));
    #if APP_BOND_SECURITY
    BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&attr_md.write_perm);
    #else
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    #endif

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen    = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = 1;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = PEGA_MAX_SEND_DATA_LEN;

    return sd_ble_gatts_characteristic_add(p_sPega->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_sPega->rx_handles);
}

void sPega_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    if ((p_context == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    sPega_t *p_sPega = (sPega_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_sPega, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_sPega, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_sPega, p_ble_evt);
            //NRF_LOG_INFO("p_sks.is_notification_enabled = %d",p_sks->is_notification_enabled);
            break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
        {
            //notify with empty data that some tx was completed.
            sPega_evt_t evt = {
                    .type = PEGA_EVT_TX_RDY,
                    .p_sPega = p_sPega
            };
            p_sPega->sPega_handler(&evt);
            break;
        }
        break;
        default:
            // No implementation needed.
            break;
    }
}

uint32_t sPega_init(sPega_t * p_sPega, sPega_init_t const * p_sPega_init)
{
    uint32_t      err_code;
    ble_uuid_t    ble_uuid;
    ble_uuid128_t sPega_base_uuid = PEGA_BASE_UUID;

    VERIFY_PARAM_NOT_NULL(p_sPega);
    VERIFY_PARAM_NOT_NULL(p_sPega_init);

    // Initialize the service structure.
    p_sPega->conn_handle             = BLE_CONN_HANDLE_INVALID;
    p_sPega->sPega_handler            = p_sPega_init->sPega_handler;
    p_sPega->is_notification_enabled = false;

    /**@snippet [Adding proprietary Service to the SoftDevice] */
    // Add a custom base UUID.
    err_code = sd_ble_uuid_vs_add(&sPega_base_uuid, &p_sPega->uuid_type);
    VERIFY_SUCCESS(err_code);

    ble_uuid.type = p_sPega->uuid_type;
    ble_uuid.uuid = UUID_SERVICE_PEGA;

    // Add the service.
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_sPega->service_handle);
    /**@snippet [Adding proprietary Service to the SoftDevice] */
    VERIFY_SUCCESS(err_code);

    // Add the RX Characteristic.
    err_code = sPega_send_char(p_sPega, p_sPega_init);
    VERIFY_SUCCESS(err_code);

    // Add the TX Characteristic.
    err_code = sPega_received_char(p_sPega, p_sPega_init);
    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}

uint32_t sPega_sendData(sPega_t *p_sPega, uint8_t *data, uint16_t len)
{
    ble_gatts_hvx_params_t hvx_params;

    VERIFY_PARAM_NOT_NULL(p_sPega);

    if ((p_sPega->conn_handle == BLE_CONN_HANDLE_INVALID) || (!p_sPega->is_notification_enabled))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (len > PEGA_MAX_DATA_LEN)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_params.handle = p_sPega->tx_handles.value_handle;
    hvx_params.p_data = data;
    hvx_params.p_len  = &len;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;

    return sd_ble_gatts_hvx(p_sPega->conn_handle, &hvx_params);
}


/******************************** End of file *********************************/

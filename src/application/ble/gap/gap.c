/**
 * @file gap.c
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
#include "gap.h"
#include "gatt.h"
#define NRF_LOG_MODULE_NAME gap
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "status.h"
#include "config_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
#define DEVICE_NAME                     "pega_ble"                               /**< Name of device. Will be included in the advertising data. */
#define APP_ADV_INTERVAL                64                                          /**< The advertising interval (in units of 0.625 ms. This value corresponds to 40 ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS      180                                         /**< The advertising timeout (in units of seconds). */
#define MAX_BYTE_ID_MAC                 9
#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(20, UNIT_1_25_MS)             /**< Minimum acceptable connection interval (20 ms), Connection interval uses 1.25 ms units. */
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(75, UNIT_1_25_MS)             /**< Maximum acceptable connection interval (75 ms), Connection interval uses 1.25 ms units. */
#define SLAVE_LATENCY                   0                                           /**< Slave latency. */
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(2000, UNIT_10_MS)             /**< Connection supervisory timeout (4 seconds), Supervision Timeout uses 10 ms units. */
#define DEAD_BEEF                       0xDEADBEEF                                  /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */
#define APP_COMPANY_IDENTIFIER          0x0059                            /**< Company identifier for Nordic Semiconductor ASA. as per www.bluetooth.org. */
#define DEBUG_GAP 1
#define BEACON 0
#define PASS_KEY                        "12345"
#if BEACON
#define APP_BEACON_INFO_LENGTH          0x17                              /**< Total length of information advertised by the Beacon. */
#define APP_ADV_DATA_LENGTH             0x15                              /**< Length of manufacturer specific data in the advertisement. */
#define APP_DEVICE_TYPE                 0x02                              /**< 0x02 refers to Beacon. */
#define APP_MEASURED_RSSI               0xC3                              /**< The Beacon's measured RSSI at 1 meter distance in dBm. */
#define APP_MAJOR_VALUE                 0x01, 0x02                        /**< Major value used to identify Beacons. */
#define APP_MINOR_VALUE                 0x03, 0x04                        /**< Minor value used to identify Beacons. */
#define APP_BEACON_UUID                 0x01, 0x12, 0x23, 0x34, \
                                        0x45, 0x56, 0x67, 0x78, \
                                        0x89, 0x9a, 0xab, 0xbc, \
                                        0xcd, 0xde, 0xef, 0xf0            /**< Proprietary UUID for Beacon. */
#endif
// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
#if BEACON
static uint8_t m_beacon_info[APP_BEACON_INFO_LENGTH] = /**< Information advertised by the Beacon. */
    {
        APP_DEVICE_TYPE,     // Manufacturer specific information. Specifies the device type in this
                             // implementation.
        APP_ADV_DATA_LENGTH, // Manufacturer specific information. Specifies the length of the
                             // manufacturer specific data in this implementation.
        APP_BEACON_UUID,     // 128 bit UUID value.
        APP_MAJOR_VALUE,     // Major arbitrary value that can be used to distinguish between Beacons.
        APP_MINOR_VALUE,     // Minor arbitrary value that can be used to distinguish between Beacons.
        APP_MEASURED_RSSI    // Manufacturer specific information. The Beacon's measured TX power in
                             // this implementation.
};
#endif
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
// static ble_opt_t m_static_pin_option;
static uint8_t arr_id[MAX_BYTE_ID_MAC];     // array id mac
static uint8_array_t id_mac = {MAX_BYTE_ID_MAC,arr_id};
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * @brief : function get id mac
 * 
 */
static void gap_get_id_mac()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        arr_id[i] = (uint8_t)(NRF_FICR->DEVICEID[0] >> 8*(3-i));
    }
    
    for (uint8_t i = 4; i < 8; i++)
    {
        arr_id[i] = (uint8_t)(NRF_FICR->DEVICEID[1] >> 8*(7-i));
    }
    // arr_id[8] = DEVICE_TYPE;
}

/**@brief Function for initializing the nrf log module.
 */
void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK_SAVY(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Function for assert macro callback.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyse
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in] line_num    Line number of the failing ASSERT call.
 * @param[in] p_file_name File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t *p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}


/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
static void on_adv_evt(ble_adv_evt_t ble_adv_evt)
{
    switch (ble_adv_evt)
    {
    case BLE_ADV_EVT_FAST:
        #if DEBUG_GAP
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("advertising !!!");
        #endif
        break;
    case BLE_ADV_EVT_IDLE:
        adv_start();
        break;
    default:
        break;
    }
}

/**@brief Function for initializing the Advertising functionality.
 */
void advertising_init(void)
{
    uint32_t err_code;
    ble_advertising_init_t init;
    ble_advdata_manuf_data_t manuf_savy;

    gap_get_id_mac();
    manuf_savy.company_identifier = APP_COMPANY_IDENTIFIER;
    manuf_savy.data = id_mac;
    
    memset(&init, 0, sizeof(init));

    init.advdata.name_type = BLE_ADVDATA_FULL_NAME;
    init.advdata.include_appearance = false;
    init.advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE;
    init.advdata.p_manuf_specific_data = &manuf_savy;

    //init.srdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    //init.srdata.uuids_complete.p_uuids  = m_adv_uuids;

    init.config.ble_adv_fast_enabled = true;
    init.config.ble_adv_fast_interval = APP_ADV_INTERVAL;
    init.config.ble_adv_fast_timeout = APP_ADV_TIMEOUT_IN_SECONDS;

    init.evt_handler = on_adv_evt;

    err_code = ble_advertising_init(&m_advertising, &init);
    APP_ERROR_CHECK_SAVY(err_code);

    ble_advertising_conn_cfg_tag_set(&m_advertising, APP_BLE_CONN_CFG_TAG);
}

/**@brief Function for the GAP initialization.
 *
 * @details This function will set up all the necessary GAP (Generic Access Profile) parameters of
 *          the device. It also sets the permissions and appearance.
 */
void gap_params_init(void)
{
    uint32_t err_code;
    ble_gap_conn_params_t gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;
    #if APP_BOND_SECURITY
    BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(&sec_mode);
    #else
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    #endif

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *)DEVICE_NAME,
                                          strlen(DEVICE_NAME));
    APP_ERROR_CHECK_SAVY(err_code);

    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK_SAVY(err_code);
    #if APP_BOND_SECURITY
    ble_gap_opt_t gap_opt;
                                          
    gap_opt.passkey.p_passkey = (uint8_t *)"123456";  
 
    err_code = sd_ble_opt_set(BLE_GAP_OPT_PASSKEY,(const ble_opt_t *)&gap_opt); 
    APP_ERROR_CHECK_SAVY(err_code); 
    #endif
}

/**
 * @brief : advertising start 
 * 
 * @return void 
 */
void adv_start()
{
    uint32_t ret;
    // NRF_LOG_FLUSH();
    // NRF_LOG_INFO("advertising on");
    ret = ble_advertising_start(&m_advertising, BLE_ADV_MODE_FAST);
    APP_ERROR_CHECK_SAVY(ret);
}

/**
 * @brief : stop advertising
 * 
 * @return void 
 */
void adv_stop()
{
    uint32_t ret;
    // NRF_LOG_FLUSH();
    // NRF_LOG_INFO("advertising off");
    ret = sd_ble_gap_adv_stop();
    APP_ERROR_CHECK_SAVY(ret);
}

/******************************** End of file *********************************/

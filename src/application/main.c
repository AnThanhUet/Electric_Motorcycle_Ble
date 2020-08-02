/**
 * @file main.c
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
#include <stdint.h>
#include "oled.h"
#include "config_pega.h"
#include "pega_eSH.h"
#include "peer.h"
#ifdef TEST
#include "test.h"
#endif
#define NRF_LOG_MODULE_NAME main
#include "status.h"
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

/**@brief Function for placing the application in low power state while waiting for events.
 */
static void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK_SAVY(err_code);
}


static void timer_init()
{
    uint32_t err_code;
    err_code = app_timer_init();
    APP_ERROR_CHECK_SAVY(err_code);
}

/**@brief Application main function.
 */
int main(void)
{
    timer_init();
    log_init();
    ble_stack_init();
    gap_params_init();
    gatt_init();
    #if APP_BOND_SECURITY
    peer_manager_init();
    #endif
    services_init();
    advertising_init();
    conn_params_init();
    adv_start();
    NRF_LOG_FLUSH();
    NRF_LOG_INFO("DISPLAY PEAGA");
    #if TEST
    test();
    #endif
    //pega_eSH_init();
    // delete_bonds();
    for (;;)
    {
        //oled_show();
        //UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
        power_manage();
    }
}
/******************************** End of file *********************************/
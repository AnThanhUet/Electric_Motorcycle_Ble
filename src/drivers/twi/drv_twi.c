/**
 * @file drv_twi.c
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-07-26
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include <stdio.h>
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"
#define NRF_LOG_MODULE_NAME drv_twi
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
/* TWI instance ID. */
#define TWI_INSTANCE_ID     0
 /* Number of possible TWI addresses. */
#define TWI_ADDRESSES       127

// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
/**
 * @brief TWI initialization.
 */
void drv_twi_init (uint32_t SCL, uint32_t SDA)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = SCL,
       .sda                = SDA,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    APP_ERROR_CHECK_SAVY(err_code);

    nrf_drv_twi_enable(&m_twi);
}

void drv_twi_scan(void)
{
    uint8_t address;
    uint8_t sample_data;
    uint8_t err_code;
    bool detected_device = false;   // 
    for (address = 1; address <= TWI_ADDRESSES; address++)
    {
        err_code = nrf_drv_twi_rx(&m_twi, address, &sample_data, sizeof(sample_data));
        if (err_code == NRF_SUCCESS)
        {
            detected_device = true;
            NRF_LOG_FLUSH();
            NRF_LOG_INFO("TWI device detected at address 0x%x.", address);
            NRF_LOG_FLUSH();
            NRF_LOG_INFO("sample_data %d.", sample_data);
            NRF_LOG_FLUSH();
        }
        NRF_LOG_FLUSH();
    }

    if (!detected_device)
    {
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("No device was found.");
        NRF_LOG_FLUSH();
    }
}

/**
 * @brief : function i2c read
 * 
 * @param address 
 * @param p_data 
 * @param lenght 
 * @return uint32_t 
 */
uint32_t drv_twi_read(uint8_t address, uint8_t *p_data, uint16_t lenght)
{
    uint32_t ret;
    ret = nrf_drv_twi_rx(&m_twi, address, p_data, lenght);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

/**
 * @brief : function i2c write
 * 
 * @param address 
 * @param p_data 
 * @param length 
 * @return uint32_t 
 */
uint32_t drv_twi_write(uint8_t address, uint8_t *p_data, uint8_t length)
{
    uint32_t ret;
    ret = nrf_drv_twi_tx(&m_twi, address, p_data, length, false);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

/******************************** End of file *********************************/


/**
 * @file drv_spi.c
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
#include "sdk_common.h"
#include "nrf_drv_spi.h"
#define NRF_LOG_MODULE_NAME drv_spi
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
#define DEBUG_DRV_SPI   0  // debug file drv_spi
// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(1);
/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * @brief : function spi handler
 * 
 * @param p_event 
 * @param p_context 
 */
void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{
    #if DEBUG_DRV_SPI
    NRF_LOG_INFO("Transfer completed.");
    #endif // end 
    
}

/**
 * @brief : function initialized spi
 * 
 * @return uint32_t 
 */
uint32_t drv_spi_init(uint32_t SS, uint32_t MISO, uint32_t MOSI, uint32_t SCK)
{
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin   = SS;
    spi_config.miso_pin = MISO;
    spi_config.mosi_pin = MOSI;
    spi_config.sck_pin  = SCK;
    RETURN_IF_ERROR(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));
    return NRF_SUCCESS;
}

/**
 * @brief : fucntion uninitializing spi
 * 
 */
void drv_spi_uninit ()
{
    nrf_drv_spi_uninit(&spi);
}

/**
 * @brief : send data spi
 * 
 * @param data 
 * @param size 
 * @return uint32_t 
 */
uint32_t drv_spi_write(uint8_t *data, size_t size)
{
    RETURN_IF_ERROR(nrf_drv_spi_transfer(&spi, data, size, NULL, 0));
    return NRF_SUCCESS;
}

/******************************** End of file *********************************/

/**
 * @file drv_spi.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include <stddef.h>
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
uint32_t drv_spi_init(uint32_t SS, uint32_t MISO, uint32_t MOSI, uint32_t SCK);

void drv_spi_uninit ();

uint32_t drv_spi_write(uint8_t *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */

/******************************** End of file *********************************/

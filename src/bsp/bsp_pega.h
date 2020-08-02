/**
 * @file bsp_pega.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __BSP_PEGA_H__
#define __BSP_PEGA_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/

/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
// module oled sh1106
#define SH1106_SPI_SS       11
#define SH1106_SPI_MISO     4
#define SH1106_SPI_MOSI     5
#define SH1106_SPI_SCK      6
#define SH1106_RES          7
#define SH1106_DC           8

#define ECU_SEN_OUT         20
#define ECU_SEN_IN          16
// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __BSP_PEGA_H__ */

/******************************** End of file *********************************/

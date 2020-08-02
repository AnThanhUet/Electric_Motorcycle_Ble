/**
 * @file drv_twi.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-07-26
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __DRV_TWI_H__
#define __DRV_TWI_H__

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

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
void drv_twi_init(uint32_t SCL, uint32_t SDA);

void drv_twi_scan(void);

uint32_t drv_twi_read(uint8_t address, uint8_t const * p_data, uint16_t lenght);

uint32_t drv_twi_write(uint8_t address, uint8_t const *p_data, uint8_t length);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_TWI_H__ */

/******************************** End of file *********************************/


/**
 * @file lis3dh.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-08-01
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __LIS3DH_H__
#define __LIS3DH_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "stdint.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
typedef struct 
{
    uint8_t lis3dh_xl;
    uint8_t lis3dh_xh;
    uint8_t lis3dh_yl;
    uint8_t lis3dh_yh;
    uint8_t lis3dh_zl;
    uint8_t lis3dh_zh;
}lis3dh_axis_t;

typedef struct 
{
    float xAcc;
    float yAcc;
    float zAcc;
}acc_t;
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t lis3dh_init();

uint32_t lis3dh_setupInit();

uint32_t lis3dh_setupCfg();

uint32_t lis3dh_write_regs(uint8_t address_start, uint8_t *data, uint16_t len);

uint32_t lis3dh_write_reg(uint8_t address_reg, uint8_t data);

uint32_t lis3dh_read_reg(uint8_t address_reg, uint8_t *data);

uint32_t lis3dh_verify_id();

uint32_t lis3dh_setupInt1();

acc_t lis3dh_read_axis();

void test();

#ifdef __cplusplus
}
#endif

#endif /* __LIS3DH_H__ */

/******************************** End of file *********************************/

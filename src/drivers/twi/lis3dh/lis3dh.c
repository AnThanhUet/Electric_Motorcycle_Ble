/**
 * @file lis3dh.c
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-08-01
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "lis3dh.h"
#include "drv_twi.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "bsp_smk.h"
#include "drv_gpiote.h"
#define NRF_LOG_MODULE_NAME lis3dh
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define DEBUG_LIS3DH 0

#define LIS3DH_SCL SENSOR_LIS3DH_SCL
#define LIS3DH_SDA SENSOR_LIS3DH_SDA
#define LIS3DH_CS   SENSOR_LISA3DH_CS

// clang-format off
#define LISH3DH_ADDR        0x19
/* auxiliary status */
#define STATUS_AUX          0x07    // r

/* detect lis3dh */
#define WHO_AM_I            0x0F    // r
#define I_AM_LIS3DH         0x33  // indentify 

/* register control */
#define CTRL_REG0           0x1E    // rw
#define TEMP_CFG_REG        0x1F    // rw
#define CTRL_REG1           0x20    // rw
#define CTRL_REG2           0x21    // rw
#define CTRL_REG3           0x22    // rw
#define CTRL_REG6           0x25    // rw
#define CTRL_REG4           0x23    // rw
#define CTRL_REG5           0x24    // rw
#define REFERENCE           0x26    // rw
#define STATUS_REG          0x27    // r

/* register out X, Y. Z */
#define OUT_X_L             0x28    // r
#define OUT_X_H             0x29    // r
#define OUT_Y_L             0x2A    // r
#define OUT_Y_H             0x2B    // r
#define OUT_Z_L             0x2C    // r
#define OUT_Z_H             0x2D    // r

/* FIFO */
#define FIFO_CTRL_REG       0x2E    // rw
#define FIFO_SRC_REG        0x2F    // r

/* INT1 */
#define INT1_CFG            0x30    // rw
#define INT1_SRC            0x31    // r
#define INT1_THS            0x32    // rw
#define INT1_DURATION       0x33    // rw

/* INT2 */
#define INT2_CFG            0x37    // 
#define INT2_SRC            0x38
#define INT2_THS            0x39
#define INT2_DURATION       0x3A

/*  */
#define CLICK_CFG           0x38
#define CLICK_SRC           0x39
#define CLICK_THS           0x3a
#define TIME_LIMIT          0x3b
#define TIME_LATENCY        0x3c
#define TIME_WINDOW         0x3d
#define ACT_THS             0x3e
#define ACT_DUR             0x3f

#define g 0.061/1000
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
acc_t lis3dh_read_axis()
{
    lis3dh_axis_t lis3dh_axis;
    uint16_t x, y, z;
    acc_t acc_value;

    lis3dh_read_reg(OUT_X_L, &lis3dh_axis.lis3dh_xl);
    lis3dh_read_reg(OUT_X_H, &lis3dh_axis.lis3dh_xh);
    lis3dh_read_reg(OUT_Y_L, &lis3dh_axis.lis3dh_yl);
    lis3dh_read_reg(OUT_Y_H, &lis3dh_axis.lis3dh_yh);
    lis3dh_read_reg(OUT_Z_L, &lis3dh_axis.lis3dh_zl);
    lis3dh_read_reg(OUT_Z_H, &lis3dh_axis.lis3dh_zh);
#if DEBUG_LIS3DH
    NRF_LOG_FLUSH();
    NRF_LOG_INFO(" Accelerometer :");
    NRF_LOG_FLUSH();
#endif
    x = (lis3dh_axis.lis3dh_xl | (lis3dh_axis.lis3dh_xh << 8));
    y = lis3dh_axis.lis3dh_yl | (lis3dh_axis.lis3dh_yh << 8);
    z = lis3dh_axis.lis3dh_zl | (lis3dh_axis.lis3dh_zh << 8);

    acc_value.xAcc = x < 32768 ? x * g : ((x - 65536) * g);
    acc_value.yAcc = y < 32768 ? y * g : ((y - 65536) * g);
    acc_value.zAcc = z < 32768 ? z * g : ((z - 65536) * g);
#if DEBUG_LIS3DH
    NRF_LOG_FLUSH();
    NRF_LOG_INFO(" Gx = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(acc_value.xAcc));
    NRF_LOG_FLUSH();
    NRF_LOG_INFO(" Gy = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(acc_value.yAcc));
    NRF_LOG_FLUSH();
    NRF_LOG_INFO(" Gz = " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(acc_value.zAcc));
    NRF_LOG_FLUSH();
#endif
    return acc_value;
}

uint32_t lis3dh_verify_id()
{
    uint32_t ret;
    uint8_t lis3dh_id;
    ret = lis3dh_read_reg(WHO_AM_I, &lis3dh_id);
    if (ret == NRF_SUCCESS && lis3dh_id == I_AM_LIS3DH)
    {
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("LIS3DH sensor.");
        NRF_LOG_FLUSH();
        return NRF_SUCCESS;
    }
    else
    {
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("No device.");
        NRF_LOG_FLUSH();
    }
    return ret;
}

uint32_t lis3dh_read_reg(uint8_t address_reg, uint8_t *data)
{
    uint32_t ret;
    ret = drv_twi_write(LISH3DH_ADDR, &address_reg, 1);

    nrf_delay_ms(10);
    ret = drv_twi_read(LISH3DH_ADDR, data, 1);
    RETURN_IF_ERROR(ret)
    return NRF_SUCCESS;
}

uint32_t lis3dh_write_reg(uint8_t address_reg, uint8_t data)
{
    uint32_t ret;
    uint8_t reg[2];
    reg[0] = address_reg;
    reg[1] = data;
    ret = drv_twi_write(LISH3DH_ADDR, reg, sizeof(reg));
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

uint32_t lis3dh_write_regs(uint8_t address_start, uint8_t *data, uint16_t len)
{
    uint32_t ret;
    uint8_t *reg;
    reg = (uint8_t *)malloc(len);
    reg[0] = address_start;
    for (uint8_t i = 1; i < len; i++)
    {
        reg[i] = data[i];
    }
    ret = drv_twi_write(LISH3DH_ADDR, reg, len);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

uint32_t lis3dh_setupCfg()
{
    uint32_t ret;
    uint8_t cfg_regs[6] = {0x57, 0x01, 0x40, 0x00, 0x00, 0x00};
    for (uint8_t i = 0; i < sizeof(cfg_regs); i++)
    {
        ret = lis3dh_write_reg(CTRL_REG1 + i, cfg_regs[i]);
        RETURN_IF_ERROR(ret);
    }
    return NRF_SUCCESS;
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t lis3dh_setupInt1()
{
    uint32_t ret;
    uint8_t int_regs[4] = {0x72, 0x00, 0x10, 0x00}; // direction x, thred
    for (uint8_t i = 0; i < sizeof(int_regs); i++)
    {
        ret = lis3dh_write_reg(INT1_CFG + i, int_regs[i]);
        RETURN_IF_ERROR(ret);
    }
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t lis3dh_setupInit()
{
    uint32_t ret;
    uint8_t cfg_init1[4] = {0x00, 0x00, 0x00, 0x00};
    ret = lis3dh_write_regs(CTRL_REG1, cfg_init1, sizeof(cfg_init1));
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}


/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t lis3dh_init()
{
    uint32_t ret;
    // gpio_cfg_out(SENSOR_LISA3DH_CS);
    // gpio_set(SENSOR_LISA3DH_CS);
    drv_twi_init(LIS3DH_SCL, LIS3DH_SDA);
    /*  indentify lis3dh */
    ret = lis3dh_verify_id();
    RETURN_IF_ERROR(ret);

    /* setup reg for lis3dh */
    ret = lis3dh_setupCfg();
    RETURN_IF_ERROR(ret);

    /* initialized interrupt */
    ret = lis3dh_setupInt1();
    RETURN_IF_ERROR(ret);

    return NRF_SUCCESS;
}

/******************************** End of file *********************************/

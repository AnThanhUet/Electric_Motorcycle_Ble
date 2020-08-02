/**
 * @file drv_oled.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __DRV_OLED_H__
#define __DRV_OLED_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off


// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
/* COLOR for Display */
typedef enum 
{
    WHITE,
    BLACK,
    INVERSE
}sh1106_color_t;

typedef enum{
    CTRL_OLED_ROTATE_0 = 0,       /**< Rotate 0 degrees, clockwise. */
    CTRL_OLED_ROTATE_90,          /**< Rotate 90 degrees, clockwise. */
    CTRL_OLED_ROTATE_180,         /**< Rotate 180 degrees, clockwise. */
    CTRL_OLED_ROTATE_270          /**< Rotate 270 degrees, clockwise. */
}drv_oled_rotation_t;

typedef struct 
{
    uint16_t height;
    uint16_t width;
    drv_oled_rotation_t rotation;
}drv_oled_cb_t;


typedef struct 
{
    uint32_t (*drv_oled_init)(void);

    void (*drv_oled_uninit)(void);

    uint32_t (*drv_oled_pixel_draw)(uint16_t x, uint16_t y, uint32_t color);

    void (*drv_oled_rect_draw)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

    void (*drv_oled_display)(void);

    void (*drv_oled_clearDisplay)(void);

    void (*drv_oled_rotation_set)(drv_oled_rotation_t rotation);

    void (*drv_oled_invert)(bool invert);

    void (*drv_oled_showCompany)(void);

    uint32_t (*drv_oled_setChar)(uint16_t x, uint16_t y, char data);

    void (*drv_oled_drawBitMap)(uint16_t x, uint16_t y, uint16_t widthBitMap, uint16_t heightBitMap, const char *bitmap);

    drv_oled_cb_t *p_drv_oled;

}drv_oled_t;

extern const drv_oled_t drv_oled_sh1106;
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __DRV_OLED_H__ */

/******************************** End of file *********************************/

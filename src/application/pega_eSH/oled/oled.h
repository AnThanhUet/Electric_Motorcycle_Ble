/**
 * @file oled.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __OLED_H__
#define __OLED_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
enum
{
    OLED_UNIT_METER = 0,
    OLED_UNIT_KILOMETER,
    OLED_UNIT_HOUR,
    OLED_UNIT_MIN,
    OLED_UNIT_KM_H,
    OLED_UNIT_M_S
}oled_unit_t;

enum
{
    OLED_TURN_LEFT,
    OLED_TURN_RIGHT,
    OLED_GO_STRAIGTH,
}oled_dir_t;
// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
void oled_init();

void oled_show();

void oled_invert(bool invert);

void oled_tab1();

void oled_close_allTab();

void oled_clearDiplay();

void oled_showCompany();

void oled_set_dir_tab1(uint8_t dir);

void oled_tab1_update(char *distance, uint8_t len_dis, uint16_t time, uint8_t direct);

#ifdef __cplusplus
}
#endif

#endif /* __OLED_H__ */

/******************************** End of file *********************************/

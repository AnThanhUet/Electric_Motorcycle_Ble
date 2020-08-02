/**
 * @file ctrl_oled.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CTRL_OLED_H__
#define __CTRL_OLED_H__

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
// list device

// oled modules

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t ctrl_oled_init();

void ctrl_oled_show();

void ctrl_oled_invert(bool invert);

void ctrl_oled_clearDisplay();

void ctrl_oledCompany();

void ctrl_oled_setChar(uint16_t x_cursor, uint16_t y_cursor, char s);

void ctrl_oled_setString(uint16_t x_cursor, uint16_t y_cursor, char *s, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* __CTRL_OLED_H__ */

/******************************** End of file *********************************/

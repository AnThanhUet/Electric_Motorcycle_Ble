/**
 * @file oled_lib.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __OLED_LIB_H__
#define __OLED_LIB_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
/* show distance */
#define OLED_DISTANCE_X         0
#define OLED_DISTANCE_Y         30
#define OLED_DISTANCE_MAX_UNIT  5
// time
#define OLED_TIME_X             10
#define OLED_TIME_Y             15
#define OLED_TIME_UNIT          26
#define OLED_TIME_MAX_UNIT      2
// Start and destination
#define OLED_START_X            0
#define OLED_START_Y            0
#define OLED_DEST_X             0
#define OLED_DEST_Y             55  
// speed
#define OLED_SPEED_X            5
#define OLED_SPEED_Y            45
#define OLED_SPEED_UNIT_X       24
#define OLED_SPEED_MAX_UNIT     3

// 16 right
// 17 left
// 18 2 mui ten
// 24 mui ten len
// 25 mui ten xuong
// 26 mui ten sang phai
// 27 mui ten sang trai
// 30 up
// 32 down
#define OLED_DIR_RIGHT  26
#define OLED_DIR_LEFT   27
#define OLED_DIR_UP     24

#define OLED_TIMEOUT    50
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

#endif /* __OLED_LIB_H__ */

/******************************** End of file *********************************/

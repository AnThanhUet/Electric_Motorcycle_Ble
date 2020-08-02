/**
 * @file sh1106.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SH1106_H__
#define __SH1106_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "drv_oled.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
#define I2C 0
#define SPI 1

#define TYPE_PROTOCOL SPI
// size of display
#define SH1106_LCDWIDTH                  128
#define SH1106_LCDHEIGHT                 64
// register sh1106
#define SH1106_SETCONTRAST          0x81    // set contract
#define SH1106_DISPLAYALLON_RESUME  0xA4    // display all on resume
#define SH1106_DISPLAYALLON         0xA5    // display all ON            
#define SH1106_NORMALDISPLAY        0xA6    // normal display
#define SH1106_INVERTDISPLAY        0xA7    // invert display
#define SH1106_DISPLAYOFF           0xAE    // display OFF
#define SH1106_DISPLAYON            0xAF    // display ON
#define SH1106_SETDISPLAYOFFSET     0xD3    // set display offset
#define SH1106_SETCOMPINS           0xDA    // set COMPINS
#define SH1106_SETVCOMDETECT        0xDB    // set Vcom Detect
#define SH1106_SETDISPLAYCLOCKDIV   0xD5    // set display clock divide
#define SH1106_SETPRECHARGE         0xD9    // set precharge
#define SH1106_SETMULTIPLEX         0xA8    // set multiplex
#define SH1106_SETLOWCOLUMN         0x00    // set low column
#define SH1106_SETHIGHCOLUMN        0x10    // set high column
#define SH1106_SETSTARTLINE         0x40    // set start line
#define SH1106_SETPAGEADDRESS       0xB0    // set page address
#define SH1106_MEMORYMODE           0x20    // memory mode
#define SH1106_COLUMNADDR           0x21    // column address
#define SH1106_PAGEADDR             0x22    // page address
#define SH1106_COMSCANINC           0xC0    // COM 
#define SH1106_COMSCANDEC           0xC8    // 
#define SH1106_SEGREMAP             0xA0    // Segment remap
#define SH1106_CHARGEPUMP           0x8D    // charge pump
#define SH1106_EXTERNALVCC          0x1     // External vcc
#define SH1106_SWITCHCAPVCC         0x2     // switch vcc

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

#endif /* __SH1106_H__ */

/******************************** End of file *********************************/

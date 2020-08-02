/**
 * @file sh1106.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "sh1106.h"
#include "drv_spi.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "sh1106_lib.h"
#include "drv_oled.h"
#define NRF_LOG_MODULE_NAME sh1106
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
// Protocol type
#define sh1106_swap(a, b) { int16_t t = a; a = b; b = t; }
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
uint8_t buffer[SH1106_LCDHEIGHT * SH1106_LCDWIDTH / 8] ;

static uint8_t bitRead(char x, uint8_t n)
{
    x >>= n;
    if (x % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief : function send command oled
 * 
 * @param c 
 */
static inline void sh1106_write_command(uint8_t c)
{
    #if TYPE_PROTOCOL == SPI  // spi
    nrf_gpio_pin_clear(SH1106_DC);
    drv_spi_write(&c, 1);
    nrf_delay_us(10); 
    #elif TYPE_PROTOCOL == I2C // i2c
    // nothing
    #endif
}

/**
 * @brief : function send data oled
 * 
 * @param c 
 */
static inline void sh1106_write_data(uint8_t c)
{
    #if TYPE_PROTOCOL == SPI   // spi
    nrf_gpio_pin_set(SH1106_DC);
    drv_spi_write(&c, 1);
    nrf_delay_us(10);
    #elif TYPE_PROTOCOL == I2C // i2c
    // nothing
    #endif
}

/**
 * @brief : function setup params oled
 * 
 * @param vccstate  : external vcc
 */
static void sh1106_write_command_list(uint8_t vccstate)
{
    nrf_gpio_pin_set(SH1106_RES);
    nrf_delay_ms(10);
    nrf_gpio_pin_clear(SH1106_RES);
    nrf_delay_ms(10);
    nrf_gpio_pin_set(SH1106_RES);
    nrf_delay_ms(10);
    // Init sequence for 128x64 OLED module
    sh1106_write_command(SH1106_DISPLAYOFF);                    // 0xAE
    sh1106_write_command(SH1106_SETDISPLAYCLOCKDIV);            // 0xD5
    sh1106_write_command(0x80);                                  // the suggested ratio 0x80
    sh1106_write_command(SH1106_SETMULTIPLEX);                  // 0xA8
    sh1106_write_command(0x3F);
    sh1106_write_command(SH1106_SETDISPLAYOFFSET);              // 0xD3
    sh1106_write_command(0x00);                                   // no offset
	
    sh1106_write_command(SH1106_SETSTARTLINE | 0x0);            // line #0 0x40
    sh1106_write_command(SH1106_CHARGEPUMP);                    // 0x8D
    if (vccstate == SH1106_EXTERNALVCC) 
      { sh1106_write_command(0x10); }
    else 
      { sh1106_write_command(0x14); }
    sh1106_write_command(SH1106_MEMORYMODE);                    // 0x20
    sh1106_write_command(0x00);                                  // 0x0 act like ks0108
    sh1106_write_command(SH1106_SEGREMAP | 0x1);
    sh1106_write_command(SH1106_COMSCANDEC);
    sh1106_write_command(SH1106_SETCOMPINS);                    // 0xDA
    sh1106_write_command(0x12);
    sh1106_write_command(SH1106_SETCONTRAST);                   // 0x81
    if (vccstate == SH1106_EXTERNALVCC) 
      { sh1106_write_command(0x9F); }
    else 
      { sh1106_write_command(0xCF); }
    sh1106_write_command(SH1106_SETPRECHARGE);                  // 0xd9
    if (vccstate == SH1106_EXTERNALVCC) 
      { sh1106_write_command(0x22); }
    else 
      { sh1106_write_command(0xF1); }
    sh1106_write_command(SH1106_SETVCOMDETECT);                 // 0xDB
    sh1106_write_command(0x40);
    sh1106_write_command(SH1106_DISPLAYALLON_RESUME);           // 0xA4
    sh1106_write_command(SH1106_NORMALDISPLAY);                 // 0xA6
    sh1106_write_command(SH1106_DISPLAYON);
    // NRF_LOG_FLUSH();
    // NRF_LOG_INFO("end command list");
}

/**
 * @brief : function display normal or display
 * 
 * @param invert 
 */
void sh1106_display_invert(bool invert)
{
    if (invert) //  dispaly invert
    {
        sh1106_write_command(SH1106_INVERTDISPLAY);
    }
    else   // display normal
    {
        sh1106_write_command(SH1106_NORMALDISPLAY);
    }
    
}

/**
 * @brief : function display show
 * 
 */
void sh1106_display()
{
    static uint8_t init = 1;
    uint8_t height = SH1106_LCDHEIGHT;
    uint8_t width = SH1106_LCDWIDTH;
    uint8_t m_row = 0;
    uint8_t m_col = 2;

    height >>= 3;
    width >>= 3;

    uint32_t p = 0;
    if (init)
    {
        init = 0;
        sh1106_write_command(SH1106_SETLOWCOLUMN | 0x00);
        sh1106_write_command(SH1106_SETHIGHCOLUMN | 0x00);
        sh1106_write_command(SH1106_SETSTARTLINE | 0x00);
    }
    

    for (int i = 0; i < height; i++)
    {
        sh1106_write_command(SH1106_SETPAGEADDRESS + i + m_row);
        sh1106_write_command(m_col & 0xf);
        sh1106_write_command(0x10 | (m_col >> 4));
        for (int j = 0 ; j < 8; j++)
        {
            for (int k = 0; k < width; k++, p++)
            {
                sh1106_write_data(buffer[p]);
            }
        }
    }
}

/**
 * @brief : function set buff = data
 * 
 */
static void sh1106_setFullScreen(uint8_t data)  
{
    memset(buffer,data,SH1106_LCDHEIGHT * SH1106_LCDWIDTH / 8);
}

/**
 * @brief clear display
 * 
 */
static void sh1106_clear_display()
{
    sh1106_setFullScreen(0x00);  // BLACK ALL
}

/**
 * @brief : function set ever pixel
 * 
 * @param x 
 * @param y 
 * @param color 
 * @return uint32_t 
 */
static uint32_t sh1106_drawPixel(uint16_t x, uint16_t y, uint32_t color)
{
    if ((x < 0) || (x >= SH1106_LCDWIDTH) || (y < 0) || (y >= SH1106_LCDHEIGHT))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    switch (color)
    {
    case WHITE:
        buffer[x + (y/8)*128] |=  (1 << (y&7));
        break;
    case BLACK:
        buffer[x + (y/8)*128] &= ~(1 << (y&7));
        break;
    case INVERSE:
        buffer[x + (y/8)*128] ^=  (1 << (y&7));
        break;
    default:
        break;
    }
    return NRF_SUCCESS;
}

static void sh1106_showCompany()
{
    for (int i = 0; i < SH1106_LCDHEIGHT * SH1106_LCDWIDTH / 8;i++)
    {
        buffer[i] = company[i];
    }
}

static void sh1106_rect_draw(uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint32_t color)
{

}

static void sh1106_rotation_set(drv_oled_rotation_t rotation)
{

}

static uint32_t sh1106_setChar(uint16_t x, uint16_t y, char data)
{
    if ((x > SH1106_LCDWIDTH - 5) || (y > SH1106_LCDHEIGHT - 7))
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    uint8_t count = (uint8_t)data;
    char *strs = &font5x7[count*5];
    for (uint32_t j = 0; j < 5; j++)
    {
        for(uint8_t  i = 0; i < 8; i++)
        {   
            if (bitRead(strs[j], i))
            {
                sh1106_drawPixel(x + j, y + i, WHITE);
            }
            else
            {
                sh1106_drawPixel(x + j, y + i, BLACK);
            }
        }
    }
    return NRF_SUCCESS;
}

static void sh1106_drawBitMap(uint16_t x, uint16_t y, uint16_t widthBitMap, uint16_t heightBitMap, const char *bitmap)
{
    for (uint16_t i = 0; i < widthBitMap; i++)
    {
        for (uint16_t j = 0; j < heightBitMap; j++)
        {
            if (bitRead(bitmap[j], i))
            {
                sh1106_drawPixel(x + j, y + i, WHITE);
            }
            else
            {
                sh1106_drawPixel(x + j, y + i, BLACK);
            }
        }
    }
}

static void sh1106_uninit()
{
    drv_spi_uninit();
}


static uint32_t sh1106_init()
{
    uint32_t err_code;
    // configure output RES DC
    nrf_gpio_cfg_output(SH1106_RES);
    nrf_gpio_cfg_output(SH1106_DC);
    // initialized spi
    err_code = drv_spi_init(SH1106_SPI_SS,
                            SH1106_SPI_MISO,
                            SH1106_SPI_MOSI,
                            SH1106_SPI_SCK);
    RETURN_IF_ERROR(err_code);
    // command list setup params oled
    sh1106_write_command_list(0x01);
    // clear
    sh1106_clear_display();

    return NRF_SUCCESS; // success
}   

static drv_oled_cb_t sh1106_cb = {
    .height = SH1106_LCDHEIGHT,
    .width = SH1106_LCDWIDTH
};

const drv_oled_t drv_oled_sh1106 = {
    .drv_oled_init = sh1106_init,
    .drv_oled_uninit = sh1106_uninit,
    .drv_oled_clearDisplay = sh1106_clear_display,
    .drv_oled_pixel_draw = sh1106_drawPixel,
    .drv_oled_rect_draw = sh1106_rect_draw,
    .drv_oled_display = sh1106_display,
    .drv_oled_rotation_set = sh1106_rotation_set,
    .drv_oled_invert = sh1106_display_invert,
    .drv_oled_showCompany = sh1106_showCompany,
    .drv_oled_setChar = sh1106_setChar,
    .drv_oled_drawBitMap = sh1106_drawBitMap,
    .p_drv_oled = &sh1106_cb,
};


/******************************** End of file *********************************/

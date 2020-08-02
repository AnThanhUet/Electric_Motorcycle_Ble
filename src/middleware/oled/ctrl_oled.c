/**
 * @file ctrl_oled.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "ctrl_oled.h"
#include "drv_oled.h"
#include "timer.h"
#define NRF_LOG_MODULE_NAME ctrl_oled
#include "nrf_log.h"
#include "status.h"
#include "nrf_log_ctrl.h"
#include "bsp_pega.h"
#include "nrf_log_default_backends.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
// APP_TIMER_DEF(id_oled);
static const drv_oled_t *main_oled = &drv_oled_sh1106; // define driver sh1106
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

uint32_t ctrl_oled_init()
{
    ASSERT(main_oled != NULL);

    uint32_t err_code;
    err_code = main_oled->drv_oled_init();
    RETURN_IF_ERROR(err_code);
    NRF_LOG_FLUSH();
    NRF_LOG_INFO("oled init");
    return NRF_SUCCESS;
}

void ctrl_oled_show()
{
    //while(1)
    {
        main_oled->drv_oled_display();
    }
}

void ctrl_oled_invert(bool invert)
{
    main_oled->drv_oled_invert(invert);
}

void ctrl_oled_clearDisplay()
{
    main_oled->drv_oled_clearDisplay();
}

void ctrl_oledCompany()
{
    main_oled->drv_oled_showCompany();
}

void ctrl_oled_setChar(uint16_t x_cursor, uint16_t y_cursor, char s)
{
	uint32_t err_code;

    err_code = main_oled->drv_oled_setChar(x_cursor,y_cursor,s);
	APP_ERROR_CHECK_SAVY(err_code);
}

void ctrl_oled_setString(uint16_t x_cursor, uint16_t y_cursor, char *s, uint16_t len)
{
    uint32_t err_code;

    for (uint16_t i = 0; i < len ; i++)
    {
        err_code = main_oled->drv_oled_setChar(x_cursor + i*5 + i,y_cursor,s[i]);
        APP_ERROR_CHECK_SAVY(err_code);
    }
}

/******************************** End of file *********************************/

/**
 * @file oled.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "ctrl_oled.h"
#include "timer.h"
#include "oled.h"
#include "oled_lib.h"
#define NRF_LOG_MODULE_NAME oled
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off
// timer
APP_TIMER_DEF(id_oled);
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
static uint16_t x_cursor = 0; // x cursor current
static uint16_t y_cursor = 0; // y cursor current
static uint8_t tab = 1;
static uint8_t dir_cur;
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
static void oled_set_char(char s)
{
    ctrl_oled_setChar(x_cursor,y_cursor,s);
}

static void oled_set_cursor(uint16_t x, uint16_t y)
{
    x_cursor = x;
    y_cursor = y;
}

static void oled_string(char *str, uint16_t len)
{
    ctrl_oled_setString(x_cursor,y_cursor,str,len);
}


void oled_init()
{
    uint32_t err_code;
    err_code = ctrl_oled_init();
    APP_ERROR_CHECK_SAVY(err_code);
}

void oled_show()
{
    ctrl_oled_show();
}

void oled_invert(bool invert)
{
    ctrl_oled_invert(invert);
}

static void oled_show_distance(uint16_t distance, uint8_t unit)
{
    char *str = (char*)malloc(sizeof(char*)*OLED_DISTANCE_MAX_UNIT);
    
    if (unit == OLED_UNIT_METER)
    {   
        oled_set_cursor(OLED_DISTANCE_X + 35, OLED_DISTANCE_Y);
        oled_string("  ",sizeof("  "));
        oled_set_cursor(OLED_DISTANCE_X + 35, OLED_DISTANCE_Y);
        oled_string("m",sizeof("m"));
    }
    else
    {
        oled_set_cursor(OLED_DISTANCE_X + 35, OLED_DISTANCE_Y);
        oled_string(" ",sizeof(" "));
        oled_set_cursor(OLED_DISTANCE_X + 35, OLED_DISTANCE_Y);
        oled_string("km",sizeof("km"));
    }

    sprintf(str,"%5d",distance);

    oled_set_cursor(OLED_DISTANCE_X,OLED_DISTANCE_Y);
    oled_string(str,sizeof(str) + 1);
    
    free(str);
}

static void oled_show_distance_str(char *distance, uint8_t len_dis)
{
    oled_set_cursor(OLED_DISTANCE_X,OLED_DISTANCE_Y);
    oled_string(distance,len_dis);
    for (uint8_t i = 0; i < len_dis;i++)
    {
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("distance = %x",distance[i]);
    }
}

void oled_show_startToDestination(char *start, uint16_t len_s, char *dist, uint16_t len_d)
{
    oled_set_cursor(OLED_START_X,OLED_START_Y);
    oled_string(start,len_s);
    oled_set_cursor(OLED_DEST_X,OLED_DEST_Y);
    oled_string(dist,len_d);
}

static void oled_show_timer(uint16_t time, uint8_t unit)
{
    char *str = (char*)malloc(sizeof(char*)*OLED_TIME_MAX_UNIT);

    if (unit == OLED_UNIT_MIN)
    {
        oled_set_cursor(OLED_TIME_UNIT,OLED_TIME_Y);
        oled_string("min",sizeof("min"));
    }
    else
    {
        oled_set_cursor(OLED_TIME_UNIT,OLED_TIME_Y);
        oled_string("hour",sizeof("hour"));
    }
    
    sprintf(str,"%2d",time);
    oled_set_cursor(OLED_TIME_X,OLED_TIME_Y);
    oled_string(str,sizeof(*str) + 1);
}

static void oled_show_speed(uint16_t speed, uint8_t unit)
{
    char *str = (char*)malloc(sizeof(char*)*OLED_SPEED_MAX_UNIT);

    if (unit == OLED_UNIT_KM_H)
    {
        oled_set_cursor(OLED_SPEED_UNIT_X,OLED_SPEED_Y);
        oled_string("km/h",sizeof("km/h"));
    }
    else
    {
        oled_set_cursor(OLED_SPEED_UNIT_X,OLED_SPEED_Y);
        oled_string("m/s",sizeof("m/s"));
    }
    
    sprintf(str,"%3d",speed);
    oled_set_cursor(OLED_SPEED_X,OLED_SPEED_Y);
    oled_string(str,OLED_SPEED_MAX_UNIT);
    free(str);
}

static void oled_navigate(uint8_t dir, uint16_t blink)
{
    static uint16_t blink_pre = 0;
    if (dir == OLED_GO_STRAIGTH)
    {
        oled_set_cursor(61,20);
        oled_set_char(' ');
        oled_set_cursor(79,20);
        oled_set_char(' ');
        if (blink_pre != 0)
        {
            oled_set_cursor(70,blink_pre);
            oled_set_char(' ');
        }
        oled_set_cursor(70,blink);
        oled_set_char(OLED_DIR_UP);
    }
    else if (dir == OLED_TURN_LEFT)
    {
        oled_set_cursor(79,20);
        oled_set_char(' ');
        if (blink <= 20)
        {
            if (blink_pre != 0)
            {
                oled_set_cursor(70 - (20 - blink_pre) + 1,20);
                oled_set_char(' ');
            }
            oled_set_cursor(70 - (20 - blink),20);
            oled_set_char(OLED_DIR_LEFT);
        }
        else
        {
            oled_set_cursor(70,blink);
            oled_set_char(OLED_DIR_UP);
        }
    }
    else if (dir == OLED_TURN_RIGHT)
    {
        oled_set_cursor(61,20);
        oled_set_char(' ');
        if (blink <= 20)
        {
            if (blink_pre != 0)
            {
                oled_set_cursor(70 + (20 - blink_pre) - 1,20);
                oled_set_char(' ');
            }
            oled_set_cursor(70 + (20 - blink),20);
            oled_set_char(OLED_DIR_RIGHT);
        }
        else
        {
            oled_set_cursor(70,blink);
            oled_set_char(OLED_DIR_UP);
        }
    }
    blink_pre = blink;
}

void oled_set_dir_tab1(uint8_t dir)
{
    dir_cur = dir;
}

void oled_timer_handler(void *p_context)
{
    static uint8_t blink_x = 40;
    // static uint16_t time = 20;
    if (tab == 1)
    {
        oled_navigate(dir_cur,blink_x);
        // oled_show_timer(time,OLED_UNIT_MIN);
    }
    
    blink_x --;
    if (blink_x <= 10)
    {
        blink_x = 40;
    }
}

void oled_tab1_update(char *distance, uint8_t len_dis, uint16_t time, uint8_t direct)
{
    tab = 1;
    oled_show_distance_str(distance,len_dis);
    oled_show_timer(time,OLED_UNIT_MIN);
    oled_set_dir_tab1(direct);
}

void oled_tab1()
{
    uint32_t err_code;
    static uint8_t init = 1;
    tab = 1;
    // oled_show_startToDestination("Chua Boc street",sizeof("Chua Boc street"),
    //                             "Back Khoa street",sizeof("Back Khoa street"));
    oled_show_distance(0, OLED_UNIT_METER);
    oled_show_timer(0, OLED_UNIT_MIN);
    oled_show_speed(0, OLED_UNIT_KM_H);
    oled_set_dir_tab1(OLED_GO_STRAIGTH);
    if (init)
    {
        init = 0;
        timer_create(id_oled,APP_TIMER_MODE_REPEATED,oled_timer_handler);
        err_code = timer_start(id_oled, OLED_TIMEOUT);
        APP_ERROR_CHECK_SAVY(err_code);
    }
}

void oled_tab2()
{
    
}

void oled_close_allTab()
{
    oled_clearDiplay();
}

void oled_clearDiplay()
{
    ctrl_oled_clearDisplay();
}

void oled_showCompany()
{
    tab = 0;
    ctrl_oledCompany();
}

/******************************** End of file *********************************/

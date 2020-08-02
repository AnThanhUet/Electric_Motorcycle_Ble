/**
 * @file timer.c
 * @author TienTD (ductien.savy@gmail.com)
 * @brief 
 * @version 0.1
 * @date 24-07-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "timer.h"
#include "status.h"
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

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

/**
 * @brief : function timer
 * 
 * @param timer_id 
 * @param mode 
 * @param timeout 
 * @return uint32_t 
 */
uint32_t timer_create(app_timer_id_t timer_id,
                    app_timer_mode_t mode,
                    app_timer_timeout_handler_t timeout)
{
    uint32_t ret;
    ret = app_timer_create(&timer_id, mode, timeout);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

/**
 * @brief : function 
 * 
 * @param timer_id 
 * @param time_start 
 * @return uint32_t 
 */
uint32_t timer_start(app_timer_id_t timer_id, uint32_t time_start)
{
    uint32_t ret;
    ret = app_timer_start(timer_id, APP_TIMER_TICKS(time_start),NULL);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

/**
 * @brief : 
 * 
 * @param timer_id 
 * @return uint32_t 
 */
uint32_t timer_stop(app_timer_id_t timer_id)
{
    uint32_t ret;
    ret = app_timer_stop(timer_id);
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

/**
 * @brief :
 * 
 * @return uint32_t 
 */
uint32_t timer_counter_get()
{
    uint32_t ret;
    ret = app_timer_cnt_get();
    RETURN_IF_ERROR(ret);
    return NRF_SUCCESS;
}

/**
 * @brief :
 * 
 * @param status 
 */
void timer_control(uint32_t status)
{
    if (status == 0)
    {
        app_timer_pause();
    }
    else
    {
        app_timer_resume();
    }
}

/******************************** End of file *********************************/

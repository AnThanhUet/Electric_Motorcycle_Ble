/**
 * @file timer.h
 * @author TienTD (ductien.savy@gmail.com)
 * @brief 
 * @version 0.1
 * @date 24-07-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "app_timer.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t timer_create(app_timer_id_t timer_id, app_timer_mode_t mode, app_timer_timeout_handler_t timeout);
uint32_t timer_start(app_timer_id_t timer_id, uint32_t time_start);
uint32_t timer_stop(app_timer_id_t timer_id);
uint32_t timer_start_buzzer(app_timer_id_t timer_id, uint32_t time_start,void*data);
uint32_t timer_start_indicator(app_timer_id_t timer_id, uint32_t time_start,void*data);
uint32_t timer_counter_get(void);
void timer_control(uint32_t status);

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H__ */

/******************************** End of file *********************************/

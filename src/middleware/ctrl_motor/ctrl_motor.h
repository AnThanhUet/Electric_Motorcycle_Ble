/**
 * @file ctrl_motor.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

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

// clang-format on

/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
typedef struct 
{

    uint8_t times;
    uint32_t period;
    uint8_t enable;
}ctrl_motor_cfg_param_t;

typedef struct 
{
    ctrl_motor_cfg_param_t buzzer;
    ctrl_motor_cfg_param_t indicator;
}ctrl_motor_cfg_t;
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t ctrl_motor_init();

uint32_t ctrl_motor_respFind();

uint32_t ctrl_motor_respAlarm();

uint32_t ctrl_motor_respWarning();


#ifdef __cplusplus
}
#endif

#endif /* __CTRL_MOTOR_H__ */

/******************************** End of file *********************************/

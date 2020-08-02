/**
 * @file ctrl_buzzer.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CTRL_BUZZER_H__
#define __CTRL_BUZZER_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include <stdint.h>
#include "ctrl_motor.h"
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
uint32_t ctrl_buzzer_init();

uint32_t ctrl_buzzer_open(ctrl_motor_cfg_param_t buzzer);

uint32_t ctrl_buzzer_close();


#ifdef __cplusplus
}
#endif

#endif /* __CTRL_BUZZER_H__ */

/******************************** End of file *********************************/

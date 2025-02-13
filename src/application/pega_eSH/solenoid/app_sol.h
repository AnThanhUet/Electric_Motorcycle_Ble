/**
 * @file app_sol.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __APP_SOL_H__
#define __APP_SOL_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/

/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/
enum
{
    APP_SOL_OFF,
    APP_SOL_ON
};
/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
void app_sol_init();

void app_sol_open();

void app_sol_close();

#ifdef __cplusplus
}
#endif

#endif /* __APP_SOL_H__ */

/******************************** End of file *********************************/

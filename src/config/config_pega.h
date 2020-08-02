/**
 * @file config_pega.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CONFIG_PEGA_H__
#define __CONFIG_PEGA_H__

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
#define TEST    1// NOTEST or TEST
#define OLED    1
/* I. PEGA ESH    status */
#define PEGA_ESH    0
/* 1. app sen */
#define APP_SOL     0
/* 2. app sim */
#define APP_SIM     0
/* 3. bond sercurity*/
#define APP_BOND_SECURITY 0
/* 4. custom key sercu*/
#define APP_SECURITY    0
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __CONFIG_PEGA_H__ */

/******************************** End of file *********************************/

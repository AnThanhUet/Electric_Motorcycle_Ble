/**
 * @file status.h
 * @author LamPT (phanthelam.savy@gamil.com)
 * @brief 
 * @version 0.1
 * @date 02-08-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef __STATUS_H__
#define __STATUS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "nrf_log.h"
#include "stdint.h"
#include "string.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_log.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off
#define NRF_LOG_DOUBLE(val) (int32_t)(val),                                       \
                           (int32_t)((((val) > 0) ? (val) - (int32_t)(val)       \
                                                : (int32_t)(val) - (val))*100)

#define RETURN_IF_ERROR(err_code)                                                    \
if ((err_code) != NRF_SUCCESS)                                                       \
{                                                                                    \
    NRF_LOG_WARNING("WARNING code returned in file: %s, line: %d, code %d ",             \
    nrf_log_push(__FILE__), __LINE__, err_code);                                     \
    return (err_code);                                                               \
}
#define DEBUG 1
#if DEBUG
#define DEBUG_SAVY NRF_LOG_INFO(" line : %d func : %s",__LINE__,__func__)
#endif

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

#endif /* __STATUS_DRIVER_H__ */

/******************************** End of file *********************************/


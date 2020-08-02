/**
 * @file drv_gpiote_irq.h
 * @author N.T.Tung (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-06
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __DRV_GPIOTE_IRQ_H__
#define __DRV_GPIOTE_IRQ_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "stdint.h"
#include "nrf_drv_gpiote.h"
/*******************************************************************************
**                                DEFINES
*******************************************************************************/
// clang-format off

// clang-format on
#define drv_gte_irq_handler_t nrf_drv_gpiote_evt_handler_t
#define drv_gte_irq_pint_t nrf_drv_gpiote_pin_t
#define drv_gte_irq_polarity_t nrf_gpiote_polarity_t
#define drv_gte_irq_in_config_t nrf_drv_gpiote_in_config_t

#define DRV_GTE_TOGGLE NRF_GPIOTE_POLARITY_TOGGLE
#define DRV_GTE_PUSH    1
#define DRV_GTE_RELEASE 0
/*******************************************************************************
**                     EXTERNAL VARIABLE DECLARATIONS
*******************************************************************************/

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
uint32_t drv_gpiote_irq_init(void);

uint32_t drv_gpiote_irq_enable(uint32_t pin, drv_gte_irq_handler_t handler);

void drv_gpiote_irq_disable(uint32_t pin);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIOTE_SAVY_H__ */

/******************************** End of file *********************************/

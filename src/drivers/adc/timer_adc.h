/**
 * @file timer_adc.h
 * @author TienTD (ductien.savy@gmail.com)
 * @brief 
 * @version 0.1
 * @date 02-08-2019
 * 
 * @copyright Copyright (c) 2019 Fangia Savy
 * 
 */
#ifndef __TIMER_ADC_H__
#define __TIMER_ADC_H__

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

/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/
void timer_adc_event_init(void);
void timer_adc_ppi_event_enable(void);
void timer_adc_start(void);
void timer_adc_stop(void);
#ifdef __cplusplus
}
#endif

#endif /* __TIMER_ADC_H__ */

/******************************** End of file *********************************/

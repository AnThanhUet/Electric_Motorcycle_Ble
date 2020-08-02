/**
 * @file drv_adc.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "drv_adc.h"
#include "nrf_delay.h"
#define NRF_LOG_MODULE_NAME drv_adc
#include "status.h"
#include "bsp_pega.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
#define MAX_SAMPLES 1
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
// use initialized drv adc
static nrf_saadc_value_t     m_buffer_pool[2][MAX_SAMPLES];

// declare timer adc
static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(3);

static nrf_ppi_channel_t     m_ppi_channel;

// value adc send to layer mid and app
static uint32_t value_adc;

static nrf_saadc_channel_config_t channel_config[MAX_CHANNEL_CONFIG_ADC];
static uint8_t m_adc_count = 0;
static uint8_t adc_instance_cur = 0;
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

void drv_adc_timer(nrf_timer_event_t event_type, void * p_context)
{
    // do nothing
}

/**
 * @brief : function initialized timer adc samp
 * 
 * @return uint32_t 
 */
uint32_t drv_adc_samp_event_init()
{
    ret_code_t err_code;
    
    err_code = nrf_drv_ppi_init();
    RETURN_IF_ERROR(err_code);
    
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, drv_adc_timer);
    RETURN_IF_ERROR(err_code);
    
    /* setup m_timer for compare event every 400ms */
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 400);
    nrf_drv_timer_extended_compare(&m_timer,
                                   NRF_TIMER_CC_CHANNEL0,
                                   ticks,
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                   false);
    nrf_drv_timer_enable(&m_timer);

    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                                                                NRF_TIMER_CC_CHANNEL0);
    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    RETURN_IF_ERROR(err_code);

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    RETURN_IF_ERROR(err_code);
    return NRF_SUCCESS;
}

/**
 * @brief : function enable sample
 * 
 * @return uint32_t 
 */
uint32_t drv_adc_samp_enable()
{
    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);

    RETURN_IF_ERROR(err_code);
    return err_code;
}

/**
 * @brief : 
 * 
 * @param p_event 
 */
void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    // uint32_t adc;
    // static uint8_t 
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
        
        ret_code_t err_code;
        err_code = nrf_drv_saadc_channel_uninit(adc_instance_cur);
		APP_ERROR_CHECK_SAVY(err_code);
        adc_instance_cur ++;
        if (adc_instance_cur == m_adc_count)
        {
            adc_instance_cur = 0;
        }
		err_code = nrf_drv_saadc_channel_init(adc_instance_cur, &channel_config[adc_instance_cur]);
		APP_ERROR_CHECK_SAVY(err_code);

        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, MAX_SAMPLES);
        value_adc = p_event->data.done.p_buffer[0];
        APP_ERROR_CHECK_SAVY(err_code);
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("adc %d value_adc = %d",adc_instance_cur,value_adc);
        nrf_delay_ms(10); //  wait get adc 
    }
}

/**
 * @brief : function return value adc
 * 
 * @return uint32_t 
 */
uint32_t drv_adc_get_value()
{
    return value_adc;
}

/**
 * @brief : function 
 * 
 * @param adc_pins 
 * @param adc_count 
 * @return uint32_t 
 */
uint32_t drv_adc_init(uint8_t *adc_pins,
                        uint8_t     adc_count)
{
    uint32_t err_code;
    if (adc_count > MAX_CHANNEL_CONFIG_ADC)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (adc_pins == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    
    
    adc_instance_cur = 0;
    m_adc_count = adc_count;
    while(adc_count --)
    {
        channel_config[adc_count].resistor_p = NRF_SAADC_RESISTOR_DISABLED;
        channel_config[adc_count].resistor_n = NRF_SAADC_RESISTOR_DISABLED;
        channel_config[adc_count].reference  = NRF_SAADC_REFERENCE_INTERNAL;
        channel_config[adc_count].acq_time   = NRF_SAADC_ACQTIME_3US;
        channel_config[adc_count].mode       = NRF_SAADC_MODE_SINGLE_ENDED;
        channel_config[adc_count].burst      = NRF_SAADC_BURST_DISABLED;
        channel_config[adc_count].pin_p      = (nrf_saadc_input_t)(adc_pins[adc_count]);
        channel_config[adc_count].pin_n      = NRF_SAADC_INPUT_DISABLED;
        channel_config[adc_count].gain       = NRF_SAADC_GAIN1_4;  // set default
    }
    

    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    RETURN_IF_ERROR(err_code);

    err_code = nrf_drv_saadc_channel_init(0, &channel_config[0]);
    RETURN_IF_ERROR(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1],MAX_SAMPLES);
    APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}



/******************************** End of file *********************************/

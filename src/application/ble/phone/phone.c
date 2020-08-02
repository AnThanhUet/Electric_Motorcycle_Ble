/**
 * @file phone.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config_pega.h"
#if phone
#include "phone.h"
#include "service_pega.h"
#define NRF_LOG_MODULE_NAME phone
#include "status.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
#define DEBUG_PHONE 0
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
nodePhone_p head;
nodePhone_p current;
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

static bool phone_isEmpty()
{
    if (NULL == head)
    {
        NRF_LOG_FLUSH();
        NRF_LOG_INFO(" empty !!");
        return true;
    }
    return false; 
}

void phone_add_id(char *name, uint16_t id_key, phone_handler_t handler)
{   
    nodePhone_p node = (nodePhone_p)malloc(sizeof(nodePhone_p));

    node->name = name;
    node->id_key = id_key;
    node->handler = handler;
    node->next = head;

    head = node;
}

static uint32_t phone_find_id(uint16_t id_key, uint8_t *data, uint16_t len)
{
    if (phone_isEmpty())
    {
        return PHONE_ID_EMPTY;
    }

    current = head;

    while(current)
    {
        if (current->id_key == id_key)
        {
            current->handler(data, len);
            return PHONE_ID_READY;
        }
    }

    return PHONE_ID_NOT_FOUND;
}

uint32_t phone_show_id()
{
    if (phone_isEmpty())
    {
        return PHONE_ID_EMPTY;
    }

    current = head;

    while(current)
    {
        NRF_LOG_FLUSH();
        NRF_LOG_INFO("%s: %s %x",__func__, current->name, current->id_key);
        current = current->next;
    }

    return PHONE_SUCCESS;
}

/**
 * @brief : 
 * 
 * @param p_sPega 
 */

void sPega_data_handler(sPega_evt_t *p_evt)
{
    uint16_t id_app;
    uint8_t *data = (uint8_t *)p_evt->params.rx_data.p_data;
    uint32_t err_code;
    switch (p_evt->type)
    {
    case PEGA_EVT_RX_DATA:
        // data received from phone
        #if DEBUG_PHONE
        for (uint8_t i = 0; i < p_evt->params.rx_data.len;i++)
        {
            NRF_LOG_FLUSH();
            NRF_LOG_INFO(" data[%d] = %x",i,p_evt->params.rx_data.p_data[i]);     
        }
        #endif

        id_app = (uint16_t)((p_evt->params.rx_data.p_data[0] << 8) | (p_evt->params.rx_data.p_data[1]));

        if (p_evt->params.rx_data.len > 2)
        {
            err_code = phone_find_id(id_app,data + 2, p_evt->params.rx_data.len - 2);
            if (PHONE_ID_READY != err_code)
            {
                NRF_LOG_FLUSH();
                NRF_LOG_INFO("warning %d \n",err_code);
            }
        }
        else
        {
            NRF_LOG_FLUSH();
            NRF_LOG_INFO(" ERROR len data !!");
        }

        break;
    case PEGA_EVT_COMM_STARTED:
        break;
    case PEGA_EVT_COMM_STOPPED:
        break;
    case PEGA_EVT_TX_RDY:
        break;
    default:
        break;
    }
}
uint32_t phone_sendData(uint8_t *data, uint16_t len)
{
    uint32_t err_code;
    if (len < PEGA_MAX_DATA_LEN)
    {
        err_code = sPega_sendData(&main_sPega, data, len);
        RETURN_IF_ERROR(err_code);
    }
    else
    {
        err_code = sPega_sendData(&main_sPega, data, PEGA_MAX_DATA_LEN);
        RETURN_IF_ERROR(err_code);
        err_code = sPega_sendData(&main_sPega, 
                        data + PEGA_MAX_DATA_LEN ,len - PEGA_MAX_DATA_LEN);
        RETURN_IF_ERROR(err_code);
    }
    return NRF_SUCCESS;
    
}
#endif
/******************************** End of file *********************************/

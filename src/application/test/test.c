/**
 * @file test.c
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */
/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "config_pega.h"
#if TEST
#include "gatt.h"
#include "drv_adc.h"
#include "drv_uart.h"
#include "service_pega.h"
#include "ctrl_solenoid.h"
#include "ctrl_readAlarm.h"
#include "ctrl_motor.h"
#include "test.h"
#include "oled.h"
#include "SEGGER_RTT.h"
#include "ctrl_sim.h"
#include "display_app.h"
#include "Display_controll.h"
#define NRF_LOG_MODULE_NAME test
#include "status.h"
NRF_LOG_MODULE_REGISTER();
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
// APP_TIMER_DEF(main_id);
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
// static uint8_t test[] = {NRF_SAADC_INPUT_AIN6, NRF_SAADC_INPUT_AIN0};
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/

/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
double convert_byteToFloat(uint8_t *arr_byte)
{
    int temp;
    float result = 0;
    temp = ((arr_byte[0] << 24) | (arr_byte[1] << 16) | (arr_byte[2] << 8) | (arr_byte[3]));
    result = *((float *)&temp);
    return result;
}

void sPega_data_handler(sPega_evt_t *p_evt)
{

    switch (p_evt->type)
    {
    case PEGA_EVT_RX_DATA:
        if (p_evt->params.rx_data.len == 5)
        {
            char *distance = (char *)malloc(sizeof(char *) * 4);
            char *dataSend = (char *)malloc(sizeof(char *) * 5);
            sprintf(distance, "%ld.%02ld", NRF_LOG_DOUBLE(convert_byteToFloat((uint8_t *)p_evt->params.rx_data.p_data)));
            for (uint8_t index = 0; index < 4; index++)
            {
                dataSend[index] = distance[index];
                NRF_LOG_INFO(" distanceDataSend = %c", *(dataSend + index));
                NRF_LOG_FLUSH();
            }
            dataSend[4] = p_evt->params.rx_data.p_data[4];        
            NRF_LOG_INFO(" DIRECTION = %d", dataSend[4]);
            NRF_LOG_FLUSH();
            display_app_sendData(dataSend, 5);
            // if (p_evt->params.rx_data.p_data[4] == 0x01)  // left
            // {
            //      NRF_LOG_FLUSH();
            //     NRF_LOG_INFO(" TurnLeft------------------\n")
            //     NRF_LOG_INFO(" data_distanceLeft = %d",*distance);
            //     NRF_LOG_INFO(" data_distanceLeft = %d",*(distance+1));
            //     NRF_LOG_INFO(" data_distanceLeft = %d",*(distance+2));
            //     NRF_LOG_INFO(" data_distanceLeft = %d",*(distance+3));
            //     NRF_LOG_FLUSH();
            //     display_app_sendData(distance,4);

            // }
            // else if (p_evt->params.rx_data.p_data[4] == 0x02) // right
            // {
            //     //oled_tab1_update(distance,5,0,OLED_TURN_RIGHT);

            //     NRF_LOG_FLUSH();
            //     NRF_LOG_INFO(" TurnRight------------------\n")
            //     NRF_LOG_INFO(" data_distanceRight = %d",*distance);
            //     NRF_LOG_INFO(" data_distanceRight = %d",*(distance+1));
            //     NRF_LOG_INFO(" data_distanceRight = %d",*(distance+2));
            //     NRF_LOG_INFO(" data_distanceRight = %d",*(distance+3));
            //     NRF_LOG_FLUSH();
            //      display_app_sendData(distance,4);
            // }
            // else if (p_evt->params.rx_data.p_data[4] == 0x00) // straigth
            // {
            //     //soled_tab1_update(distance,5,0,OLED_GO_STRAIGTH); //
            //     NRF_LOG_FLUSH();
            //     NRF_LOG_INFO("straight ------------------\n");
            //     NRF_LOG_INFO(" data_distanceStraigth = %d",*distance);
            //     NRF_LOG_INFO(" data_distanceStraigth = %d",*(distance+1));
            //     NRF_LOG_INFO(" data_distanceStraigth = %d",*(distance+2));
            //     NRF_LOG_INFO(" data_distanceStraigth = %d",*(distance+3));
            //     NRF_LOG_FLUSH();
            //     display_app_sendData(distance,4);

            // }
            free(dataSend);
            free(distance);
        }
        /*  
        for (uint8_t i = 0; i < p_evt->params.rx_data.len;i++)
        {
            NRF_LOG_FLUSH();
            NRF_LOG_INFO(" data[%d] = %x",i,p_evt->params.rx_data.p_data[i]);     
        }
        // tet
        if (p_evt->params.rx_data.p_data[0] == 0x01)
        {
            char str[] = "CLOSE SOCKET";
            drv_uart_write((uint8_t*)str,sizeof(str));
            // ctrl_solenoid_off();
        }
        else if (p_evt->params.rx_data.p_data[0] == 0x02)
        {
            char str2[] = "CONNECT AGAIN";
            drv_uart_write((uint8_t*)str2,sizeof(str2));
            // ctrl_solenoid_on();
        }
        else if (p_evt->params.rx_data.p_data[0] == 0x03)
        {
            char str3[] = "GPRS DIS";
            drv_uart_write((uint8_t*)str3,sizeof(str3));
        }
        else if (p_evt->params.rx_data.p_data[0] == 0x04)
        {
            char str4[] = "SOCKET SEND";
            drv_uart_write((uint8_t*)str4, sizeof(str4));
        }
        else if (p_evt->params.rx_data.p_data[0] == 0x05)
        {
            char send[30] = {0};
            sprintf(send,"BATTERY : %ld.%02ldV",
                            NRF_LOG_DOUBLE(12.22));
            NRF_LOG_FLUSH();
            NRF_LOG_INFO(" %d \n", sizeof(send));
            drv_uart_write((uint8_t*)send, 30);
        }
     */

        // drv_uart_write((uint8_t*)p_evt->params.rx_data.p_data,p_evt->params.rx_data.len);

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

uint8_t str_cmp(char *str1, char *str2, uint8_t len)
{
    // SEGGER_RTT_printf(0," \n ");
    for (uint8_t i = 0; i < len; i++)
    {
        // SEGGER_RTT_printf(0," %x ",str2[i]);
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    // SEGGER_RTT_printf(0," \n ");
    return 1;
}

void uart_handler(drv_uart_evt_t *p_event)
{
    static uint8_t data_array[100];
    static uint8_t index = 0;
    switch (p_event->evt_type)
    {
    case APP_UART_DATA_READY:
        app_uart_get(&data_array[index]);              // received data
        SEGGER_RTT_printf(0, "%c", data_array[index]); // printf quickly

        if (data_array[index++] == '\n')
        {
            if (str_cmp((char *)data_array, "NRF:", 4) != 0)
            {
                for (uint8_t i = 0; i < index; i++)
                {
                    SEGGER_RTT_printf(0, "%c", data_array[i]);
                }
            }
            index = 0;
        }

        break;
    case APP_UART_COMMUNICATION_ERROR:
        //FIXME: no plugin rx tx
        //APP_ERROR_CHECK_SAVY(p_event->data.error_communication,__LINE__,__func__);
        break;
    case APP_UART_FIFO_ERROR:
        //APP_ERROR_CHECK_SAVY(p_event->data.error_code,__LINE__,__func__);
        break;
    default:
        break;
    }
}

// void alarm_handler(uint8_t pin_no, uint8_t button_action)
// {
//     switch(pin_no)
//     {
//         case PIN_ECU_RESP_LOCKED:
//             if (button_action == 1)
//             {
//                 NRF_LOG_FLUSH();
//                 NRF_LOG_INFO(" E - ON ");
//             }
//             else
//             {
//                 NRF_LOG_FLUSH();
//                 NRF_LOG_INFO(" E - OFF ");
//             }
//             break;
//         case PIN_CTRL_LOCK_WEEL:
//             if (button_action == 1)
//             {
//                 NRF_LOG_FLUSH();
//                 NRF_LOG_INFO(" W - ON ");
//             }
//             else
//             {
//                 NRF_LOG_FLUSH();
//                 NRF_LOG_INFO(" W - OFF ");
//             }
//             break;
//         case PIN_READ_ALARM:
//             if (button_action == 1)
//             {
//                 NRF_LOG_FLUSH();
//                 NRF_LOG_INFO(" A - ON ");
//             }
//             else
//             {
//                 NRF_LOG_FLUSH();
//                 NRF_LOG_INFO(" A - OFF ");
//             }
//             break;
//         default:
//             break;
//     }
// }

// void solenoid_handler(ctrl_solenoid_evt_t evt)
// {
//     switch(evt)
//     {
//         case CTRL_SEN_OFF:
//             NRF_LOG_FLUSH();
//             NRF_LOG_INFO("OFF");
//             break;
//         case CTRL_SEN_ON:
//             NRF_LOG_FLUSH();
//             NRF_LOG_INFO("ON");
//             break;
//         default:
//             break;
//     }
// }

void test()
{
    // /* TEST */
    //oled_init();
    //oled_tab1();

    //  test adc
    // drv_adc_init(test,2);
    // saadc_sampling_event_init();
    // saadc_sampling_event_enable();

    // test uart
    // ctrl_solenoid_init(solenoid_handler);
    // ctrl_readAlarm_init(alarm_handler);
    // //

    Display_controll_open(115200, uart_handler);
    //char testData[1] = {0x04};
    //display_app_sendData(testData, 1);
    // ctrl_motor_init();
    // ctrl_motor_respFind();

    /* TEST */
}
#endif
/******************************** End of file *********************************/

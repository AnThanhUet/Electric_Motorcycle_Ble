/**
 * @file phone.h
 * @author N.T.TUNG (nguyenthanhtung8196@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __PHONE_H__
#define __PHONE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**                               INCLUDES
*******************************************************************************/
#include "service_pega.h"
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
    PHONE_SUCCESS,
    PHONE_ID_EMPTY,
    PHONE_ID_READY,
    PHONE_ID_NOT_FOUND
};


typedef void (*phone_handler_t)(uint8_t *data, uint16_t len);

typedef struct nodePhone_s
{
    char                *name;
    uint16_t            id_key;
    phone_handler_t     handler;
    struct nodePhone_s  *next;
}nodePhone_t, *nodePhone_p;


/*******************************************************************************
**                     EXTERNAL FUNCTION DECLARATIONS
*******************************************************************************/

void phone_add_id(char *name, uint16_t id_key, phone_handler_t handler);

uint32_t phone_sendData(uint8_t *data, uint16_t len);

uint32_t phone_show_id();

#ifdef __cplusplus
}
#endif

#endif /* __PHONE_H__ */

/******************************** End of file *********************************/

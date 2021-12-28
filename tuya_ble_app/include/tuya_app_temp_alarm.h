/**
 * @file tuya_app_temp_alarm.h
 * @author lifan
 * @brief temperature alarm application header file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#ifndef __TUYA_APP_TEMP_ALARM_H__
#define __TUYA_APP_TEMP_ALARM_H__

#include "tuya_ble_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
************************micro define************************
***********************************************************/

/***********************************************************
***********************typedef define***********************
***********************************************************/

/***********************************************************
***********************variable define**********************
***********************************************************/

/***********************************************************
***********************function define**********************
***********************************************************/
/**
 * @brief temp alarm init
 * @param[in] none
 * @return none
 */
void tuya_app_temp_alarm_init(void);

/**
 * @brief main loop of temperature alarm
 * @param[in] none
 * @return none
 */
void tuya_app_temp_alarm_loop(void);

/**
 * @brief dp data handler of temperature alarm
 * @param[in] dp_data：dp data array
 * @return none
 */
void tuya_app_temp_alarm_dp_data_handler(uint8_t *dp_data);

/**
 * @brief ble connect status change handler of temperature alarm
 * @param[in] status: ble connect status
 * @return none
 */
void tuya_app_temp_alarm_ble_connect_status_change_handler(tuya_ble_connect_status_t status);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TUYA_APP_TEMP_ALARM_H__ */

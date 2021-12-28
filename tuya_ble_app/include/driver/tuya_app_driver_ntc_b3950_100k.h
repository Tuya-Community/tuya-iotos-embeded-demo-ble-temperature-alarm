/**
 * @file tuya_app_driver_ntc_b3950_100k.h
 * @author lifan
 * @brief ntc(B3950/100K) driver header file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#ifndef __TUYA_APP_DRIVER_NTC_B3950_100K_H__
#define __TUYA_APP_DRIVER_NTC_B3950_100K_H__

#include "tuya_ble_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
************************micro define************************
***********************************************************/
#define TEMP_ARRAY_MIN_VALUE    0
#define TEMP_ARRAY_SIZE         120

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
 * @brief ntc adc init
 * @param[in] none
 * @return none
 */
void ntc_adc_init(void);

/**
 * @brief get current temperature
 * @param[in] none
 * @return ntc_temp：temperature value
 */
uint8_t get_cur_temp(void);

#ifdef __cplusplus
}
#endif

#endif /* __TUYA_APP_DRIVER_NTC_B3950_100K_H__ */

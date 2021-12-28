/**
 * @file tuya_app_driver_buzzer.h
 * @author lifan
 * @brief buzzer driver header file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#ifndef __TUYA_APP_DRIVER_BUZZER_H__
#define __TUYA_APP_DRIVER_BUZZER_H__

#include "tuya_ble_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
************************micro define************************
***********************************************************/
#define OFF 0
#define ON  (!OFF)

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
 * @brief buzzer driver init (PWM)
 * @param[in] none
 * @return none
 */
void buzzer_pwm_init(void);

/**
 * @brief set buzzer on or off
 * @param[in] b_on_off：buzzer on / buzzer off
 * @return none
 */
void set_buzzer(bool b_on_off);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TUYA_APP_DRIVER_BUZZER_H__ */

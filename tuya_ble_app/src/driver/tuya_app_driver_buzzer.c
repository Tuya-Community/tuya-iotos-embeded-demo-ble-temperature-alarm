/**
 * @file tuya_app_driver_buzzer.c
 * @author lifan
 * @brief buzzer driver source file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#include "tuya_app_driver_buzzer.h"
#include "app_config.h"
#include "gpio_8258.h"
#include "pwm.h"

/***********************************************************
************************micro define************************
***********************************************************/
/* Buzzer pin */
#define P_BUZZER            GPIO_PD4    /* P17 */
/* Buzzer pwm id */
#define PWM_ID_BUZZER       PWM2_ID     /* PWM2 */

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
void buzzer_pwm_init(void)
{
    pwm_set_clk(CLOCK_SYS_CLOCK_HZ, CLOCK_SYS_CLOCK_HZ);
	gpio_set_func(P_BUZZER, AS_PWM2_N);
    pwm_set_mode(PWM_ID_BUZZER, PWM_NORMAL_MODE);
    pwm_set_cycle_and_duty(PWM_ID_BUZZER, (uint16_t)(250 * CLOCK_SYS_CLOCK_1US), (uint16_t)(125 * CLOCK_SYS_CLOCK_1US));    /* 250us 4KHz 50% */
}

/**
 * @brief set buzzer on or off
 * @param[in] b_on_off：buzzer on / buzzer off
 * @return none
 */
void set_buzzer(bool b_on_off)
{
    static bool s_last_status = 0;
    if (s_last_status != b_on_off) {
        if (b_on_off == ON) {
        	pwm_start(PWM_ID_BUZZER);
        } else {
        	pwm_stop(PWM_ID_BUZZER);
            gpio_write(P_BUZZER, 0);
        }
        s_last_status = b_on_off;
    }
}

/**
 * @file tuya_app_temp_alarm.c
 * @author lifan
 * @brief temperature alarm application source file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#include "tuya_app_temp_alarm.h"
#include "tuya_app_driver_ntc_b3950_100k.h"
#include "tuya_app_driver_buzzer.h"
#include "tuya_ble_api.h"
#include "tuya_ble_log.h"
#include "tuya_ble_mutli_tsf_protocol.h"
#include "timer.h"

/***********************************************************
************************micro define************************
***********************************************************/
/* DP ID */
#define DP_ID_ALARM         101
#define DP_ID_TEMP_ALARM    102
/* DP TYPE */
#define DP_TYPE_ALARM       DT_BOOL
#define DP_TYPE_TEMP_ALARM  DT_VALUE

/* Temperature */
#define TEMP_ALARM_DEFAULT  35
/* Time */
#define TEMP_UPDATE_TIME_MS 2000

/***********************************************************
***********************typedef define***********************
***********************************************************/
/* DP data struct */
typedef struct {
    uint8_t id;
    dp_type type;
    uint8_t len;
    uint8_t value;
} DP_DATA_T;

/***********************************************************
***********************variable define**********************
***********************************************************/
/* DP data value */
uint8_t g_alarm_status = 0;
uint8_t g_temp_alarm = 0;

/***********************************************************
***********************function define**********************
***********************************************************/
/**
 * @brief get dp type
 * @param[in] dp_id：DP ID
 * @return type：DP type
 */
static uint8_t get_dp_type(uint8_t dp_id)
{
    dp_type type = 0;
    switch (dp_id) {
    case DP_ID_ALARM:
        type = DP_TYPE_ALARM;
        break;
    case DP_ID_TEMP_ALARM:
        type = DP_TYPE_TEMP_ALARM;
        break;
    default:
        break;
    }
    return type;
}

/**
 * @brief report one dp data
 * @param[in] dp_id：DP ID
 * @return none
 */
static void report_one_dp_data(uint8_t dp_id, uint8_t dp_value)
{
    DP_DATA_T dp_data_s;
    dp_data_s.id = dp_id;
    dp_data_s.type = get_dp_type(dp_id);
    dp_data_s.len = 0x01;
    dp_data_s.value = dp_value;
    tuya_ble_dp_data_report((uint8_t *)&dp_data_s, sizeof(DP_DATA_T));
}

/**
 * @brief set alarm temperature
 * @param[in] temp: alarm temperature
 * @return none
 */
static void set_alarm_temp(uint8_t temp)
{
    if ((temp >= TEMP_ARRAY_MIN_VALUE) &&
        (temp <= (TEMP_ARRAY_MIN_VALUE + TEMP_ARRAY_SIZE - 1))) {
        g_temp_alarm = temp;
        TUYA_APP_LOG_DEBUG("alarm temp: %d", g_temp_alarm);
    }
}

/**
 * @brief set alarm status
 * @param[in] status: alarm status
 * @return none
 */
static void set_alarm_status(uint8_t status)
{
    if (status != g_alarm_status) {
        g_alarm_status = status;
        report_one_dp_data(DP_ID_ALARM, g_alarm_status);
        TUYA_APP_LOG_DEBUG("alarm status: %d", g_alarm_status);
    }
}

/**
 * @brief update current temperature
 * @param[in] none
 * @return none
 */
static void update_cur_temp(void)
{
    static uint32_t s_get_temp_tm = 0;

	if (!clock_time_exceed(s_get_temp_tm, TEMP_UPDATE_TIME_MS*1000)) {
		return;
	}
	s_get_temp_tm = clock_time();
    if (get_cur_temp() >= g_temp_alarm) {
        set_alarm_status(1);
        set_buzzer(ON);
    } else {
        set_alarm_status(0);
        set_buzzer(OFF);
    }
}

/**
 * @brief temp alarm init
 * @param[in] none
 * @return none
 */
void tuya_app_temp_alarm_init(void)
{
    set_alarm_temp(TEMP_ALARM_DEFAULT);
    buzzer_pwm_init();
}

/**
 * @brief main loop of temperature alarm
 * @param[in] none
 * @return none
 */
void tuya_app_temp_alarm_loop(void)
{
    update_cur_temp();
}

/**
 * @brief dp data handler of temperature alarm
 * @param[in] dp_data：dp data array
 * @return none
 */
void tuya_app_temp_alarm_dp_data_handler(uint8_t *dp_data)
{
    switch (dp_data[0]) {
    case DP_ID_TEMP_ALARM:
        set_alarm_temp(dp_data[6]);
        *(dp_data+6) = g_temp_alarm;
        break;
    case DP_ID_ALARM:
    default:
        break;
    }
}

/**
 * @brief ble connect status change handler of temperature alarm
 * @param[in] status: ble connect status
 * @return none
 */
void tuya_app_temp_alarm_ble_connect_status_change_handler(tuya_ble_connect_status_t status)
{
    if (status == BONDING_CONN) {
        report_one_dp_data(DP_ID_ALARM, g_alarm_status);
        report_one_dp_data(DP_ID_TEMP_ALARM, g_temp_alarm);
    }
}

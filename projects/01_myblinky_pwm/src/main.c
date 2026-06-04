// will use the zephyr sample with minor modifications for learning purposes

// Copyrights so no one sues me :)
/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM.
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h> // wont see its output as we dont connect uart but wont hurt

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>


#include "my_pwm.h"

// all three of these resolve to the same node ( known from the overlay file ):
/*
    DT_ALIAS(pwm_led0)                        // via alias
    DT_NODELABEL(my_pwm_led_name)             // via label
    DT_PATH(pwmleds, pwm_led_0)              // via full path
*/
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

#define MIN_PERIOD PWM_SEC(1U) / 128U
#define MAX_PERIOD PWM_SEC(1U)

int main(void)
{
    uint32_t max_period;
    uint32_t period;
    uint8_t dir = 0U;
    int ret;

    printk("PWM-based blinky\n");

    ret = my_pwm_init(&pwm_led0);
    if (ret)
    {
        printk("PWM init failed: %d\n", ret);
        return 0;
    }

    /*
     * In case the default MAX_PERIOD value cannot be set for
     * some PWM hardware, decrease its value until it can.
     *
     * Keep its value at least MIN_PERIOD * 4 to make sure
     * the sample changes frequency at least once.
     */
    printk("Calibrating for channel %d...\n", pwm_led0.channel);
    max_period = MAX_PERIOD;
    while (my_pwm_set_duty(&pwm_led0, max_period, CONFIG_MY_PWM_DUTY_CYCLE) < 0)
    {
        max_period /= 2U;
        if (max_period < (4U * MIN_PERIOD))
        {
            printk("Error: PWM device "
                   "does not support a period at least %lu\n",
                   4U * MIN_PERIOD);
            return 0;
        }
    }

    printk("Done calibrating; maximum/minimum periods %u/%lu nsec\n",
           max_period, MIN_PERIOD);

    period = max_period;
    while (1)
    {
        ret = my_pwm_set_duty(&pwm_led0, period, CONFIG_MY_PWM_DUTY_CYCLE);
        if (ret)
        {
            printk("Error %d: failed to set pulse width\n", ret);
            return 0;
        }
        printk("Using period %d\n", period);

        period = dir ? (period * 2U) : (period / 2U);
        if (period > max_period)
        {
            period = max_period / 2U;
            dir = 0U;
        }
        else if (period < MIN_PERIOD)
        {
            period = MIN_PERIOD * 2U;
            dir = 1U;
        }

        k_sleep(K_SECONDS(4U));
    }
    return 0;
}

#ifndef MY_PWM_H
#define MY_PWM_H

#include <zephyr/drivers/pwm.h>
#include <stdint.h>

int my_pwm_init(const struct pwm_dt_spec *spec);

int my_pwm_set_duty(const struct pwm_dt_spec *spec, uint32_t period, uint8_t duty_percent);

#endif
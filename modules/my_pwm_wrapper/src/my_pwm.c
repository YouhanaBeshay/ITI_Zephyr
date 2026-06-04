#include "my_pwm.h"
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>


int my_pwm_init(const struct pwm_dt_spec *spec)
{
    if (!pwm_is_ready_dt(spec))
    {
        return -ENODEV;
    }

    return 0;
}

int my_pwm_set_duty(const struct pwm_dt_spec *spec, uint32_t period, uint8_t duty_percent)
{
    if (duty_percent > 100)
    {
        return -EINVAL;
    }

    uint32_t pulse = (period * duty_percent) / 100U;

    return pwm_set_dt(spec, period, pulse);
}
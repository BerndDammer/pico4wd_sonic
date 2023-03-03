#include <stdbool.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "ultrasonic.h"

#define ULTRASONIC_PIN_TRIGGER 6
#define ULTRASONIC_PIN_ECHO 7
#define ULTRASONIC_SLICE 3
#define ULTRASONIC_TRIG_CHANNEL PWM_CHAN_A

//#define FPWM 10
#define FPWM 50
#define PWM_CLK 500000
#define SONIC_SPEED 340.0

void ultrasonic_init(void)
{

    gpio_init(ULTRASONIC_PIN_TRIGGER);
    gpio_set_function(ULTRASONIC_PIN_TRIGGER, GPIO_FUNC_PWM);
    gpio_set_dir(ULTRASONIC_PIN_TRIGGER, true);

    gpio_init(ULTRASONIC_PIN_ECHO);
    gpio_set_function(ULTRASONIC_PIN_ECHO, GPIO_FUNC_SIO);
    gpio_set_dir(ULTRASONIC_PIN_ECHO, false);

    pwm_config pc = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&pc, PWM_DIV_FREE_RUNNING);

    //int div;
    double d;
    {
        d = (double) clock_get_hz(clk_sys) / (double) PWM_CLK;
    }
    pwm_config_set_clkdiv(&pc, d);

    //s->pc.div = div;
    pc.top = PWM_CLK / FPWM - 1;

    pwm_init(ULTRASONIC_SLICE, &pc, false);

    pwm_set_chan_level(ULTRASONIC_SLICE, ULTRASONIC_TRIG_CHANNEL, 5);

    pwm_set_enabled(ULTRASONIC_SLICE, true);
}

double ultrasonic_get(void)
{
}

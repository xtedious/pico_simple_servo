#include "../include/simple_servo.h"

#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include <stdio.h>

// printf debugging fo the win
#define DEBUG 1

#if DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...) // No bitches???
#endif

// Checks if the value x is between a(min) and b(max) returns 0 if true and
// non-zero if false
static int constrain(int x, int a, int b) {
    if (x > b || x < a) {
        return -1;
    }
    return 0;
}

inline float pwm_get_freq_div(pwm_properties *settings) {
    return (SYS_CLK * 1000.0f) /
           ((settings->pwm_wrap + 1) * settings->pwm_freq);
}

int servo_init(Servo *servo) {

    gpio_set_function(servo->gpio, GPIO_FUNC_PWM);

    /*float freq_div = pwm_get_freq_div(servo->pwm_settings);*/
    uint slice_num = pwm_gpio_to_slice_num(servo->gpio);
    pwm_config config = pwm_get_default_config();
    if (servo->pwm_settings->pwm_wrap) {
        pwm_config_set_wrap(&config, servo->pwm_settings->pwm_wrap);
    } else {
        servo->pwm_settings->pwm_wrap = (1 << 16) - 1;
    }

    float freq_div = pwm_get_freq_div(servo->pwm_settings);
    if (constrain(freq_div, 1.0f, 256.0f)) {
        DEBUG_PRINT("ERROR__--INVALID FREQUENCY PLEASE CHANGE--\n");
        return -1;
    }

    pwm_config_set_clkdiv(&config, pwm_get_freq_div(servo->pwm_settings));

    pwm_init(slice_num, &config, true);

    return 0;
}

int servo_angle(Servo *servo, uint angle) {

    if (!(angle >= 0 || angle <= servo->range)) {
        DEBUG_PRINT("Invalid Angle!!! angles allowed 0-%d", servo->range);
        return -1;
    }
    float servo_pos_ms = (((float)angle / (float)servo->range) *
                          (servo->time_max - servo->time_min)) +
                         servo->time_min;

    uint16_t servo_pos =
        (servo_pos_ms / (1000.0f / servo->pwm_settings->pwm_freq)) *
        servo->pwm_settings->pwm_wrap;

    DEBUG_PRINT("ms: %f\t pwm_pos:%hu\n", servo_pos_ms, servo_pos);

    pwm_set_gpio_level(servo->gpio, servo_pos);

    return 0;
}

Servo *servo_config(uint gpio_pin, uint servo_range, float pwm_time_min,
                    float pwm_time_max, uint target_pwm_freq) {

    static pwm_properties settings;
    settings.pwm_freq = target_pwm_freq;
    static Servo servo;
    servo.gpio = gpio_pin;
    servo.range = servo_range;
    servo.time_min = pwm_time_min;
    servo.time_max = pwm_time_max;
    servo.pwm_settings = &settings;

    servo_init(&servo);

    return &servo;
}

Servo *default_servo_config(uint gpio_pin) {

    static pwm_properties settings;
    settings.pwm_freq = 50;

    static Servo servo;
    servo.gpio = gpio_pin;
    servo.range = 180;
    servo.time_min = 0.45;
    servo.time_max = 2.2;
    servo.pwm_settings = &settings;

    servo_init(&servo);

    return &servo;
}

#ifndef _SIMPLE_SERVO_H_
#define _SIMPLE_SERVO_H_

#include "hardware/pwm.h"

#define SYS_CLK 125000 // System clock in kHz

// Servo and PWM Properties

typedef struct {
        uint pwm_freq;
        uint pwm_wrap;
} pwm_properties;

typedef struct {
        uint gpio;
        uint range;     // Range of the servo in degrees
        float time_min; // length of the pulse for the minimum position (in ms)
        float time_max; // length of the pulse for the maximum position (in ms)
        pwm_properties *pwm_settings;
} Servo;
// Servo Setup Code

// Initializing the servo motor manually using the Servo struct
int servo_init(Servo *servo);

// Configure the servo motor using certain flags - calls servo_init()
Servo *servo_config(uint gpio_pin, uint servo_range, float pwm_time_min,
                    float pwm_time_max, uint target_pwm_freq);

// Configures a 180 degree servo with 50Hz PWM frequency and time_range between
// 0,45-2.1ms
Servo default_servo_config(uint gpio_pin);
// Servo Functions

// Makes the servo move to the desired angle
int servo_angle(Servo *servo, uint angle);

#endif // _SIMPLE_SERVO_H_

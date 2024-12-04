#include <stdio.h>

#include "../include/simple_servo.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    Servo servo1 = default_servo_config(1);
    Servo servo2 = default_servo_config(2);

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    while (1) {
        servo_angle(&servo1, 90);
        servo_angle(&servo2, 90);
        sleep_ms(100);
    }
}

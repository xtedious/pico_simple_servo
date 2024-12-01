#include <stdio.h>

#include "../include/simple_servo.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    Servo *servo1 = default_servo_config(1);
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    while (1) {
        for (int i = 0; i <= 180; i++) {
            servo_angle(servo1, i);
            sleep_ms(10);
        }
        for (int i = 180; i >= 0; i--) {
            servo_angle(servo1, i);
            sleep_ms(10);
        }
        gpio_put(25, !gpio_get(25));
        sleep_ms(1000);

        servo_angle(servo1, 0);
        sleep_ms(1000);

        servo_angle(servo1, 180);
        sleep_ms(1000);

        servo_angle(servo1, 135);
        sleep_ms(1000);

        servo_angle(servo1, 45);
        sleep_ms(1000);

        gpio_put(25, !gpio_get(25));
    }
}

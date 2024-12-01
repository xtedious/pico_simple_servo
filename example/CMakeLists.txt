cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(servo_test C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(servo_test
    example.c 
    ../src/simple_servo.c
)

target_link_libraries(servo_test
    pico_stdlib
    hardware_pwm
)

pico_enable_stdio_usb(servo_test 1)
pico_enable_stdio_uart(servo_test 0)

pico_add_extra_outputs(servo_test)

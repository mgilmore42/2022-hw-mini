/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// API documentation: https://raspberrypi.github.io/pico-sdk-doxygen/modules.html

// Fade an LED between low and high brightness.
// An interrupt handler updates the PWM slice's output level each time the counter wraps.

#include "pico/stdlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#ifndef PICO_DEFAULT_LED_PIN
#error pwm/led_fade example requires a board with a regular LED
#endif

#define MAX_LED_BRIGHTNESS 255
#define MIN_LED_BRIGHTNESS 0

#define LED_ON  65535
#define LED_OFF 0

#define TIME_UNIT 200

// function turns LED on
void led_on(){
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, LED_ON);
}

// function turns LED on
void led_off(){
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, LED_OFF);
}

// creates a morse dot
void morse_dot() {
    led_on();
    sleep_ms(TIME_UNIT * 1);
    led_off();
    sleep_ms(TIME_UNIT * 1);
}

// creates morse dash
void morse_dash() {
    led_on();
    sleep_ms(TIME_UNIT * 3);
    led_off();
    sleep_ms(TIME_UNIT * 1);
}

// define end of a letter
void morse_endletter() {
    led_off();
    sleep_ms(TIME_UNIT * 3);
}

// define end of a letter
void morse_endword() {
    led_off();
    sleep_ms(TIME_UNIT * 7);
}

// define the letter h '....'
void morse_h() {
    morse_dot();
    morse_dot();
    morse_dot();
    morse_dot();

    morse_endletter();
}

// define the letter e '.'
void morse_e() {
    morse_dot();

    morse_endletter();
}

// define the letter l '.-..'
void morse_l() {
    morse_dot();
    morse_dash();
    morse_dot();
    morse_dot();

    morse_endletter();
}

// define the letter o '---'
void morse_o() {
    morse_dash();
    morse_dash();
    morse_dash();

    morse_endletter();
}

// define the letter w '.--'
void morse_w() {
    morse_dot();
    morse_dash();
    morse_dash();

    morse_endletter();
}

// define the letter r '.-.'
void morse_r() {
    morse_dot();
    morse_dash();
    morse_dot();

    morse_endletter();
}

// define the letter d '-..'
void morse_d() {
    morse_dash();
    morse_dot();
    morse_dot();

    morse_endletter();
}

void on_pwm_wrap() {
// this is the interrupt handler, called each time the PWM counter wraps
    morse_h(); //
    morse_e(); //
    morse_l(); //
    morse_l(); //
    morse_o(); //

    morse_endword();

    morse_w(); //
    morse_o(); //
    morse_r(); //
    morse_l(); //
    morse_d(); //

    morse_endword();

}


int main(void) {
    // Tell the LED pin that the PWM is in charge of its value.
    gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
    // Figure out which slice we just connected to the LED pin
    uint slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

    // Mask our slice's IRQ output into the PWM block's single interrupt line
    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);

    // Register the interrupt handler: here it's function on_pwm_wrap() defined above
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // Get some sensible defaults for the slice configuration. By default, the
    // counter is allowed to wrap over its maximum range (0 to 2**16-1)
    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, 4.f);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);

    // This empty loop allows the PWM interrupt handler to effectively take over program control.
    // tight_loop_contents() is an empty no-op function that's a placeholder.
    while (true)
        tight_loop_contents();
}

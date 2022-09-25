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

#define LED_ON  1
#define LED_OFF 0

#define TIME_UNIT 100

// function turns LED on
void led_on(){
    gpio_put(PICO_DEFAULT_LED_PIN, LED_ON);
}

// function turns LED on
void led_off(){
    gpio_put(PICO_DEFAULT_LED_PIN, LED_OFF);
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

// prints "hello word " in morse code
void morse_hello_world() {
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
    // enables LED pin
    gpio_init(PICO_DEFAULT_LED_PIN);

    // sets LED pin to be output
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // repeates "hello world " in morse code
    while (true){
        morse_hello_world();
    }
}

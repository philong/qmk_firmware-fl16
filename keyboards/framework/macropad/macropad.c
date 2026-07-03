// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(RGB_MATRIX_ENABLE)
const is31fl3743a_led_t PROGMEM g_is31fl3743a_leds[IS31FL3743A_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |   R location
 *   |   |         G location
 *   |   |         |         B location
 *   |   |         |         | */
    // Re-arranged in LED ID order so it matches with the physical location array
    {0,  SW1_CS3,  SW1_CS2,  SW1_CS1}, // LED 1
    {0,  SW2_CS3,  SW2_CS2,  SW2_CS1}, // LED 2
    {0,  SW3_CS3,  SW3_CS2,  SW3_CS1}, // LED 3
    {0,  SW4_CS3,  SW4_CS2,  SW4_CS1}, // LED 4

    {0,  SW1_CS6,  SW1_CS5,  SW1_CS4}, // LED 5
    {0,  SW3_CS6,  SW3_CS5,  SW3_CS4}, // LED 6
    {0,  SW4_CS6,  SW4_CS5,  SW4_CS4}, // LED 7
    {0,  SW2_CS6,  SW2_CS5,  SW2_CS4}, // LED 8

    {0,  SW1_CS9,  SW1_CS8,  SW1_CS7}, // LED 9
    {0,  SW2_CS9,  SW2_CS8,  SW2_CS7}, // LED 10
    {0,  SW3_CS9,  SW3_CS8,  SW3_CS7}, // LED 11
    {0,  SW4_CS9,  SW4_CS8,  SW4_CS7}, // LED 12

    {0, SW1_CS12, SW1_CS11, SW1_CS10}, // LED 13
    {0, SW2_CS12, SW2_CS11, SW2_CS10}, // LED 14
    {0, SW3_CS12, SW3_CS11, SW3_CS10}, // LED 15
    {0, SW4_CS12, SW4_CS11, SW4_CS10}, // LED 16

    {0, SW2_CS15, SW2_CS14, SW2_CS13}, // LED 17
    {0, SW3_CS15, SW3_CS14, SW3_CS13}, // LED 18
    {0, SW1_CS15, SW1_CS14, SW1_CS13}, // LED 19
    {0, SW4_CS15, SW4_CS14, SW4_CS13}, // LED 20

    {0, SW1_CS18, SW1_CS17, SW1_CS16}, // LED 21
    {0, SW2_CS18, SW2_CS17, SW2_CS16}, // LED 22
    {0, SW3_CS18, SW3_CS17, SW3_CS16}, // LED 23
    {0, SW4_CS18, SW4_CS17, SW4_CS16}, // LED 24
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {     4,      7,      6,      9,      0,      1,      3,     11, },
  {     8,     20,     21,     23,     15,     14,     18,     19, },
  {    12,      5,      2, NO_LED,     17,     16,     13,     10, },
  {NO_LED, NO_LED, NO_LED, NO_LED,     22, NO_LED, NO_LED, NO_LED, },
}, {
  // LED Index to Physical Position
  {  73,  10 }, // LED 1
  {  73,  24 }, // LED 2
  {  73,   0 }, // LED 3
  {  73,  37 }, // LED 4
  {   0,  10 }, // LED 5
  {   0,   0 }, // LED 6
  {   0,  37 }, // LED 7
  {   0,  24 }, // LED 8
  {   0,  64 }, // LED 9
  {   0,  50 }, // LED 10
  {  73,  64 }, // LED 11
  {  73,  50 }, // LED 12
  { 223,  64 }, // LED 13
  { 223,  50 }, // LED 14
  { 150,  64 }, // LED 15
  { 150,  50 }, // LED 16
  { 223,  24 }, // LED 17
  { 223,   0 }, // LED 18
  { 223,  10 }, // LED 19
  { 223,  37 }, // LED 20
  { 150,  10 }, // LED 21
  { 150,  24 }, // LED 22
  { 150,   0 }, // LED 23
  { 150,  37 }, // LED 24
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4
} };
#endif

void keyboard_post_init_user(void) {
    // Sync initial numlock state from the host
    if (host_keyboard_led_state().num_lock) {
        layer_on(_NUMLOCK);
    } else {
        layer_off(_FN);
    }
}

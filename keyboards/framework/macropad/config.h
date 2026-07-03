// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#define MATRIX_COLS 8
#define MATRIX_ROWS 4

#define IS31FL3743A_I2C_ADDRESS_1 IS31FL3743A_I2C_ADDRESS_GND_GND
#define RGB_MATRIX_LED_COUNT 24
// Enable only the first 4 SW and disable software shutdown
// Otherwise voltage on SW pins without LEDs causes voltage rise and noise
#define IS31FL3743A_CONFIGURATION 0x71

// Limit current to ensure max current draw is just about 500mA
// when white at 100% brightness
#define IS31FL3743A_GLOBAL_CURRENT 185

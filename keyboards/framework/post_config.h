// Copyright 2026 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef FRAMEWORK_DISPLAY_TOGGLE_HID
// Widen System Control HID usage range to include SYSTEM_DISPLAY_TOGGLE_INT_EXT (0xB5).
// Note: This range spans Generic Desktop D-pad usages (0x90..0x93), which may cause
// hosts like Steam to misidentify the keyboard as a gamepad (see QMK #26295).
#    ifndef SYSTEM_CONTROL_USAGE_MAXIMUM
#        define SYSTEM_CONTROL_USAGE_MAXIMUM 0x00B5
#    endif
#endif

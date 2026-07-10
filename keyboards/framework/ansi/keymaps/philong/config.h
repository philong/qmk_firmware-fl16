// Copyright 2026 Phi-Long Do
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Home row mods tuning
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define CHORDAL_HOLD
#define FLOW_TAP_TERM 100
#define SPECULATIVE_HOLD

// No tap auto-repeat on tap-hold keys, except space (see get_quick_tap_term)
#define QUICK_TAP_TERM 0
#define QUICK_TAP_TERM_PER_KEY

#define CAPS_WORD_IDLE_TIMEOUT 5000

// Oneshot mods set by the punctuation mod expire if unused
#define ONESHOT_TIMEOUT 2000

// Capital-accent combos are hold-only (see get_combo_must_hold)
#define COMBO_MUST_HOLD_PER_COMBO
#define COMBO_HOLD_TERM 100

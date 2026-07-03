// Copyright 2026 Phi-Long Do
// SPDX-License-Identifier: GPL-2.0-or-later
//
// GACS-style home-row-mods keymap with nav/numbers and fn/symbols layers

#include QMK_KEYBOARD_H
#include "framework.h"

enum _layers {
  _BASE,
  _FN,
  _FN_LOCK,
  _FM,
  _NAV,   // Space held: navigation + numbers
  _SYM,   // G held: F-keys + shifted symbols
  _SYMA,  // H held: same as _SYM but with Del/Esc
};

// Home row mods
#define HM_A    LGUI_T(KC_A)
#define HM_S    LALT_T(KC_S)
#define HM_D    LSFT_T(KC_D)
#define HM_F    LCTL_T(KC_F)
#define HM_J    RCTL_T(KC_J)
#define HM_K    RSFT_T(KC_K)
#define HM_L    LALT_T(KC_L)
#define HM_SCLN RGUI_T(KC_SCLN)
// Extra bottom row shift mods
#define HM_C    LSFT_T(KC_C)
#define HM_COMM RSFT_T(KC_COMM)
// Extra bottom row mods
#define HM_V    RALT_T(KC_V)
#define HM_M    RALT_T(KC_M)
// Layer taps
#define LT_G    LT(_SYM, KC_G)
#define LT_H    LT(_SYMA, KC_H)
#define LT_SPC  LT(_NAV, KC_SPC)
// Mod-taps on the _NAV number cluster
#define NM_1    RALT_T(KC_1)
#define NM_4    RCTL_T(KC_4)
#define NM_5    RSFT_T(KC_5)
#define NM_6    LALT_T(KC_6)
#define NM_DOT  RGUI_T(KC_DOT)
// Mod-taps on the _SYM F-key cluster
#define SM_SCRL LGUI_T(KC_SCRL)
#define SM_F3   RALT_T(KC_F3)
#define SM_F4   LALT_T(KC_F4)
#define SM_F5   LSFT_T(KC_F5)
#define SM_F6   LCTL_T(KC_F6)
// Tap for [, hold for ] (handled in process_record_user)
#define BRC_LT  LT(0, KC_LBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │ESC  │Mut│vDn│vUp│Prv│Ply│Nxt│bDn│bUp│Scn│Air│Prt│App│Del │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backsp│
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \  │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │CapsWd│A/⊞│S/⎇│D/⇧│F/^│G/L5│H/L6│J/^│K/⇧│L/⎇│;/⊞│ ' │Enter│
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │ Shift  │ Z │ X │C/⇧│V/⎇│ B │ N │M/⎇│,/⇧│ . │ / │ Shift │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     * 11 keys │Ctrl│FN │GUI│Alt│      Space/L4     │Alt│Ctl│ ←  │↑ ↓│  → │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CW_TOGG, HM_A,    HM_S,    HM_D,    HM_F,    LT_G,    LT_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    HM_C,    HM_V,    KC_B,    KC_N,    HM_M,    HM_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT,          LT_SPC,                    KC_RALT, KC_RCTL, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT
    ),
    // Function layer (same as the default keymap)
    [_FN] = LAYOUT(
        FN_LOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_SPDU, RM_VALU, _______, _______, KC_PAUS, _______, _______, _______,
        _______, _______, _______, RM_PREV,RM_HUED, RM_SATD, RM_SPDD, RM_VALD, KC_SCRL, _______, _______, _______,          _______,
        _______,          _______, _______, BL_BRTG, _______, KC_BRK,  _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______,          BL_STEP,                   _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
    // Function lock layer
    // Everything on F-row locked to function layer, except ESC and DEL
    [_FN_LOCK] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, MO(_FM), _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),
    // Locked+temporary FN (back to base plus extra keys)
    [_FM] = LAYOUT(
        FN_LOCK, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_SPDU, RM_VALU, _______, _______, KC_PAUS, _______, _______, _______,
        _______, _______, _______, RM_PREV,RM_HUED, RM_SATD, RM_SPDD, RM_VALD, KC_SCRL, _______, _______, _______,          _______,
        _______,          _______, _______, BL_BRTG, _______, KC_BRK,  _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______,          BL_STEP,                   _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
     /*
     * Navigation + numbers (Space held)
     *         ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┐
     * 14 keys │     │   │   │   │   │   │   │   │   │   │   │   │   │    │
     *         ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
     * 14 keys │   │   │   │   │   │   │   │   │   │   │   │   │   │      │
     *         ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * 14 keys │     │Ins│Hom│ ↑ │End│PgU│ = │ 7 │ 8 │ 9 │ ` │   │   │    │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │Backsp│CWd│ ← │ ↓ │ → │PgD│ - │4/^│5/⇧│6/⎇│./⊞│Ent│       │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │        │Und│Cut│Cpy│Pst│Red│ 0 │1/⎇│ 2 │ 3 │ \ │         │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     * 11 keys │    │   │   │   │      (held)       │   │   │    │   │    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     */
    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_EQL,  KC_7,    KC_8,    KC_9,    KC_GRV,  _______, _______, _______,
        KC_BSPC, CW_TOGG, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_MINS, NM_4,    NM_5,    NM_6,    NM_DOT,  KC_ENT,           _______,
        _______,          C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(S(KC_Z)), KC_0, NM_1,    KC_2,    KC_3,    KC_BSLS,          _______,
        _______, _______, _______, _______,          _______,                   _______, _______, _______, _______, _______, _______
    ),
     /*
     * F-keys + symbols (G held)
     *         ┌ ... F-row and number row transparent ... ┐
     *         ├─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┤
     * 14 keys │     │Prt│F7 │F8 │F9 │F12│ + │ & │ * │ ( │ ~ │   │   │    │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │CapsWd│ScL│F4 │F5 │F6 │F11│ _ │ $ │ % │ ^ │[/]│Ent│       │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │        │Pau│F1 │F2 │F3 │F10│ ) │ ! │ @ │ # │ | │         │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     * 11 keys │    │   │   │   │       Enter       │   │   │    │   │    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     */
    [_SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_PSCR, KC_F7,   KC_F8,   KC_F9,   KC_F12,  KC_PLUS, KC_AMPR, KC_ASTR, KC_LPRN, KC_TILD, _______, _______, _______,
        CW_TOGG, SM_SCRL, SM_F4,   SM_F5,   SM_F6,   KC_F11,  KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, BRC_LT,  KC_ENT,           _______,
        _______,          KC_PAUS, KC_F1,   KC_F2,   SM_F3,   KC_F10,  KC_RPRN, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,          _______,
        _______, _______, _______, _______,          KC_ENT,                    _______, _______, _______, _______, _______, _______
    ),
    // Same as _SYM, but with Delete on Caps and Escape on Space (H held)
    [_SYMA] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_PSCR, KC_F7,   KC_F8,   KC_F9,   KC_F12,  KC_PLUS, KC_AMPR, KC_ASTR, KC_LPRN, KC_TILD, _______, _______, _______,
        KC_DEL,  SM_SCRL, SM_F4,   SM_F5,   SM_F6,   KC_F11,  KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, BRC_LT,  KC_ENT,           _______,
        _______,          KC_PAUS, KC_F1,   KC_F2,   SM_F3,   KC_F10,  KC_RPRN, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,          _______,
        _______, _______, _______, _______,          KC_ESC,                    _______, _______, _______, _______, _______, _______
    ),
};

// Chordal Hold handedness. Only Space is exempted ('*'),
// as its layer is meant to be used with either hand.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',      'R',
    'L',      'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R',      'R',
    'L', 'L', 'L', 'L',           '*',           'R', 'R', 'R', 'R', 'R', 'R'
);

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { // Slower pinkies, avoid accidental GUI
        case HM_A:
        case HM_SCLN:
            return TAPPING_TERM + 200;
        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_SPC: // Keep tap-then-hold auto-repeat for space only
            return 150;
        default:
            return QUICK_TAP_TERM;
    }
}

bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) { // Instant left Shift/Ctrl, e.g. for mouse clicks
        case HM_D:
        case HM_F:
            return true;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Make sure to keep FN Lock even after reset
        case FN_LOCK:
            if (record->event.pressed) {
                if (layer_state_is(_FN)) {
                    set_single_persistent_default_layer(_FN_LOCK);
                }
                if (layer_state_is(_FM)) {
                    set_single_persistent_default_layer(_BASE);
                }
            }
            return false;
        case BRC_LT:
            if (!record->tap.count) { // Held: send ] instead of layer 0
                if (record->event.pressed) {
                    register_code(KC_RBRC);
                } else {
                    unregister_code(KC_RBRC);
                }
                return false;
            }
            return true;
        default:
            break;
    }
    return true;
}

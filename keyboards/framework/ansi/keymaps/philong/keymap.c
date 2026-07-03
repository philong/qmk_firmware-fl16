// Copyright 2026 Phi-Long Do
// SPDX-License-Identifier: GPL-2.0-or-later
//
// GACS-style home-row-mods keymap with nav/numbers and fn/symbols layers
//

#include QMK_KEYBOARD_H
#include "framework.h"

#include "keymap_colemak.h"

enum _layers {
  _BASE,
  _FN,
  _FN_LOCK,
  _FM,
  _NAV,   // Space held: navigation + numbers
  _SYM,   // G held: F-keys + shifted symbols
  _SYMA,  // H held: same as _SYM but with Del/Esc
  _ACC,   // V or M held: French accents (custom Colemak)
};

// Accented characters, sent as AltGr dead key + letter scancode sequences.
enum custom_keycodes {
  FR_AGRV = KC_CPLT + 1, // à
  FR_ACIR,               // â
  FR_EACU,               // é
  FR_EGRV,               // è
  FR_ECIR,               // ê
  FR_EDIA,               // ë
  FR_ICIR,               // î
  FR_IDIA,               // ï
  FR_OCIR,               // ô
  FR_UGRV,               // ù
  FR_UCIR,               // û
};

// {dead key, letter}, indexed by keycode - FR_AGRV
static const uint16_t accent_sequences[][2] = {
    [FR_AGRV - FR_AGRV] = {RALT(KC_S), KC_A},
    [FR_ACIR - FR_AGRV] = {RALT(KC_X), KC_A},
    [FR_EACU - FR_AGRV] = {RALT(KC_F), KC_K},
    [FR_EGRV - FR_AGRV] = {RALT(KC_S), KC_K},
    [FR_ECIR - FR_AGRV] = {RALT(KC_X), KC_K},
    [FR_EDIA - FR_AGRV] = {RALT(KC_G), KC_K},
    [FR_ICIR - FR_AGRV] = {RALT(KC_X), KC_L},
    [FR_IDIA - FR_AGRV] = {RALT(KC_G), KC_L},
    [FR_OCIR - FR_AGRV] = {RALT(KC_X), KC_SCLN},
    [FR_UGRV - FR_AGRV] = {RALT(KC_S), KC_I},
    [FR_UCIR - FR_AGRV] = {RALT(KC_X), KC_I},
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
// Layer taps
#define LT_G    LT(_SYM, KC_G)
#define LT_H    LT(_SYMA, KC_H)
#define LT_V    LT(_ACC, KC_V)
#define LT_M    LT(_ACC, KC_M)
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
     * 12 keys │ Shift  │ Z │ X │C/⇧│V/L7│ B │ N │M/L7│,/⇧│ . │ / │ Shift │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     * 11 keys │Ctrl│FN │GUI│Alt│      Space/L4     │Alt│Ctl│ ←  │↑ ↓│  → │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CW_TOGG, HM_A,    HM_S,    HM_D,    HM_F,    LT_G,    LT_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    HM_C,    LT_V,    KC_B,    KC_N,    LT_M,    HM_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
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
     /*
     * French accents (V or M held; shifted for capitals via C+V / M+, chord)
     *         ┌ ... F-row and number row transparent ... ┐
     *         ├─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────┤
     * 14 keys │     │ â │ ë │ ê │ è │⎇gT│⎇gY│ ù │ û │ ï │⎇gP│   │   │    │
     *         ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴────┤
     * 13 keys │CapsWd│ à │⎇gS│ é │⎇gF│⎇gG│⎇gH│⎇gJ│⎇gK│ î │ ô │Ent│       │
     *         ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───────┤
     * 12 keys │        │⎇gZ│⎇gX│⎇gC│⎇gV│⎇gB│⎇gN│⎇gM│⎇g,│⎇g.│⎇g/│         │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     * 11 keys │    │   │   │   │    AltGr+Space    │   │   │    │   │    │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     */
    [_ACC] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, FR_ACIR, FR_EDIA, FR_ECIR, FR_EGRV, RALT(KC_T), RALT(KC_Y), FR_UGRV, FR_UCIR, FR_IDIA, RALT(KC_P), _______, _______, _______,
        CW_TOGG, FR_AGRV, RALT(KC_S), FR_EACU, RALT(KC_F), RALT(KC_G), RALT(KC_H), RALT(KC_J), RALT(KC_K), FR_ICIR, FR_OCIR, KC_ENT, _______,
        _______,          RALT(KC_Z), RALT(KC_X), RALT(KC_C), RALT(KC_V), RALT(KC_B), RALT(KC_N), RALT(KC_M), RALT(KC_COMM), RALT(KC_DOT), RALT(KC_SLSH), _______,
        _______, _______, _______, _______,          RALT(KC_SPC),              _______, _______, _______, _______, _______, _______
    ),
};

// Chordal Hold handedness. The layer-tap keys (G, H, V, M) and Space are
// exempted ('*') so their layers remain reachable with same-hand keys.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', '*', '*', 'R', 'R', 'R', 'R', 'R',      'R',
    'L',      'L', 'L', 'L', '*', 'L', 'R', '*', 'R', 'R', 'R',      'R',
    'L', 'L', 'L', 'L',           '*',           'R', 'R', 'R', 'R', 'R', 'R'
);

// Colemak layout: letters are identified by
// what the host maps the scancode to, not the QWERTY legend: KC_SCLN is the
// letter O and KC_P is ';' (CM_* aliases from keymap_colemak.h).
static bool is_alpha(uint16_t keycode) {
    return (KC_A <= keycode && keycode <= KC_O) // Exclude CM_SCLN == KC_P
           || (keycode == CM_O)                 // Include CM_O == KC_SCLN
           || (KC_Q <= keycode && keycode <= KC_Z);
}

// Colemak-aware Caps Word: the default handler would shift KC_P (host ';')
// and deactivate on KC_SCLN (host 'o'). No is_flow_tap_key override is
// needed: the default list covers every Colemak alpha and ';' already.
bool caps_word_press_user(uint16_t keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    if (is_alpha(keycode) || keycode == KC_MINS) {
        add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
        return true;
    }

    switch (keycode) {
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

// C+V or M+, chorded: shifted accent layer for capitals
const uint16_t PROGMEM accent_combo_left[]  = {HM_C, LT_V, COMBO_END};
const uint16_t PROGMEM accent_combo_right[] = {LT_M, HM_COMM, COMBO_END};
combo_t key_combos[] = {
    COMBO(accent_combo_left, LM(_ACC, MOD_LSFT)),
    COMBO(accent_combo_right, LM(_ACC, MOD_LSFT)),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Slower pinkies, avoid accidental GUI
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

static bool process_accent(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        const uint16_t dead    = accent_sequences[keycode - FR_AGRV][0];
        const uint16_t letter  = accent_sequences[keycode - FR_AGRV][1];
        const uint8_t  mods    = get_mods();
        const bool     shifted = ((mods | get_oneshot_mods()) & MOD_MASK_SHIFT) != 0;
        // The dead key must be sent unshifted, only the letter is capitalized
        del_oneshot_mods(MOD_MASK_SHIFT);
        del_mods(MOD_MASK_SHIFT);
        tap_code16(dead);
        tap_code16(shifted ? S(letter) : letter);
        set_mods(mods);
    }
    return false;
}

// Convert 8-bit mods to the 5-bit format used in keycodes. This is lossy: if
// left and right handed mods were mixed, they all become right handed.
static uint8_t get_keycode_mods(uint8_t mods) {
    return ((mods & 0xf0) ? /* set right hand bit */ 0x10 : 0)
           // Combine right and left hand mods.
           | (((mods >> 4) | mods) & 0xf);
}

// Combine basic keycode with mods.
static uint16_t combine_keycode(uint16_t keycode, uint8_t mods) {
    return (get_keycode_mods(mods) << 8) | keycode;
}

// Punctuation mod: `,` or `;` tapped before a letter acts as a oneshot mod on
// it: ",a" -> "A" (Shift), ";a" -> AltGr+a (à on the custom French Colemak
// host), and ";;" / ",;" / ";," -> Shift+AltGr. The punctuation is typed
// immediately and backspaced when a letter follows within ONESHOT_TIMEOUT, so
// it stays plain punctuation otherwise. ",," escapes to a literal ",,".
static bool process_punctuation_mod(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    uint16_t tap_keycode;

    if (IS_QK_LAYER_TAP(keycode) || IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count == 0) {
            return true; // Key is being held.
        }
        tap_keycode = get_tap_keycode(keycode);
    } else {
        tap_keycode = keycode;
    }

    static uint8_t      comma_count  = 0;
    static uint8_t      scln_count   = 0;
    static uint16_t     last_keycode = KC_NO;
    static fast_timer_t timer        = 0;

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (!all_mods && (is_alpha(tap_keycode) || tap_keycode == CM_QUOT || tap_keycode == CM_SLSH)) {
        last_keycode = KC_NO;

        const bool shifted_ralted = (comma_count == 0 && scln_count == 2) || (comma_count == 1 && scln_count == 1);
        const bool shifted        = (comma_count == 1 && scln_count == 0) || shifted_ralted;
        const bool ralted         = (comma_count == 0 && scln_count == 1) || shifted_ralted;

        if ((!shifted && !ralted) || timer_elapsed_fast(timer) > ONESHOT_TIMEOUT) {
            comma_count = 0;
            scln_count  = 0;
            return true;
        }

        for (uint8_t i = comma_count + scln_count; i > 0; --i) {
            tap_code(KC_BSPC);
        }
        comma_count = 0;
        scln_count  = 0;

        if (shifted) {
            set_oneshot_mods(get_oneshot_mods() | MOD_BIT(KC_LSFT));
        }

        if (ralted) {
            set_oneshot_mods(get_oneshot_mods() | MOD_BIT(KC_RALT));
        }

        return true;
    }

    if (all_mods) {
        tap_keycode = combine_keycode(tap_keycode, all_mods);
    }

    switch (tap_keycode) {
        case CM_COMM:
            timer = timer_read_fast();
            ++comma_count;

            // ",," cancels the pending mod and yields a literal ",,"
            if (last_keycode == CM_COMM && comma_count == 2 && scln_count == 0) {
                last_keycode = KC_NO;
                comma_count  = 0;
                scln_count   = 0;
                tap_code(KC_COMM);
                return false;
            }
            break;
        case CM_SCLN: // ';' is scancode KC_P on the Colemak host
            timer = timer_read_fast();
            ++scln_count;
            break;
        default:
            comma_count = 0;
            scln_count  = 0;
    }

    last_keycode = tap_keycode;

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_punctuation_mod(keycode, record)) {
        return false;
    }

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
        case FR_AGRV ... FR_UCIR:
            return process_accent(keycode, record);
        default:
            break;
    }
    return true;
}

// Copyright 2026 Phi-Long Do
// SPDX-License-Identifier: GPL-2.0-or-later
//
// GACS-style home-row-mods keymap with nav/numbers and fn/symbols layers
//

#include QMK_KEYBOARD_H
#include "framework.h"

#include "keymap_colemak.h"

#ifdef COMBO_ENABLE
const uint16_t PROGMEM boot_combo[] = {KC_LALT, KC_RALT, KC_ESC, KC_DEL, COMBO_END};
combo_t key_combos[] = {
    COMBO(boot_combo, QK_BOOT)
};
#endif

enum _layers {
  _BASE,
  _FN,
  _FN_LOCK,
  _FM,
  _NAV,   // Space held: navigation + numbers
  _SYM,   // G held: F-keys + shifted symbols
  _SYMA,  // H held: same as _SYM but with Del/Esc
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
  FR_UDIA,               // ü
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
    [FR_UDIA - FR_AGRV] = {RALT(KC_G), KC_I},
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
#define LT_SPC  LT(_NAV, KC_SPC)
// AltGr mod-taps: French accents (see process_altgr_accent)
#define AG_V    RALT_T(KC_V)
#define AG_M    RALT_T(KC_M)
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
     * 12 keys │ Shift  │ Z │ X │C/⇧│V/⎇g│ B │ N │M/⎇g│,/⇧│ . │ / │ Shift │
     *         ├────┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┴┬───┬────┤
     * 11 keys │Ctrl│FN │GUI│Alt│      Space/L4     │Alt│Ctl│ ←  │↑ ↓│  → │
     *         └────┴───┴───┴───┴───────────────────┴───┴───┴────┴───┴────┘
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, KC_SCRN, KC_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        CW_TOGG, HM_A,    HM_S,    HM_D,    HM_F,    LT_G,    LT_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    HM_C,    AG_V,    KC_B,    KC_N,    AG_M,    HM_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, MO(_FN), KC_LGUI, KC_LALT,          LT_SPC,                    KC_RALT, KC_RCTL, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT
    ),
    // Function layer (same as the default keymap)
    [_FN] = LAYOUT(
        FN_LOCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_SPDU, RM_VALU, _______, _______, KC_PAUS, _______, _______, _______,
        _______, _______, _______, RM_PREV, RM_HUED, RM_SATD, RM_SPDD, RM_VALD, KC_SCRL, _______, _______, _______,          _______,
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
        _______, _______, _______, RM_PREV, RM_HUED, RM_SATD, RM_SPDD, RM_VALD, KC_SCRL, _______, _______, _______,          _______,
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

// Chordal Hold handedness. The layer-tap keys (G, H, Space) and the AltGr
// mod-taps (V, M) are exempted ('*') so their holds remain reachable with
// same-hand keys.
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
// and deactivate on KC_SCLN (host 'o').
bool caps_word_press_user(uint16_t keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    if (is_alpha(keycode) || keycode == KC_MINS) {
        add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
        return true;
    }

    switch (keycode) {
        // Keycodes that continue Caps Word, without shifting.
        // Accents handle capitalization themselves (see process_accent);
        // the dead key must stay unshifted, so no weak shift here.
        case FR_AGRV ... FR_UDIA:
        // ',' (CM_COMM) and ';' (CM_SCLN) may be punctuation-mod prefixes of an accented letter
        // (backspaced when a letter follows), so they must not break the word.
        // Adding only ';' for accented letters, ',' for caps would be redundant.
        case CM_SCLN:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

#ifdef FLOW_TAP_TERM
    bool is_flow_tap_key(uint16_t keycode) {
        if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
            return false; // Disable Flow Tap on hotkeys.
        }

        const uint16_t tap_keycode = get_tap_keycode(keycode);

        if (is_alpha(tap_keycode)) {
            return true;
        }

        switch (tap_keycode) {
            // case KC_SPC:
            case CM_DOT:
            case CM_COMM:
            case CM_SCLN:
            case CM_SLSH:
                return true;
        }

        return false;
    }

    uint16_t get_flow_tap_term(
        uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {

        const uint16_t tap_keycode = get_tap_keycode(keycode);

        // home-row-mods
        switch (tap_keycode) {
            case CM_A:
            case CM_R:
            case CM_S:
            case CM_T:
            case CM_N:
            case CM_E:
            case CM_I:
            case CM_O:
                return 0;  // Disable filter for these keys.
        }

        // Don't force a tap on the keys typed right after an AltGr accent
        // key, so accents stay reachable at typing speed. Only the accented
        // letters that are tap-hold keys on base need listing; plain keys
        // never reach this hook.
        switch (prev_keycode) {
            case AG_V:
                switch (tap_keycode) {
                    case CM_E:
                    case CM_I:
                    case CM_O:
                        return 0;
                }
                break;
            case AG_M:
                switch (tap_keycode) {
                    case CM_A:
                    case CM_C:
                    case CM_V:
                    case CM_COMM:
                        return 0;
                }
                break;
            case HM_C:
                if (tap_keycode == CM_V) {
                    return 0;
                }
                break;
            case HM_COMM:
                if (tap_keycode == CM_M) {
                    return 0;
                }
                break;
        }

        if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
            return FLOW_TAP_TERM;
        }

        return 0;  // Disable Tap Flow.
    }
#endif

#ifdef CHORDAL_HOLD
    bool get_chordal_hold(
        uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
        uint16_t other_keycode, keyrecord_t* other_record) {

        // LGui+L screen lock protection: force HM_A to tap when CM_L is pressed
        if (tap_hold_keycode == HM_A && get_tap_keycode(other_keycode) == CM_L) {
            return false;
        }
        return get_chordal_hold_default(tap_hold_record, other_record);
    }
#endif

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

// The dead key must be sent unshifted, only the letter is capitalized
static void tap_accent_sequence(uint16_t accent_keycode, bool shifted) {
    const uint16_t dead   = accent_sequences[accent_keycode - FR_AGRV][0];
    const uint16_t letter = accent_sequences[accent_keycode - FR_AGRV][1];
    tap_code16(dead);
    tap_code16(shifted ? S(letter) : letter);
}

static bool process_accent(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        const uint8_t mods    = get_mods();
        const bool    shifted = ((mods | get_oneshot_mods()) & MOD_MASK_SHIFT) != 0 || is_caps_word_on();
        del_oneshot_mods(MOD_MASK_SHIFT);
        del_mods(MOD_MASK_SHIFT);
        tap_accent_sequence(keycode, shifted);
        set_mods(mods);
    }
    return false;
}

// Customize host Colmak layout to produce French accents by default on AltGr+letter.
// Letters not listed (e.g. é on E, ç on C) fall through to the host's AltGr+letter mapping.
static bool process_altgr_accent(uint16_t keycode, keyrecord_t *record) {
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

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();
    if ((all_mods & MOD_BIT(KC_RALT)) == 0) {
        return true;
    }
    // Caps Word never sees this key (process_caps_word runs after
    // process_record_user), so apply its shift here.
    const bool shifted = (all_mods & MOD_MASK_SHIFT) != 0 || is_caps_word_on();

    uint16_t accent;
    switch (tap_keycode) {
        // acute
        case CM_S:    accent = FR_EACU; break; // é
        // grave
        case CM_A:    accent = FR_AGRV; break; // à
        case CM_P:    accent = FR_EGRV; break; // è
        case CM_U:    accent = FR_UGRV; break; // ù
        // circumflex
        case CM_Q:    accent = FR_ACIR; break; // â
        case CM_F:    accent = FR_ECIR; break; // ê
        case CM_I:    accent = FR_ICIR; break; // î
        case CM_O:    accent = FR_OCIR; break; // ô
        case CM_L:    accent = FR_UCIR; break; // û
        // diaeresis
        case CM_W:    accent = FR_EDIA; break; // ë
        case CM_Y:    accent = FR_IDIA; break; // ï
        case CM_SCLN: accent = FR_UDIA; break; // ü
        default:
            return true;
    }

    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
    tap_accent_sequence(accent, shifted);
    set_mods(mods);

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

    // After the punctuation mod, so it sees the oneshot AltGr set by ";"
    if (!process_altgr_accent(keycode, record)) {
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
        case FR_AGRV ... FR_UDIA:
            return process_accent(keycode, record);
        default:
            break;
    }
    return true;
}

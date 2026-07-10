# Home row mods keymap

Native QMK port of a [kanata home-row-mod-advanced](https://github.com/jtroo/kanata/blob/main/cfg_samples/home-row-mod-advanced.kbd)
based config. Layers 0–3 match the default keymap (media F-row, Fn lock).

## Home row mods (GACS-variant)

| A   | S   | D     | F    | G       | H        | J    | K     | L   | ;   |
|-----|-----|-------|------|---------|----------|------|-------|-----|-----|
| GUI | Alt | Shift | Ctrl | Sym lyr | SymA lyr | Ctrl | Shift | Alt | GUI |

Plus: `C`/`,` = extra Shift, `V`/`M` = accents layer, `Space` = nav/numbers
layer, `Caps` = Caps Word toggle.

## Tap-hold behavior ([docs/tap_hold.md](../../../../../docs/tap_hold.md))

- `PERMISSIVE_HOLD` + `CHORDAL_HOLD`: holds settle on nested taps, same-hand
  chords settle as taps (replaces kanata's per-hand early-tap key lists).
  Layer-tap keys (G, H, V, M) and Space have `'*'` handedness so their layers
  work with same-hand keys.
- `FLOW_TAP_TERM 150`: holds disabled during fast typing (replaces kanata's
  "nomods" typing-streak layer).
- `SPECULATIVE_HOLD` on `D` (Shift) and `F` (Ctrl) only: modifier applies
  instantly on key down, e.g. for Shift+Click.
- `TAPPING_TERM 200` (400 on `A` to avoid accidental GUI), `QUICK_TAP_TERM 0`
  (150 on Space so tap-then-hold still auto-repeats space).

## Layers

- **Nav/numbers** (hold Space): arrows/Home/End/PgUp/PgDn + Backspace on the
  left, numpad-style digits with mod-taps on the right,
  undo/cut/copy/paste/redo on the bottom row.
- **Symbols** (hold G / hold H): F1–F12 on the left, shifted-number symbols on
  the right, `[`/`]` on tap/hold of `;`. The H variant adds Delete (Caps) and
  Escape (Space).
- **Accents** (hold V or M): French accented letters as AltGr dead key
  sequences (scancodes replayed as-is — host must use the same layout as the
  original kanata setup). Chord C+V or M+, (held ≥100 ms) for capital
  accents; quicker rolls pass through as normal taps.

## Custom French Colemak host layout

The host is assumed to run a custom French Colemak layout, so scancode
`KC_SCLN` is the letter O and `KC_P` is `;`. Character-aware features use a
Colemak-aware `is_alpha()`: Caps Word (the default handler would shift `;` and
stop on O), and the punctuation mod below.

## Punctuation mod

`,` or `;` tapped before a letter acts as a oneshot mod on it:

- `,` then letter → capital letter (oneshot Shift)
- `;` then letter → accented letter (oneshot AltGr). Grave, circumflex and
  diaeresis letters (`;a` → à, `;f` → ê, `;y` → ï, …) are sent as the dead key
  sequences from the accents layer instead of plain AltGr+letter, which the
  host maps to the wrong accent (á). Letters without an entry (é, ç, …) use
  the host's AltGr+letter mapping, which is correct for them.
- `;;`, `,;` or `;,` then letter → Shift+AltGr+letter (capital accents)
- `,,` → literal `,,`, cancelling the pending mod

The punctuation is typed immediately and backspaced when a letter follows
within `ONESHOT_TIMEOUT` (2 s); followed by anything else it stays plain
punctuation.

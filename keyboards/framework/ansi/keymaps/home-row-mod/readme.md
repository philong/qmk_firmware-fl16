# Home row mods keymap

GACS-style how-row-mods with nav/numbers and fn/symbols layers

## Home row mods (GACS-variant)

| A   | S   | D     | F    | G       | H        | J    | K     | L   | ;   |
| --- | --- | ----- | ---- | ------- | -------- | ---- | ----- | --- | --- |
| GUI | Alt | Shift | Ctrl | Sym lyr | SymA lyr | Ctrl | Shift | Alt | GUI |

Plus: `V`/`M` = AltGr, `C`/`,` = extra Shift, `Space` = nav/numbers layer, `Caps` = Caps Word
toggle.

## Tap-hold behavior

- `PERMISSIVE_HOLD` + `CHORDAL_HOLD`: holds settle on nested taps, same-hand
  chords settle as taps.
  Layer-tap keys (G, H) and Space have `'*'` handedness so their layers
  work with same-hand keys.
- `FLOW_TAP_TERM 150`: holds disabled during fast typing.
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

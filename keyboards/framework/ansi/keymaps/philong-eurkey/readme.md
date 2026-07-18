# Home row mods keymap (EurKEY host)

Variant of the [philong](../philong) keymap for a host running
[EurKEY](https://eurkey.steffen.bruentjen.eu) (`eu` layout on Linux) instead of
the custom French Colemak layout. Physical layout, layers and tap-hold tuning
are identical; only the host-layout-aware parts differ (letter detection,
accent sequences).

## Home row mods (GACS-variant)

| A   | S   | D     | F    | G       | H        | J    | K     | L   | ;   |
|-----|-----|-------|------|---------|----------|------|-------|-----|-----|
| GUI | Alt | Shift | Ctrl | Sym lyr | SymA lyr | Ctrl | Shift | Alt | GUI |

Plus: `C`/`,` = extra Shift, `V`/`M` = AltGr (accents), `Space` = nav/numbers
layer, `Caps` = Caps Word toggle.

## Tap-hold behavior ([docs/tap_hold.md](../../../../../docs/tap_hold.md))

- `PERMISSIVE_HOLD` + `CHORDAL_HOLD`: holds settle on nested taps, same-hand
  chords settle as taps. Only `Space` has `'*'` handedness so its nav/number
  holds work with both hands; G/H layer-taps and V/M AltGr mod-taps are
  symmetric, so the opposite-hand activator covers same-hand keys.
- `FLOW_TAP_TERM 100`: holds disabled during fast typing.
- `SPECULATIVE_HOLD` on `D` (Shift) and `F` (Ctrl) only: modifier applies
  instantly on key down, e.g. for Shift+Click.
- `TAPPING_TERM 200` (400 on `A` and `;` to avoid accidental GUI),
  `QUICK_TAP_TERM 0`
  (150 on Space so tap-then-hold still auto-repeats space).

## Layers

- **Nav/numbers** (hold Space): arrows/Home/End/PgUp/PgDn + Backspace on the
  left, numpad-style digits with mod-taps on the right,
  undo/cut/copy/paste/redo on the bottom row.
- **Symbols** (hold G / hold H): F1–F12 on the left, shifted-number symbols on
  the right, `[`/`]` on tap/hold of `;`. The H variant adds Delete (Caps) and
  Escape (Space).

## AltGr accents

`V` and `M` are AltGr mod-taps. AltGr+letter is intercepted so each vowel
carries its most-used French accent (`e` → é, `a` → à, `i` → î, `o` → ô,
`u` → ù); the remaining accents sit on neighbors by frequency — è (2nd most
frequent) on home-row D, then the rest around their vowel:

| Key    | E | A | I | O | U | D | R | W | Q | J | K | P |
|--------|---|---|---|---|---|---|---|---|---|---|---|---|
| Accent | é | à | î | ô | ù | è | ê | ë | â | û | ï | ü |

Letters not listed fall through to EurKEY's native AltGr mapping (`ç` on C,
`ñ` on N, `á` on X, …). Note this shadows EurKEY's native AltGr umlauts on
A/E/I/O/U; German umlauts remain available via the dead diaeresis key
(AltGr+Shift+`'`).

Accents EurKEY types directly are sent as a single AltGr chord (capital on the
AltGr+Shift level); circumflex letters use the dead key sequence AltGr+`6`
then letter. Hold Shift (home-row, `C` or `,`) together with `V`/`M` for
capital accents — plain modifier stacking.

## Punctuation mod

`,` or `;` tapped before a letter acts as a oneshot mod on it:

- `,` then letter → capital letter (oneshot Shift)
- `;` then letter → accented letter (oneshot AltGr), using the interception
  table above (`;e` → é, `;a` → à, `;d` → è, …); letters without an entry use
  EurKEY's AltGr mapping (`;c` → ç, `;n` → ñ).
- `;;`, `,;` or `;,` then letter → Shift+AltGr+letter (capital accents)
- `,,` → literal `,,`, cancelling the pending mod

The punctuation is typed immediately and backspaced when a letter follows
within `ONESHOT_TIMEOUT` (2 s); followed by anything else it stays plain
punctuation.

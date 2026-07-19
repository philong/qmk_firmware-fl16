# Home row mods keymap (Gralmak on EurKEY host)

Variant of the [philong-eurkey](../philong-eurkey) keymap that rearranges the
letters to [Gralmak](https://github.com/DreymaR/Gralmak). There is no Gralmak
host layout: the host keeps running [EurKEY](https://eurkey.steffen.bruentjen.eu)
(`eu` on Linux) and the keymap sends the rearranged scancodes.

```
b l d w q   j f o u '
n r t s g   y h a e i
z x m c v   k p , . /
```

Including Gralmak's quote/semicolon swap: `'` takes the old P position, `;`
moves to the old quote key. The game layer stays plain QWERTY.

## Home row mods (GACS-variant)

| N   | R   | T     | S    | G       | Y        | H    | A     | E   | I   |
|-----|-----|-------|------|---------|----------|------|-------|-----|-----|
| GUI | Alt | Shift | Ctrl | Sym lyr | SymA lyr | Ctrl | Shift | Alt | GUI |

Plus: `M`/`,` = extra Shift, `C`/`P` = AltGr (accents), `Space` = nav/numbers
layer, `Caps` = Caps Word toggle. Same physical positions as philong-eurkey;
only the letters they type changed.

## Tap-hold behavior ([docs/tap_hold.md](../../../../../docs/tap_hold.md))

Identical tuning to philong-eurkey: `PERMISSIVE_HOLD` + `CHORDAL_HOLD`,
`FLOW_TAP_TERM 100`, `SPECULATIVE_HOLD` on the D/F positions (Shift/Ctrl),
`TAPPING_TERM 200` (400 on the pinky GUI keys N and I), `QUICK_TAP_TERM 0`
(150 on Space). The GUI+L screen lock guard now protects the right-hand GUI
(`I`), since Gralmak puts `L` on the left hand.

## Layers

Nav/numbers (hold Space), symbols (hold G / hold Y) and Fn layers are
unchanged from philong-eurkey — they are positional, not letter-based.

## AltGr accents

Character-based and therefore identical to philong-eurkey: each vowel carries
its most-used French accent, the rest placed by frequency.

| Key    | e | a | i | o | u | d | r | w | q | j | k | p |
|--------|---|---|---|---|---|---|---|---|---|---|---|---|
| Accent | é | à | î | ô | ù | è | ê | ë | â | û | ï | ü |

`C` and `P` (Gralmak letters on the old V/M positions) are the AltGr
mod-taps. Letters not listed fall through to EurKEY's native AltGr mapping
(`ç` on C, `ñ` on N, …). Direct EurKEY chords for most accents; circumflex
via the AltGr+`6` dead key.

## Punctuation mod

Unchanged: `,` or `;` tapped before a letter acts as a oneshot mod
(`,` → Shift, `;` → AltGr accent, `;;`/`,;`/`;,` → both, `,,` → literal).
`;` now sits on the old quote key.

# qmk-firmware

## Overview

QMK External Userspace holding one keymap: a Sofle split keyboard with the
`cenk1cenk2` layout. QMK itself is not vendored; it is cloned at build time, so
there is no fork to rebase and no upstream merges. Every push builds in CI and
publishes the firmware as a release named `latest`.

## Stack & Structure

- **Firmware:** QMK, latest tagged release (not master)
- **Board:** Sofle split, 2x Pro Micro (ATmega32U4, AVR, 28 KB usable flash)
- **Bootloader:** Caterina, flashed with `avrdude` over `/dev/ttyACM*`
- **Build:** Taskfile locally, GitHub Actions in CI
- **Python:** mise + uv with `pyproject.toml`; the venv auto-activates on entering
  the directory, so `qmk` is on `PATH` without a wrapper

```
keyboards/sofle/keymaps/cenk1cenk2/   the keymap
qmk.json                              build targets
.qmk/                                 QMK tree, gitignored
dist/                                 built and downloaded firmware, gitignored
```

## Conventions

- YAML in block style. Never flow collections (`{a: 1}`, `[a, b]`).
- Conventional commits, bare types, no scope.
- OLED status labels are exactly 5 characters. See Constraints.
- Build features are toggled in `rules.mk`. Display-only toggles are `1`/`0`
  defines in `config.h`, guarded by an `#error` when they need a build feature
  that is off.

## Constraints

- **The LED chain order does not match `keyboards/sofle/info.json`.** On this
  board each side runs: index 0-5 the six rear underglow LEDs, index 6 the single
  forward-facing LED, index 7-35 per-key. The `rgb_matrix.layout` flags claim the
  forward-facing LED is index 0. Select underglow by index, never by
  `LED_FLAG_UNDERGLOW` — the flags light one forward-facing LED and leave one rear
  LED unlit, identically on both halves. The `x`/`y` coordinates in that layout are
  shifted by the same amount, so treat any spatial claim about the six rear LEDs as
  unverified.
- **A rotated OLED line holds exactly 5 glyphs.** `OLED_DISPLAY_HEIGHT` is 32px
  and the font is 6px, leaving a 2px remainder no glyph can reach. Labels are
  padded to exactly 5 characters: a shorter label gets padded by the driver with
  `invert` hardcoded to false, so a highlight bar stops short of the edge; a longer
  one wraps onto the next line and corrupts it. `fill_line_tail` drives the 2px
  remainder directly. `oled_advance_page` rounds that remainder down to zero
  glyphs, so a trailing `\n` after a 5-character string does nothing at all.
- **28 KB of flash.** Every feature is weighed against it, and measured by
  building rather than estimated.
- **A 500 mA polyfuse on the master half feeds both sides** through the TRRS. 72
  WS2812 at brightness 150 draw roughly 1.2 A theoretical; it works, so real draw
  is lower, but headroom is thin. White costs the most per LED since it drives all
  three channels.
- **`.qmk/` is a separate clean QMK tree** because `locate_keymap` searches
  `QMK_FIRMWARE` before `QMK_USERSPACE` and returns the first hit, despite its own
  comment claiming the opposite. Any QMK checkout containing a `cenk1cenk2` keymap
  shadows this repo and silently builds a hybrid of the two.
- **Each RGB Matrix flush bit-bangs 72 LEDs with interrupts masked for ~2.2 ms**
  on both halves, competing with the single-wire half-duplex split serial.
  `RGB_MATRIX_LED_FLUSH_LIMIT` is 100 ms because a static colour does not need
  more; lowering it toward the 16 ms default reintroduces that contention.

## Gotchas

- `qmk` exposes only `clone`, `config`, `console`, `env` and `setup` until
  `QMK_HOME` points at a QMK checkout. The Taskfile sets it.
- `qmk clone` refuses a non-empty destination, so `qmk:sync` removes the tree and
  re-clones when the tag moves.
- QMK publishes no GitHub releases, only tags. `git ls-remote --tags
  --sort=-v:refname` resolves the latest; the releases API returns 404 and the
  tags API returns them reverse-alphabetically.
- Flashing runs once per half, same binary both times. USB decides which half is
  master at every boot; `EE_HANDS` decides left/right from EEPROM and survives
  flashing.
- Local `avr-gcc` and the CI container produce firmware differing by roughly 200
  bytes from identical sources.
- RGB Matrix keeps its settings in its own EEPROM slot, so the `config.h` defaults
  apply only when the EEPROM is initialised. `EE_CLR` on the Adjust layer forces
  that; it does not touch `EE_HANDS` handedness, which lives outside eeconfig.
- Writing to `/dev/ttyACM*` needs the QMK udev rules, which grant access via
  `TAG+="uaccess"` rather than a group. `task udev` installs them.

## Tools & MCP Usage

- `task compile:sofle:rev1:cenk1cenk2` — build locally into `dist/`.
- `task download:sofle:rev1:cenk1cenk2` — fetch the CI build into `dist/`.
- `task flash:sofle:rev1:cenk1cenk2` — flash `dist/`; run once per half.
- `task qmk:sync` — put `.qmk` on the latest tagged release. `compile` depends on
  it, so a local build cannot use an older tree than CI.
- `task udev` — install the QMK udev rules. Guarded, so it is a no-op once done.

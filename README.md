# qmk-firmware

QMK [External Userspace](https://docs.qmk.fm/newbs_external_userspace) for my Sofle.

Holds only my own keymap. QMK itself is pulled in at build time, so there is no
fork to rebase and no upstream to merge.

## Layout

```
keyboards/sofle/keymaps/cenk1cenk2/   the keymap
qmk.json                              build targets
```

## Building

Every push builds against current `qmk/qmk_firmware` master via GitHub Actions
and publishes the firmware as a release.

To build locally instead:

```sh
task install
task compile
```

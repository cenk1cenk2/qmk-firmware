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

Every push builds against the latest tagged `qmk/qmk_firmware` release via
GitHub Actions and publishes the firmware as a release named `latest`.

To build and flash locally instead:

```sh
task install
task compile:sofle:rev1:cenk1cenk2
task flash:sofle:rev1:cenk1cenk2
```

`task download:sofle:rev1:cenk1cenk2` fetches the CI build instead of compiling.
Flashing runs once per half, resetting that half when prompted.

#include QMK_KEYBOARD_H
#include "layers.h"

// enum my_keycodes {};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
QK_GESC,            KC_1,                 KC_2,                 KC_3,               KC_4,                KC_5,                                                          KC_6,                KC_7,               KC_8,                 KC_9,               KC_0,               KC_MINS,
KC_TAB,             KC_Q,                 KC_W,                 KC_E,               KC_R,                KC_T,                                                          KC_Y,                KC_U,               KC_I,                 KC_O,               KC_P,               KC_BSPC,
KC_LCTL,            KC_A,                 KC_S,                 KC_D,               KC_F,                KC_G,                                                          KC_H,                KC_J,               KC_K,                 KC_L,               KC_SCLN,            KC_QUOT,
KC_LSFT,            KC_Z,                 KC_X,                 KC_C,               KC_V,                KC_B,                KC_MUTE,             RGB_TOG,             KC_N,                KC_M,               KC_COMM,              KC_DOT,             KC_SLSH,            KC_RSFT,
                    KC_LALT,              KC_LCTL,              KC_LGUI,            MO(_LOWER),          KC_ENT,                                                        KC_SPC,              MO(_RAISE),         KC_RALT,              KC_RCTL,            KC_RGUI
),
[_LOWER]  = LAYOUT(
KC_GRV,             KC_NO,                KC_NO,                KC_NO,              KC_NO,               KC_NO,                                                         KC_NO,               KC_NO,              KC_NO,                KC_NO,              KC_NO,              KC_NO,
KC_TRNS,            KC_EXLM,              KC_AT,                KC_HASH,            KC_DLR,              KC_PERC,                                                       KC_CIRC,             KC_AMPR,            KC_ASTR,              KC_LPRN,            KC_RPRN,            KC_TRNS,
KC_TRNS,            KC_1,                 KC_2,                 KC_3,               KC_4,                KC_5,                                                          KC_6,                KC_7,               KC_8,                 KC_9,               KC_0,               KC_DQUO,
KC_TRNS,            KC_LCBR,              KC_RCBR,              KC_UNDS,            KC_PLUS,             KC_PIPE,             KC_MPLY,             KC_TRNS,             KC_BSLS,             KC_EQL,             KC_MINS,              KC_LBRC,            KC_RBRC,            KC_TRNS,
                    KC_TRNS,              KC_TRNS,              KC_TRNS,            KC_TRNS,             KC_TRNS,                                                       KC_TRNS,             KC_TRNS,            KC_TRNS,              KC_TRNS,            KC_TRNS
),
[_RAISE]  = LAYOUT(
KC_TRNS,            KC_NO,                KC_NO,                KC_NO,              KC_NO,               KC_NO,                                                         KC_NO,               KC_NO,              KC_NO,                KC_NO,              KC_NO,               KC_NO,
KC_TRNS,            KC_F1,                KC_F2,                KC_F3,              KC_F4,               KC_NO,                                                         KC_NO,               LCTL(KC_LEFT),      KC_UP,                LCTL(KC_RIGHT),     KC_PGUP,             KC_DEL,
KC_TRNS,            KC_F5,                KC_F6,                KC_F7,              KC_F8,               KC_NO,                                                         KC_NO,               KC_LEFT,            KC_DOWN,              KC_RGHT,            KC_PGDN,             KC_ENT,
KC_TRNS,            KC_F9,                KC_F10,               KC_F11,             KC_F12,              KC_NO,               KC_TRNS,             KC_TRNS,             KC_PSCR,             KC_HOME,            KC_NO,                KC_END,             KC_NO,               KC_NO,
                    KC_TRNS,              KC_TRNS,              KC_TRNS,            KC_TRNS,             KC_TRNS,                                                       KC_TRNS,             KC_TRNS,            KC_TRNS,              KC_TRNS,            KC_TRNS
),
[_ADJUST] = LAYOUT(
QK_REBOOT,          KC_NO,                KC_NO,                KC_NO,              KC_NO,               KC_NO,                                                         KC_NO,               KC_NO,              KC_NO,                KC_NO,              KC_NO,               KC_NO,
KC_NO,              KC_INS,               KC_SCRL,              BL_TOGG,            RGB_TOG,             KC_NO,                                                         KC_BRIU,             KC_VOLD,            KC_MUTE,              KC_VOLU,            KC_NO,               KC_NO,
KC_CAPS,            RGB_HUI,              RGB_SAI,              RGB_VAI,            RGB_MOD,             CG_SWAP,                                                       KC_BRID,             KC_MPRV,            KC_MPLY,              KC_MNXT,            KC_NO,               KC_NO,
KC_NO,              RGB_HUD,              RGB_SAD,              RGB_VAD,            RGB_RMOD,            CG_NORM,             KC_TRNS,             KC_TRNS,             KC_NO,               KC_NO,              KC_NO,                KC_NO,              KC_NO,               KC_NO,
                    KC_TRNS,              KC_TRNS,              KC_TRNS,            KC_TRNS,             KC_TRNS,                                                       KC_TRNS,             KC_TRNS,            KC_TRNS,              KC_TRNS,            KC_TRNS
)
//                  |                    |                    |                    |                    |                    |                    |                    |                    |                    |                    |                    |                    |
};
// clang-format on

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(MS_WHLD);
                } else {
                    tap_code(MS_WHLU);
                }
            }
            break;
        case _RAISE:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
            }
            break;
        case _LOWER:
            if (index == 1) {
                if (clockwise) {
                    tap_code(MS_WHLR);
                } else {
                    tap_code(MS_WHLL);
                }
            }
            break;
    }

    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {}
    return true;
}

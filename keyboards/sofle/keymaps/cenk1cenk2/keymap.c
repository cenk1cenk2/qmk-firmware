#include QMK_KEYBOARD_H
#include "layers.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
QK_GESC,            KC_1,                 KC_2,                 KC_3,               KC_4,                KC_5,                                                          KC_6,                KC_7,               KC_8,                 KC_9,               KC_0,               KC_MINS,
KC_TAB,             KC_Q,                 KC_W,                 KC_E,               KC_R,                KC_T,                                                          KC_Y,                KC_U,               KC_I,                 KC_O,               KC_P,               KC_BSPC,
KC_LCTL,            KC_A,                 KC_S,                 KC_D,               KC_F,                KC_G,                                                          KC_H,                KC_J,               KC_K,                 KC_L,               KC_SCLN,            KC_QUOT,
KC_LSFT,            KC_Z,                 KC_X,                 KC_C,               KC_V,                KC_B,                KC_MUTE,             UG_TOGG,             KC_N,                KC_M,               KC_COMM,              KC_DOT,             KC_SLSH,            KC_RSFT,
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
KC_TRNS,            KC_F1,                KC_F2,                KC_F3,              KC_F4,               KC_NO,                                                         QK_LLCK,             LCTL(KC_LEFT),      KC_UP,                LCTL(KC_RIGHT),     KC_PGUP,             KC_DEL,
KC_TRNS,            KC_F5,                KC_F6,                KC_F7,              KC_F8,               KC_NO,                                                         KC_PSCR,             KC_LEFT,            KC_DOWN,              KC_RGHT,            KC_PGDN,             KC_ENT,
KC_TRNS,            KC_F9,                KC_F10,               KC_F11,             KC_F12,              KC_NO,               KC_TRNS,             KC_TRNS,             KC_NO,               KC_HOME,            KC_NO,                KC_END,             KC_NO,               KC_NO,
                    KC_TRNS,              KC_TRNS,              KC_TRNS,            KC_TRNS,             KC_TRNS,                                                       KC_TRNS,             KC_TRNS,            KC_TRNS,              KC_TRNS,            KC_TRNS
),
[_ADJUST] = LAYOUT(
EE_CLR,             KC_NO,                KC_NO,                KC_NO,              KC_NO,               KC_NO,                                                         KC_NO,               KC_NO,              KC_NO,                KC_NO,              KC_NO,               KC_NO,
KC_NO,              KC_INS,               KC_SCRL,              KC_NO,              UG_TOGG,             KC_NO,                                                         KC_BRIU,             KC_VOLD,            KC_MUTE,              KC_VOLU,            KC_NO,               KC_NO,
KC_CAPS,            UG_HUEU,              UG_SATU,              UG_VALU,            KC_MNXT,             KC_NO,                                                         KC_BRID,             KC_MPRV,            KC_MPLY,              KC_MNXT,            KC_NO,               KC_NO,
KC_NO,              UG_HUED,              UG_SATD,              UG_VALD,            KC_MPRV,             KC_NO,               KC_TRNS,             KC_TRNS,             KC_NO,               KC_NO,              KC_NO,                KC_NO,              KC_NO,               KC_NO,
                    KC_TRNS,              KC_TRNS,              KC_TRNS,            KC_TRNS,             KC_TRNS,                                                       KC_TRNS,             KC_TRNS,            KC_TRNS,              KC_TRNS,            KC_TRNS
)
//                  |                    |                    |                    |                    |                    |                    |                    |                    |                    |                    |                    |                    |
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE

// Volume left, scroll right. Holding raise turns the left knob into track
// skipping. Transparent entries fall through to the layer below.
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//                 left encoder                        right encoder
[_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),   ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
[_LOWER]  = { ENCODER_CCW_CW(_______, _______),   ENCODER_CCW_CW(_______, _______) },
[_RAISE]  = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT),   ENCODER_CCW_CW(_______, _______) },
[_ADJUST] = { ENCODER_CCW_CW(_______, _______),   ENCODER_CCW_CW(_______, _______) },
};
// clang-format on

#endif

#include QMK_KEYBOARD_H
#include "transactions.h"
#include "handler.h"
#include "layers.h"
#include "rgb.h"

void suspend_wakeup_init_user(void) {
// #ifdef RGBLIGHT_ENABLE
//     rgblight_enable();
// #endif
// #ifdef OLED_ENABLE
//     oled_on();
// #endif
//
//     if (!is_keyboard_master()) return;
//     slave_sleep_state m2s = {power : true};
//     transaction_rpc_send(USER_SYNC_SLEEP_STATE, sizeof(m2s), &m2s);
}

void suspend_power_down_user(void) {
// #ifdef RGBLIGHT_ENABLE
//     rgblight_disable_noeeprom();
// #endif
// #ifdef OLED_ENABLE
//     oled_clear();
//     oled_off();
// #endif
//
//     if (!is_keyboard_master()) return;
//     slave_sleep_state m2s = {power : false};
//     transaction_rpc_send(USER_SYNC_SLEEP_STATE, sizeof(m2s), &m2s);
}

void user_sync_sleep_state_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
//     const slave_sleep_state *m2s = (const slave_sleep_state *)in_data;
//
//     switch (m2s->power) {
//         case true:
// #ifdef RGBLIGHT_ENABLE
//             rgblight_enable_noeeprom();
// #endif
// #ifdef OLED_ENABLE
//             oled_set_brightness(255);
//             oled_on();
// #endif
//             break;
//         case false:
// #ifdef RGBLIGHT_ENABLE
//             rgblight_disable_noeeprom();
// #endif
// #ifdef OLED_ENABLE
//             oled_set_brightness(0);
//             oled_clear();
//             oled_off();
// #endif
//             break;
//     }
}

#ifdef RGBLIGHT_LAYERS

const rgblight_segment_t PROGMEM rgb_layer_default[] = RGBLIGHT_LAYER_SEGMENTS(SET_UNDERGLOW(HSV_WHITE));
const rgblight_segment_t PROGMEM rgb_layer_lower[]   = RGBLIGHT_LAYER_SEGMENTS(SET_UNDERGLOW(HSV_CYAN));
const rgblight_segment_t PROGMEM rgb_layer_raise[]   = RGBLIGHT_LAYER_SEGMENTS(SET_UNDERGLOW(HSV_GOLD));
const rgblight_segment_t PROGMEM rgb_layer_adjust[]  = RGBLIGHT_LAYER_SEGMENTS(SET_UNDERGLOW(HSV_RED));

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(rgb_layer_default, rgb_layer_lower, rgb_layer_raise, rgb_layer_adjust);

#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_LAYERS
    rgblight_layers = my_rgb_layers;
#endif

    // transaction_register_rpc(USER_SYNC_SLEEP_STATE, user_sync_sleep_state_slave_handler);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

#ifdef AUTO_SHIFT_ENABLE
    switch (get_highest_layer(state)) {
        case _QWERTY:
        case _LOWER:
            autoshift_enable();
            break;
        default:
            autoshift_disable();
            break;
    }
#endif

#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    // rgblight_enable_noeeprom();
#endif

    return state;
}

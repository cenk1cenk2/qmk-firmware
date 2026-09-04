#include QMK_KEYBOARD_H
#include "layers.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef RGB_MATRIX_ENABLE

// Per-side index 0 is the forward-facing indicator and 1-6 the rear underglow;
// 7-35 are per-key. Selecting on flags rather than index keeps this correct if
// the chain ever changes.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    hsv_t hsv;

    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            hsv = (hsv_t){HSV_CYAN};
            break;
        case _RAISE:
            hsv = (hsv_t){HSV_GOLD};
            break;
        case _ADJUST:
            hsv = (hsv_t){HSV_RED};
            break;
        default:
            hsv = (hsv_t){HSV_WHITE};
            break;
    }

    // Track the user's brightness the way RGBLIGHT_LAYERS_RETAIN_VAL did.
    hsv.v = rgb_matrix_get_val();

    const rgb_t rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (g_led_config.flags[i] & (LED_FLAG_UNDERGLOW | LED_FLAG_INDICATOR)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return false;
}

#endif

#include QMK_KEYBOARD_H
#include "layers.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef RGB_MATRIX_ENABLE

// The layer colour goes on the six rear underglow LEDs per side. Everything else
// is left to the active effect, so the forward-facing LED and the per-key LEDs
// share the base colour.
//
// This selects by index rather than by LED_FLAG_UNDERGLOW because the flags in
// keyboards/sofle/info.json do not match this board: they place the
// forward-facing LED first, while on the hardware the chain runs through the six
// rear LEDs and reaches the forward-facing one at index 6. Trusting the flags lit
// one front LED and left one rear LED unlit, on both halves.
#define LEDS_PER_SIDE (RGB_MATRIX_LED_COUNT / 2)
#define UNDERGLOW_FIRST 0
#define UNDERGLOW_LAST 5

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
        const uint8_t on_side = i % LEDS_PER_SIDE;

        if (on_side >= UNDERGLOW_FIRST && on_side <= UNDERGLOW_LAST) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return false;
}

#endif

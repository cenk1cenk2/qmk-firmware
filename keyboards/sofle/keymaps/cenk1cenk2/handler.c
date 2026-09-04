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

// Temporary: paints each rear LED a distinct hue so the physical order around
// the ring can be read off the board. Set to 1 to diagnose, 0 for normal use.
#define UNDERGLOW_PROBE 0

#if UNDERGLOW_PROBE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    static const uint8_t probe_hue[] = {
        0,   // index 0 - red
        43,  // index 1 - yellow
        85,  // index 2 - green
        128, // index 3 - cyan
        170, // index 4 - blue
        213, // index 5 - magenta
    };

    for (uint8_t i = led_min; i < led_max; i++) {
        const uint8_t on_side = i % LEDS_PER_SIDE;

        if (on_side >= UNDERGLOW_FIRST && on_side <= UNDERGLOW_LAST) {
            const hsv_t hsv = (hsv_t){probe_hue[on_side], 255, rgb_matrix_get_val()};
            const rgb_t rgb = hsv_to_rgb(hsv);

            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return false;
}

#else

// Ring position to column, counted from the outer edge: 0 outer, 1 middle,
// 2 inner. Indices 0-2 run along the top from outer to inner and 3-5 back along
// the bottom, so the far side of the ring folds onto the same three columns.
// The chain already mirrors between halves, so this holds for both.
#define UG_COLUMNS 3
#define UG_COLUMN(pos) ((pos) < UG_COLUMNS ? (pos) : (UNDERGLOW_LAST - (pos)))

// One step every 128ms, off the frame timestamp. g_rgb_timer is stamped from
// sync_timer_read32(), which the master pushes to the peripheral, so both halves
// count the same steps without anything extra on the transport. Four phases: the
// ring grows a column at a time and holds full for one before restarting.
#define UG_PHASES 4
#define UG_STEP ((uint8_t)((g_rgb_timer >> 7) % UG_PHASES))

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const uint8_t layer = get_highest_layer(layer_state);
    const uint8_t val   = rgb_matrix_get_val();
    const uint8_t step  = UG_STEP;
    const uint8_t grown = step < UG_COLUMNS ? step : UG_COLUMNS - 1;

    hsv_t hsv;

    switch (layer) {
        case _LOWER:
            hsv = (hsv_t){HSV_YELLOW};
            break;
        case _RAISE:
            // Not HSV_ORANGE (21): its green channel is half of red, and WS2812
            // green carries roughly twice the perceived weight per unit, so it
            // reads yellow-green. This sits at R150 G39 and reads orange.
            hsv = (hsv_t){11, 255, 0};
            break;
        case _ADJUST:
            hsv = (hsv_t){HSV_RED};
            break;
        default:
            hsv = (hsv_t){HSV_WHITE};
            break;
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        const uint8_t on_side = i % LEDS_PER_SIDE;

        if (on_side < UNDERGLOW_FIRST || on_side > UNDERGLOW_LAST) {
            continue;
        }

        bool lit = true;

        if (layer != _QWERTY) {
            // Grows outward from the inner edge, which is where the thumbs hold
            // the layer key. Colour alone separates the layers.
            lit = UG_COLUMN(on_side) >= (UG_COLUMNS - 1) - grown;
        }

        // Track the user's brightness the way RGBLIGHT_LAYERS_RETAIN_VAL did.
        // Ungrown columns sit at a quarter, which the CIE curve turns into a
        // faint tint rather than a second brightness level.
        hsv.v = lit ? val : val / 4;

        const rgb_t rgb = hsv_to_rgb(hsv);

        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return false;
}

#endif // UNDERGLOW_PROBE

#endif

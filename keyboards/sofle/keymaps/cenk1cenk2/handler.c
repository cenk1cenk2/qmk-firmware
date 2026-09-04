#include QMK_KEYBOARD_H
#include "layers.h"
#include "rgb.h"

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
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
#endif

    return state;
}

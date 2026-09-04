#pragma once

#define EE_HANDS

#ifndef NO_DEBUG
#    define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#    define NO_PRINT
#endif // !NO_PRINT

#define ENCODER_DIRECTION_FLIP
#undef ENCODER_RESOLUTION
#define ENCODER_RESOLUTION 1
#define SPLIT_TRANSPORT_MIRROR

#define NO_ACTION_ONESHOT

#define QUICK_TAP_TERM 0

#define FORCE_NKRO

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 60000
#    define SPLIT_OLED_ENABLE
#endif

#define WS2812_DI_PIN D3

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SPLIT
#    define SPLIT_LED_STATE_ENABLE
#    define RGBLIGHT_LED_COUNT 72 // Number of LEDs
#    define RGBLED_SPLIT \
        { 36, 36 }
#    define RGBLIGHT_DEFAULT_HUE 120
#    define RGBLIGHT_SLEEP
#    define RGB_MATRIX_SLEEP
#    define RGB_DISABLE_WHEN_USB_SUSPENDED

#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17

#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define SPLIT_LAYER_STATE_ENABLE
#endif

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

#define NO_ACTION_ONESHOT
#define LAYER_STATE_8BIT

#define QUICK_TAP_TERM 0

// The peripheral reboots itself if the master goes quiet, so reflashing one half
// does not need the other power cycled.
#define SPLIT_WATCHDOG_ENABLE

// FORCE_NKRO was removed from QMK; this sets the EEPROM default instead.
#define NKRO_DEFAULT_ON true

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 60000
#    define SPLIT_OLED_ENABLE

// Words per minute on the status screen. Needs WPM_ENABLE = yes in rules.mk.
#    define STATUS_SHOW_WPM 1
#endif

#ifdef RGB_MATRIX_ENABLE
// The indicator hook reads layer_state on the peripheral, which only arrives
// with this.
#    define SPLIT_LAYER_STATE_ENABLE

#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#    define RGB_MATRIX_DEFAULT_HUE 120
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150

#    define RGB_MATRIX_HUE_STEP 10
#    define RGB_MATRIX_SAT_STEP 17
#    define RGB_MATRIX_VAL_STEP 17

// Default is 16ms, which masks interrupts ~13% of the time on both halves and
// collides with the single-wire split serial. A static colour does not need
// that cadence.
#    define RGB_MATRIX_LED_FLUSH_LIMIT 100
#endif

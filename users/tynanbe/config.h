#pragma once

// Use custom magic number so EEPROM always gets reset when switching branches
#define EECONFIG_MAGIC_NUMBER (uint16_t)0xDAFA

// Set polling rate to 1000Hz
#define USB_POLLING_INTERVAL_MS 1



/* RGB CONFIG */

#ifdef RGBLIGHT_ENABLE
#  define RGBLIGHT_HUE_STEP 8
#  define RGBLIGHT_SAT_STEP 8
#  define RGBLIGHT_VAL_STEP 5
// #  define RGBLIGHT_LIMIT_VAL 150
#  undef RGBLIGHT_ANIMATIONS
#  define RGBLIGHT_EFFECT_BREATHING
#  define RGBLIGHT_EFFECT_KNIGHT
#  define RGBLIGHT_EFFECT_RAINBOW_MOOD
#  define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#  define RGBLIGHT_EFFECT_STATIC_GRADIENT
#  define RGBLIGHT_SLEEP
#endif // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Reacts to keypresses (will slow down matrix scan by a lot)
#  define RGB_MATRIX_KEYPRESSES
// Reacts to keyreleases (instead of keypresses)
// #  define RGB_MATRIX_KEYRELEASES
#  define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// Number of milliseconds to wait until rgb automatically turns off
// #  define RGB_DISABLE_TIMEOUT 0
// Turn off effects when suspended
#  define RGB_DISABLE_WHEN_USB_SUSPENDED true
// Limits the number of LEDs to process in an animation per task run
// (increases keyboard responsiveness)
// #  define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5
// Limits in milliseconds how frequently an animation will update the LEDs
// 16 (16ms) is equivalent to limiting to 60fps
// (increases keyboard responsiveness)
// #  define RGB_MATRIX_LED_FLUSH_LIMIT 16
// Limits maximum brightness of LEDs to 200 out of 255
// If not defined maximum brightness is set to 255
// #  define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#  define RGB_MATRIX_HUE_STEP 8
#  define RGB_MATRIX_SAT_STEP 8
#  define RGB_MATRIX_VAL_STEP 5
#  define RGB_MATRIX_SPD_STEP 10
#  define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_GRADIENT_UP_DOWN
#  define RGB_MATRIX_STARTUP_HUE 247
// #  define RGB_MATRIX_STARTUP_SAT 255
// #  define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
// #  define RGB_MATRIX_STARTUP_SPD 127
// Use an unused EEPROM index instead of sharing with RGBLIGHT
// #  define EECONFIG_RGB_MATRIX (uint32_t *)16

#  if defined(__AVR__) && !defined(__AVR_AT90USB1286__)
#    define DISABLE_RGB_MATRIX_ALPHAS_MODS
// #    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
// #    define DISABLE_RGB_MATRIX_BREATHING
#    define DISABLE_RGB_MATRIX_BAND_SAT
#    define DISABLE_RGB_MATRIX_BAND_VAL
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #    define DISABLE_RGB_MATRIX_CYCLE_ALL
#    define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #    define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
// #    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
// #    define DISABLE_RGB_MATRIX_DUAL_BEACON
#    define DISABLE_RGB_MATRIX_RAINBOW_BEACON
// #    define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define DISABLE_RGB_MATRIX_RAINDROPS
#    define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #    define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#    define DISABLE_RGB_MATRIX_DIGITAL_RAIN
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define DISABLE_RGB_MATRIX_SPLASH
// #    define DISABLE_RGB_MATRIX_MULTISPLASH
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH
// #    define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#  else
    // No need for single versions if multi performance isn't a problem
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define DISABLE_RGB_MATRIX_SPLASH
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH
#  endif // AVR
#endif // RGB_MATRIX_ENABLE



/* TAP CONFIG */

#define FORCE_NKRO

// Makes it possible to do rolling combos (zx) with keys that convert to other keys on hold, by enforcing the `TAPPING_TERM` for both keys
#define IGNORE_MOD_TAP_INTERRUPT

#ifndef ONESHOT_TAP_TOGGLE
#  define ONESHOT_TAP_TOGGLE 2
#endif // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
#  define ONESHOT_TIMEOUT 1000
#endif // !ONESHOT_TIMEOUT

// Makes tap and hold keys trigger the hold if another key is pressed before releasing, even if it hasn't hit the `TAPPING_TERM`
#undef PERMISSIVE_HOLD

// Tap anyway, even after `TAPPING_TERM`, if there was no other key interruption between press and release
// #define RETRO_TAPPING

// Sets the delay, in ms, between `register_code` and `unregister_code`, if you're having issues with it registering properly (common on VUSB boards)
#define TAP_CODE_DELAY 5

// Makes it possible to use a dual role key as modifier shortly after having been tapped
// Not compatible with ONESHOT_TAP_TOGGLE
// #define TAPPING_FORCE_HOLD

#undef TAPPING_TERM
#define TAPPING_TERM 175

/*
#ifndef TAPPING_TOGGLE
#  define TAPPING_TOGGLE 1
#endif // TAPPING_TOGGLE
*/

/*
 * Allows sending more than one key per scan. By default, only one key event
 * gets sent via `process_record()` per scan. This has little impact on most
 * typing, but if you're doing a lot of chords, or your scan rate is slow to
 * begin with, you can have some delay in processing key events. Each press and
 * release is a separate event. For a keyboard with 1ms or so scan times, even a
 * very fast typist isn't going to produce the 500 keystrokes a second needed to
 * actually get more than a few ms of delay from this. But if you're doing
 * chording on something with 3-4ms scan times? You probably want this.
 */
/*
#ifndef QMK_KEYS_PER_SCAN
#  define QMK_KEYS_PER_SCAN 4
#endif // !QMK_KEYS_PER_SCAN
*/



/* REMOVE UNUSED FEATURES */

#ifdef LOCKING_SUPPORT_ENABLE
#  undef LOCKING_SUPPORT_ENABLE
#endif // LOCKING_SUPPORT_ENABLE

#ifdef LOCKING_RESYNC_ENABLE
#  undef LOCKING_RESYNC_ENABLE
#endif // LOCKING_RESYNC_ENABLE

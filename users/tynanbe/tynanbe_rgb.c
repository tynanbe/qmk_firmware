#include "tynanbe_rgb.h"
#if defined(RGBLIGHT_ENABLE)
#  include "rgblight.h"
#elif defined(RGB_MATRIX_ENABLE)
#  include "lib/lib8tion/lib8tion.h"
#  include "rgb_matrix.h"
#endif // RGBLIGHT_ENABLE



void keyboard_post_init_rgb(void) {
#if defined(RGBLIGHT_ENABLE)
  rgblight_disable_noeeprom();
#elif defined(RGB_MATRIX_ENABLE)
  rgb_matrix_disable_noeeprom();
#endif // RGBLIGHT_ENABLE


  return;
}

layer_state_t layer_state_set_rgb(layer_state_t state) {
  return state;
}

void matrix_scan_rgb(void) {
  return;
}

bool process_record_rgb(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
#ifdef RGB_USE_NOEEPROM
    /* Do not write to EEPROM when using RGB_* keycodes */
#  if defined(RGBLIGHT_ENABLE)
    case RGB_TOG:
      if (record->event.pressed) {rgblight_toggle_noeeprom();}
      return false;
    case RGB_MODE_FORWARD:
      if (record->event.pressed) {rgblight_step_noeeprom();}
      return false;
    case RGB_MODE_REVERSE:
      if (record->event.pressed) {rgblight_step_reverse_noeeprom();}
      return false;
    case RGB_HUI:
      if (record->event.pressed) {rgblight_increase_hue_noeeprom();}
      return false;
    case RGB_HUD:
      if (record->event.pressed) {rgblight_decrease_hue_noeeprom();}
      return false;
    case RGB_SAI:
      if (record->event.pressed) {rgblight_increase_sat_noeeprom();}
      return false;
    case RGB_SAD:
      if (record->event.pressed) {rgblight_decrease_sat_noeeprom();}
      return false;
    case RGB_VAI:
      if (record->event.pressed) {rgblight_increase_val_noeeprom();}
      return false;
    case RGB_VAD:
      if (record->event.pressed) {rgblight_decrease_val_noeeprom();}
      return false;
    case RGB_SPI:
      // TODO when implemented in QMK core
    case RGB_SPD:
      // TODO when implemented in QMK core
#  elif defined(RGB_MATRIX_ENABLE)
    case RGB_TOG:
      if (record->event.pressed) {
        if (rgb_matrix_config.enable) {rgb_matrix_disable_noeeprom();}
        else {rgb_matrix_enable_noeeprom();}
      }
      return false;
    case RGB_MODE_FORWARD:
      if (record->event.pressed) {
        rgb_matrix_config.mode++;
        rgb_matrix_mode_noeeprom(
          (rgb_matrix_config.mode >= RGB_MATRIX_EFFECT_MAX)
          ? 1
          : rgb_matrix_config.mode
        );
      }
      return false;
    case RGB_MODE_REVERSE:
      if (record->event.pressed) {
        rgb_matrix_config.mode--;
        rgb_matrix_mode_noeeprom(
          (rgb_matrix_config.mode < 1)
          ? RGB_MATRIX_EFFECT_MAX - 1
          : rgb_matrix_config.mode
        );
    }
      return false;
    case RGB_HUI:
      if (record->event.pressed) {
        rgb_matrix_sethsv_noeeprom(
          rgb_matrix_config.hsv.h + RGB_MATRIX_HUE_STEP,
          rgb_matrix_config.hsv.s,
          rgb_matrix_config.hsv.v
        );
      }
      return false;
    case RGB_HUD:
      if (record->event.pressed) {
        rgb_matrix_sethsv_noeeprom(
          rgb_matrix_config.hsv.h - RGB_MATRIX_HUE_STEP,
          rgb_matrix_config.hsv.s,
          rgb_matrix_config.hsv.v
        );
      }
      return false;
    case RGB_SAI:
      if (record->event.pressed) {
        rgb_matrix_sethsv_noeeprom(
          rgb_matrix_config.hsv.h,
          qadd8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP),
          rgb_matrix_config.hsv.v
        );
      }
      return false;
    case RGB_SAD:
      if (record->event.pressed) {
        rgb_matrix_sethsv_noeeprom(
          rgb_matrix_config.hsv.h,
          qsub8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP),
          rgb_matrix_config.hsv.v
        );
      }
      return false;
    case RGB_VAI:
      if (record->event.pressed) {
        rgb_matrix_sethsv_noeeprom(
          rgb_matrix_config.hsv.h,
          rgb_matrix_config.hsv.s,
          qadd8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP)
        );
      }
      return false;
    case RGB_VAD:
      if (record->event.pressed) {
        rgb_matrix_sethsv_noeeprom(
          rgb_matrix_config.hsv.h,
          rgb_matrix_config.hsv.s,
          qsub8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP)
        );
      }
      return false;
    case RGB_SPI:
      // TODO when implemented in QMK core
    case RGB_SPD:
      // TODO when implemented in QMK core
#  endif // RGBLIGHT_ENABLE
#endif // RGB_USE_NOEEPROM
    default:
      return true;
  }
}

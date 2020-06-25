#include "tynanbe_rgb.h"
#if defined(RGBLIGHT_ENABLE)
#  include "rgblight.h"
#elif defined(RGB_MATRIX_ENABLE)
#  include "lib/lib8tion/lib8tion.h"
#  include "rgb_matrix.h"
#endif // RGBLIGHT_ENABLE

//TODO remove after QMK merges https://github.com/qmk/qmk_firmware/pull/9487
static rgb_task_states rgb_task_state    = SYNCING;
void my_eeconfig_update_rgb_matrix(void) { eeprom_update_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config)); }

void rgb_matrix_toggle_eeprom_helper(bool write_to_eeprom) {
  rgb_matrix_config.enable ^= 1;
  rgb_task_state = STARTING;
  if (write_to_eeprom) {
    //eeconfig_update_rgb_matrix();
    my_eeconfig_update_rgb_matrix();
  }
  dprintf("rgb matrix toggle [%s]: rgb_matrix_config.enable = %u\n",
    (write_to_eeprom)
      ? "EEPROM"
      : "NOEEPROM",
    rgb_matrix_config.enable
  );
}
void rgb_matrix_toggle_noeeprom(void) { rgb_matrix_toggle_eeprom_helper(false); }
//void rgb_matrix_toggle(void) { rgb_matrix_toggle_eeprom_helper(true); }

void rgb_matrix_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom) {
  if (! rgb_matrix_config.enable) {
    return;
  }
  if (mode < 1) {
    rgb_matrix_config.mode = 1;
  }
  else if (mode > RGB_MATRIX_EFFECT_MAX) {
    rgb_matrix_config.mode = RGB_MATRIX_EFFECT_MAX;
  }
  else {
    rgb_matrix_config.mode = mode;
  }
  rgb_task_state = STARTING;
  if (write_to_eeprom) {
    //eeconfig_update_rgb_matrix();
    my_eeconfig_update_rgb_matrix();
  }
  dprintf("rgb matrix mode [%s]: %u\n",
    (write_to_eeprom)
      ? "EEPROM"
      : "NOEEPROM",
    rgb_matrix_config.mode
  );
}
//void rgb_matrix_mode_noeeprom(uint8_t mode) { rgb_matrix_mode_eeprom_helper(mode, false); }
//void rgb_matrix_mode(uint8_t mode) { rgb_matrix_mode_eeprom_helper(mode, true); }

void rgb_matrix_step_helper(bool write_to_eeprom) {
  uint8_t mode = rgb_matrix_config.mode + 1;
  rgb_matrix_mode_eeprom_helper(
    (mode < RGB_MATRIX_EFFECT_MAX)
      ? mode
      : 1,
    write_to_eeprom
  );
}
void rgb_matrix_step_noeeprom(void) { rgb_matrix_step_helper(false); }
//void rgb_matrix_step(void) { rgb_matrix_step_helper(true); }

void rgb_matrix_step_reverse_helper(bool write_to_eeprom) {
  uint8_t mode = rgb_matrix_config.mode - 1;
  rgb_matrix_mode_eeprom_helper(
    (mode < 1)
      ? RGB_MATRIX_EFFECT_MAX - 1
      : mode,
    write_to_eeprom
  );
}
void rgb_matrix_step_reverse_noeeprom(void) { rgb_matrix_step_reverse_helper(false); }
//void rgb_matrix_step_reverse(void) { rgb_matrix_step_reverse_helper(true); }

void rgb_matrix_sethsv_eeprom_helper(uint16_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom) {
  if (! rgb_matrix_config.enable) {
    return;
  }
  rgb_matrix_config.hsv.h = hue;
  rgb_matrix_config.hsv.s = sat;
  rgb_matrix_config.hsv.v =
    (val > RGB_MATRIX_MAXIMUM_BRIGHTNESS)
    ? RGB_MATRIX_MAXIMUM_BRIGHTNESS
    : val;
  if (write_to_eeprom) {
    //eeconfig_update_rgb_matrix();
    my_eeconfig_update_rgb_matrix();
  }
  dprintf("rgb matrix set hsv [%s]: %u,%u,%u\n",
    (write_to_eeprom)
      ? "EEPROM"
      : "NOEEPROM",
    rgb_matrix_config.hsv.h,
    rgb_matrix_config.hsv.s,
    rgb_matrix_config.hsv.v
  );
}
//void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val) { rgb_matrix_sethsv_eeprom_helper(hue, sat, val, false); }
//void rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val) { rgb_matrix_sethsv_eeprom_helper(hue, sat, val, true); }

void rgb_matrix_increase_hue_helper(bool write_to_eeprom) {
  rgb_matrix_sethsv_eeprom_helper(
    rgb_matrix_config.hsv.h + RGB_MATRIX_HUE_STEP,
    rgb_matrix_config.hsv.s,
    rgb_matrix_config.hsv.v,
    write_to_eeprom
  );
}
void rgb_matrix_increase_hue_noeeprom(void) { rgb_matrix_increase_hue_helper(false); }
//void rgb_matrix_increase_hue(void) { rgb_matrix_increase_hue_helper(true); }

void rgb_matrix_decrease_hue_helper(bool write_to_eeprom) {
  rgb_matrix_sethsv_eeprom_helper(
    rgb_matrix_config.hsv.h - RGB_MATRIX_HUE_STEP,
    rgb_matrix_config.hsv.s,
    rgb_matrix_config.hsv.v,
    write_to_eeprom
  );
}
void rgb_matrix_decrease_hue_noeeprom(void) { rgb_matrix_decrease_hue_helper(false); }
//void rgb_matrix_decrease_hue(void) { rgb_matrix_decrease_hue_helper(true); }

void rgb_matrix_increase_sat_helper(bool write_to_eeprom) {
  rgb_matrix_sethsv_eeprom_helper(
    rgb_matrix_config.hsv.h,
    qadd8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP),
    rgb_matrix_config.hsv.v,
    write_to_eeprom
  );
}
void rgb_matrix_increase_sat_noeeprom(void) { rgb_matrix_increase_sat_helper(false); }
//void rgb_matrix_increase_sat(void) { rgb_matrix_increase_sat_helper(true); }

void rgb_matrix_decrease_sat_helper(bool write_to_eeprom) {
  rgb_matrix_sethsv_eeprom_helper(
    rgb_matrix_config.hsv.h,
    qsub8(rgb_matrix_config.hsv.s, RGB_MATRIX_SAT_STEP),
    rgb_matrix_config.hsv.v,
    write_to_eeprom
  );
}
void rgb_matrix_decrease_sat_noeeprom(void) { rgb_matrix_decrease_sat_helper(false); }
//void rgb_matrix_decrease_sat(void) { rgb_matrix_decrease_sat_helper(true); }

void rgb_matrix_increase_val_helper(bool write_to_eeprom) {
  rgb_matrix_sethsv_eeprom_helper(
    rgb_matrix_config.hsv.h,
    rgb_matrix_config.hsv.s,
    qadd8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP),
    write_to_eeprom
  );
}
void rgb_matrix_increase_val_noeeprom(void) { rgb_matrix_increase_val_helper(false); }
//void rgb_matrix_increase_val(void) { rgb_matrix_increase_val_helper(true); }

void rgb_matrix_decrease_val_helper(bool write_to_eeprom) {
  rgb_matrix_sethsv_eeprom_helper(
    rgb_matrix_config.hsv.h,
    rgb_matrix_config.hsv.s,
    qsub8(rgb_matrix_config.hsv.v, RGB_MATRIX_VAL_STEP),
    write_to_eeprom
  );
}
void rgb_matrix_decrease_val_noeeprom(void) { rgb_matrix_decrease_val_helper(false); }
//void rgb_matrix_decrease_val(void) { rgb_matrix_decrease_val_helper(true); }

void rgb_matrix_set_speed_eeprom_helper(uint8_t speed, bool write_to_eeprom) {
  rgb_matrix_config.speed = speed;
  if (write_to_eeprom) {
    //eeconfig_update_rgb_matrix();
    my_eeconfig_update_rgb_matrix();
  }
  dprintf("rgb matrix set speed [%s]: %u\n",
    (write_to_eeprom)
      ? "EEPROM"
      : "NOEEPROM",
    rgb_matrix_config.speed
  );
}
void rgb_matrix_set_speed_noeeprom(uint8_t speed) { rgb_matrix_set_speed_eeprom_helper(speed, false); }
void rgb_matrix_set_speed(uint8_t speed) { rgb_matrix_set_speed_eeprom_helper(speed, true); }

void rgb_matrix_increase_speed_helper(bool write_to_eeprom) {
  rgb_matrix_set_speed_eeprom_helper(
    qadd8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP),
    write_to_eeprom
  );
}
void rgb_matrix_increase_speed_noeeprom(void) { rgb_matrix_increase_speed_helper(false); }
//void rgb_matrix_increase_speed(void) { rgb_matrix_increase_speed_helper(true); }

void rgb_matrix_decrease_speed_helper(bool write_to_eeprom) {
  rgb_matrix_set_speed_eeprom_helper(
    qsub8(rgb_matrix_config.speed, RGB_MATRIX_SPD_STEP),
    write_to_eeprom
  );
}
void rgb_matrix_decrease_speed_noeeprom(void) { rgb_matrix_decrease_speed_helper(false); }
//void rgb_matrix_decrease_speed(void) { rgb_matrix_decrease_speed_helper(true); }
//TODO /remove

void keyboard_post_init_rgb(void) {
#if defined(RGBLIGHT_ENABLE)
  //TODO set mode, hsv, speed
  rgblight_disable_noeeprom();
#elif defined(RGB_MATRIX_ENABLE)
  rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
  rgb_matrix_sethsv_noeeprom(RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL);
  rgb_matrix_set_speed_noeeprom(RGB_MATRIX_STARTUP_SPD);
  rgb_matrix_disable_noeeprom();
#endif // RGB_ENABLE
  return;
}

layer_state_t layer_state_set_rgb(layer_state_t state) {
  return state;
}

void matrix_scan_rgb(void) {
  return;
}

typedef void (*rgb_func_pointer)(void);

/**
 * Wrapper for inc/dec rgb keycode
 *
 * noinline to optimise for firmware size not speed (not in hot path)
 */
static void __attribute__((noinline)) handleKeycodeRGB(const uint8_t is_shifted, const rgb_func_pointer inc_func, const rgb_func_pointer dec_func) {
  if (is_shifted) {
    dec_func();
  } else {
    inc_func();
  }
}

bool process_record_rgb(const uint16_t keycode, const keyrecord_t *record) {
#ifndef SPLIT_KEYBOARD
  if (record->event.pressed) {
#else
  // Split keyboards need to trigger on key-up for edge-case issue
  if (!record->event.pressed) {
#endif
    uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
#ifdef RGB_USE_NOEEPROM
    /* Do not write to EEPROM when using RGB_* keycodes */
    switch (keycode) {
      case RGB_TOG:
        rgblight_toggle_noeeprom();
        return false;
      case RGB_MODE_FORWARD:
        handleKeycodeRGB(shifted, rgblight_step_noeeprom, rgblight_step_reverse_noeeprom);
        return false;
      case RGB_MODE_REVERSE:
        handleKeycodeRGB(shifted, rgblight_step_reverse_noeeprom, rgblight_step_noeeprom);
        return false;
      case RGB_HUI:
        handleKeycodeRGB(shifted, rgblight_increase_hue_noeeprom, rgblight_decrease_hue_noeeprom);
        return false;
      case RGB_HUD:
        handleKeycodeRGB(shifted, rgblight_decrease_hue_noeeprom, rgblight_increase_hue_noeeprom);
        return false;
      case RGB_SAI:
        handleKeycodeRGB(shifted, rgblight_increase_sat_noeeprom, rgblight_decrease_sat_noeeprom);
        return false;
      case RGB_SAD:
        handleKeycodeRGB(shifted, rgblight_decrease_sat_noeeprom, rgblight_increase_sat_noeeprom);
        return false;
      case RGB_VAI:
        handleKeycodeRGB(shifted, rgblight_increase_val_noeeprom, rgblight_decrease_val_noeeprom);
        return false;
      case RGB_VAD:
        handleKeycodeRGB(shifted, rgblight_decrease_val_noeeprom, rgblight_increase_val_noeeprom);
        return false;
      case RGB_SPI:
        handleKeycodeRGB(shifted, rgblight_increase_speed_noeeprom, rgblight_decrease_speed_noeeprom);
        return false;
      case RGB_SPD:
        handleKeycodeRGB(shifted, rgblight_decrease_speed_noeeprom, rgblight_increase_speed_noeeprom);
        return false;
    }
#endif // RGB_USE_NOEEPROM
  }
  return true;
}

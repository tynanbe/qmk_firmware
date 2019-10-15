#include "tynanbe_process_record.h"
#include "tynanbe.h"
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#  include "tynanbe_rgb.h"
#endif // RGB_ENABLE



__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, print matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
#  if defined(REVERSE_ROW_COL)
  xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.row, record->event.key.col, record->event.pressed);
#  else
  xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#  endif
#endif // KEYLOGGER_ENABLE

  switch (keycode) {
    case DF_MODE_FORWARD:
    case DF_MODE_REVERSE:
      process_record_df_mode(keycode, record);
      break;
    case SKC_BULLET_ELLIPSIS:
      process_record_skc(A(KC_8), A(KC_SCLN), record);
      break;
    case SKC_NDASH_MDASH:
      process_record_skc(A(KC_MINS), S(A(KC_MINS)), record);
      break;
    default:
      break;
  }

  return process_record_keymap(keycode, record) &&
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
         process_record_rgb(keycode, record) &&
#endif // RGB_ENABLE
         true;
}



/* Cycle through default layers on tap (in reverse direction on Shift + tap).
 */
bool process_record_df_mode(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }

  uint8_t layer_default = biton32(default_layer_state);
  uint8_t layer_next = (layer_default < LAYERS_BASIC_MAX)
                       ? layer_default + 1
                       : LAYERS_BASIC;
  uint8_t layer_prev = (layer_default > LAYERS_BASIC
                       && layer_default <= LAYERS_BASIC_MAX)
                       ? layer_default - 1
                       : LAYERS_BASIC_MAX;

  return (keycode == DF_MODE_FORWARD)
         ? process_record_skc(DF(layer_next), DF(layer_prev), record)
         : process_record_skc(DF(layer_prev), DF(layer_next), record);
}

/* Send any keycode `kc_0` on tap, and any other keycode `kc_1` on Shift + tap.
 */
bool process_record_skc(uint16_t kc_0, uint16_t kc_1, keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }

  uint8_t held_mods = mod_config(get_mods());
  uint8_t osm_mods = mod_config(get_oneshot_mods());

  del_mods(held_mods);
  clear_oneshot_mods();

  if ((held_mods | osm_mods) & MOD_MASK_SHIFT) {
    tap_code16(kc_1);
  }
  else {
    tap_code16(kc_0);
  }

  add_mods(held_mods);

  return true;
}

/* Send a standard ANSI string, applying held or one-shot shift as expected.
 */
bool process_record_ss(char str[], keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }

  uint8_t held_mods = mod_config(get_mods());
  uint8_t osm_mods = mod_config(get_oneshot_mods());

  del_mods(held_mods);
  clear_oneshot_mods();

  if (held_mods & MOD_MASK_SHIFT) {
    add_mods(MOD_MASK_SHIFT);
  }
  if (osm_mods & MOD_MASK_SHIFT) {
    set_oneshot_mods(MOD_MASK_SHIFT);
  }

  send_string(str);

  add_mods(held_mods);

  return true;
}


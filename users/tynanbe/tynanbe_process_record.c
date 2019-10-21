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

  bool handoff = true;

  /* Use normal Numeral LAYOUT with some default layer(s)
   */
  if (keycode >> 8 == LT(_NUM, KC_NO) >> 8) {
    switch (biton32(default_layer_state)) {
      case _QWERTY: {
        action_t action;
        action.code = ACTION_LAYER_TAP_KEY(_NUM_N & 0xF, keycode & 0xFF);
        process_action(record, action);
        handoff = false;
        break;
      }
      default:
        break;
    }
  }
  else if (keycode == TG(_NUM)) {
    switch (biton32(default_layer_state)) {
      case _QWERTY: {
        action_t action;
        action.code = ACTION_LAYER_TOGGLE(_NUM_N & 0xFF);
        process_action(record, action);
        handoff = false;
        break;
      }
      default:
        break;
    }
  }

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
         handoff;
}



/* Cycle through default layers on tap (in reverse direction on Shift + tap).
 */
bool process_record_df_mode(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }

  uint8_t mods_held = mod_config(get_mods());
  uint8_t mods_osm = mod_config(get_oneshot_mods());

  del_mods(mods_held);
  clear_oneshot_mods();

  if ((mods_held | mods_osm) & MOD_MASK_SHIFT) {
    keycode = (keycode == DF_MODE_FORWARD)
              ? DF_MODE_REVERSE
              : DF_MODE_FORWARD;
  }

  uint8_t default_layer = biton32(default_layer_state);
  if (keycode == DF_MODE_FORWARD) {
    default_layer = (default_layer < LAYERS_BASIC_MAX)
                    ? default_layer + 1
                    : LAYERS_BASIC;
  }
  else {
    default_layer = (default_layer > LAYERS_BASIC
                    && default_layer <= LAYERS_BASIC_MAX)
                    ? default_layer - 1
                    : LAYERS_BASIC_MAX;
  }

  default_layer_set(1UL << default_layer);

  add_mods(mods_held);

  return true;
}

/* Send any keycode `kc_0` on tap, and any other keycode `kc_1` on Shift + tap.
 */
bool process_record_skc(uint16_t kc_0, uint16_t kc_1, keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }

  uint8_t mods_held = mod_config(get_mods());
  uint8_t mods_osm = mod_config(get_oneshot_mods());

  del_mods(mods_held);
  clear_oneshot_mods();

  if ((mods_held | mods_osm) & MOD_MASK_SHIFT) {
    tap_code16(kc_1);
  }
  else {
    tap_code16(kc_0);
  }

  add_mods(mods_held);

  return true;
}

/* Send a standard ANSI string, applying held or one-shot shift as expected.
 */
bool process_record_ss(char str[], keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }

  uint8_t mods_held = mod_config(get_mods());
  uint8_t mods_osm = mod_config(get_oneshot_mods());

  del_mods(mods_held);
  clear_oneshot_mods();

  if (mods_held & MOD_MASK_SHIFT) {
    add_mods(MOD_MASK_SHIFT);
  }
  if (mods_osm & MOD_MASK_SHIFT) {
    set_oneshot_mods(MOD_MASK_SHIFT);
  }

  send_string(str);

  del_mods(MOD_MASK_SHIFT);
  clear_oneshot_mods();

  add_mods(mods_held);

  return true;
}


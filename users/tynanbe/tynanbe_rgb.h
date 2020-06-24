#pragma once

#include "quantum.h"

void          keyboard_post_init_rgb(void);
layer_state_t layer_state_set_rgb(layer_state_t state);
void          matrix_scan_rgb(void);
bool          process_record_rgb(const uint16_t keycode, const keyrecord_t *record);

//TODO remove after QMK merges https://github.com/qmk/qmk_firmware/pull/9487
void rgb_matrix_toggle_eeprom_helper(bool write_to_eeprom);
void rgb_matrix_toggle_noeeprom(void);
void rgb_matrix_mode_eeprom_helper(uint8_t mode, bool write_to_eeprom);
void rgb_matrix_step_noeeprom(void);
void rgb_matrix_step_reverse_noeeprom(void);
void rgb_matrix_sethsv_eeprom_helper(uint16_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom);
void rgb_matrix_increase_hue_noeeprom(void);
void rgb_matrix_decrease_hue_noeeprom(void);
void rgb_matrix_increase_sat_noeeprom(void);
void rgb_matrix_decrease_sat_noeeprom(void);
void rgb_matrix_increase_val_noeeprom(void);
void rgb_matrix_decrease_val_noeeprom(void);
void rgb_matrix_set_speed_eeprom_helper(uint8_t speed, bool write_to_eeprom);
void rgb_matrix_set_speed(uint8_t speed);
void rgb_matrix_set_speed_noeeprom(uint8_t speed);
void rgb_matrix_increase_speed_noeeprom(void);
void rgb_matrix_decrease_speed_noeeprom(void);

#ifndef RGBLIGHT_ENABLE
#  define rgblight_toggle_noeeprom rgb_matrix_toggle_noeeprom
#  define rgblight_step_noeeprom rgb_matrix_step_noeeprom
#  define rgblight_step_reverse_noeeprom rgb_matrix_step_reverse_noeeprom
#  define rgblight_increase_hue_noeeprom rgb_matrix_increase_hue_noeeprom
#  define rgblight_decrease_hue_noeeprom rgb_matrix_decrease_hue_noeeprom
#  define rgblight_increase_sat_noeeprom rgb_matrix_increase_sat_noeeprom
#  define rgblight_decrease_sat_noeeprom rgb_matrix_decrease_sat_noeeprom
#  define rgblight_increase_val_noeeprom rgb_matrix_increase_val_noeeprom
#  define rgblight_decrease_val_noeeprom rgb_matrix_decrease_val_noeeprom
#  define rgblight_set_speed rgb_matrix_set_speed
#  define rgblight_set_speed_noeeprom rgb_matrix_set_speed_noeeprom
#  define rgblight_increase_speed_noeeprom rgb_matrix_increase_speed_noeeprom
#  define rgblight_decrease_speed_noeeprom rgb_matrix_decrease_speed_noeeprom
#endif // RGBLIGHT_ENABLE
//TODO /remove

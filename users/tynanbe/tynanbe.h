/* Copyright 2019 Tynan Beatty <contact@tynan.be>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include "eeprom.h"
#include "tynanbe_keymap.h"
#include "tynanbe_process_record.h"
#ifdef TAP_DANCE_ENABLE
#  include "tynanbe_tap_dance.h"
#endif // TAP_DANCE_ENABLE
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#  include "tynanbe_rgb.h"
#endif // RGB_ENABLE



enum layers_user {
  LAYERS_BASIC = 0,
  _CMK_DHM = LAYERS_BASIC,
  _QWERTY,
  _DVORAK,
  _CMK,
  LAYERS_BASIC_MAX = _CMK,
  LAYERS_ADVANCED,
  _SYS = LAYERS_ADVANCED,
  _NAV,
  _NUM,
  _NUM_E = _NUM,
  _NUM_N,
  _SYM,
  LAYERS_ADVANCED_MAX = _SYM,
  LAYERS_MAX = LAYERS_ADVANCED_MAX,
  LAYERS_SAFE_RANGE_KEYMAP
};



void          eeconfig_init_keymap(void);
void          keyboard_post_init_keymap(void);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
layer_state_t layer_state_set_keymap(layer_state_t state);
void          led_set_keymap(uint8_t usb_led);
void          matrix_init_keymap(void);
void          matrix_scan_keymap(void);
void          shutdown_keymap(void);
void          startup_keymap(void);
void          suspend_power_down_keymap(void);
void          suspend_wakeup_init_keymap(void);

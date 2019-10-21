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

#include "tynanbe.h"



/* Replace the following `*_user()` functions with otherwise identical
 * `*_keymap()` functions in individual `keymap.c` files to support an
 * additional level of customization in the userspace scope.
 */

__attribute__((weak))
void eeconfig_init_keymap(void) {}

__attribute__((weak))
void keyboard_post_init_keymap(void) {}

__attribute__((weak))
layer_state_t default_layer_state_set_keymap(layer_state_t state) {
  return state;
}

__attribute__((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
  return state;
}

__attribute__((weak))
void led_set_keymap(uint8_t usb_led) {}

__attribute__((weak))
void matrix_init_keymap(void) {}

__attribute__((weak))
void matrix_scan_keymap(void) {}

__attribute__((weak))
void shutdown_keymap(void) {}

__attribute__ ((weak))
void startup_keymap(void) {}

__attribute__((weak))
void suspend_power_down_keymap(void) {}

__attribute__((weak))
void suspend_wakeup_init_keymap(void) {}



void eeconfig_init_user(void) {
  // Reset user EEPROM value to blank, rather than to a set value
  eeconfig_update_user(0);
  eeconfig_init_keymap();
  // keyboard_init();
}

void keyboard_post_init_user(void) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  keyboard_post_init_rgb();
#endif // RGB_ENABLE
  keyboard_post_init_keymap();
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  return default_layer_state_set_keymap(state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  state = layer_state_set_rgb(state);
#endif // RGB_ENABLE

  return layer_state_set_keymap(state);
}

void led_set_user(uint8_t usb_led) {
  led_set_keymap(usb_led);
}

void matrix_init_user(void) {
#ifdef BOOTLOADER_CATERINA
  DDRD &= ~(1 << 5);
  PORTD &= ~(1 << 5);

  DDRB &= ~(1 << 0);
  PORTB &= ~(1 << 0);
#endif // BOOTLOADER_CATERINA
  matrix_init_keymap();
}

void matrix_scan_user(void) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
  matrix_scan_rgb();
#endif // RGB_ENABLE
  matrix_scan_keymap();
}

void shutdown_user(void) {
  shutdown_keymap();
}

void startup_user(void) {
  startup_keymap();
}

void suspend_power_down_user(void) {
  suspend_power_down_keymap();
}

void suspend_wakeup_init_user(void) {
  suspend_wakeup_init_keymap();
}



// Same as default but doesn't reset EEPROM
void bootmagic_lite(void) {
  matrix_scan();
#if defined(DEBOUNCING_DELAY) && DEBOUNCING_DELAY > 0
  wait_ms(DEBOUNCING_DELAY * 2);
#elif defined(DEBOUNCE) && DEBOUNCE > 0
  wait_ms(DEBOUNCE * 2);
#else
  wait_ms(30);
#endif
  matrix_scan();
  if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
    bootloader_jump();
  }
}

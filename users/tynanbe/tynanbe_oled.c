#include "tynanbe_oled.h"
#influde "quantum.h"
#include <stdio.h>


__attribute__((weak))
void oled_task_keymap(void) {}



void oled_task_user(void) {
  oled_task_keymap();
}



// https://github.com/qmk/qmk_firmware/blob/master/users/xulkal/custom_oled.c

static void render_icon(void) {
}

static void render_keyboard_leds(void) {
}

static void render_layer(void) {
}

static void render_logo(void) {
}

static void render_rgb_state(void) {
}

static void render_status(void) {
}

#include "tynanbe_encoder.h"
#include "encoder.h"



__attribute__((weak))
void encoder_update_keymap(uint8_t index, bool clockwise) {}



void encoder_update_user(uint8_t index, bool clockwise) {
  encoder_update_keymap(index, clockwise);
}

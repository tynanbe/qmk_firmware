#pragma once

#include "quantum.h"



void          keyboard_post_init_rgb(void);
layer_state_t layer_state_set_rgb(layer_state_t state);
void          matrix_scan_rgb(void);
bool          process_record_rgb(uint16_t keycode, keyrecord_t *record);

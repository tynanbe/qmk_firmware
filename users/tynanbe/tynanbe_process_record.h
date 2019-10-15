#pragma once

#include "quantum.h"



enum keycodes_user {
  DF_MODE_FORWARD = SAFE_RANGE,
  DF_MODE_REVERSE,
  SKC_BULLET_ELLIPSIS,
  SKC_NDASH_MDASH,
  SAFE_RANGE_KEYMAP
};



bool process_record_keymap(uint16_t keycode, keyrecord_t *record);



bool process_record_df_mode(uint16_t keycode, keyrecord_t *record);
bool process_record_skc(uint16_t kc_0, uint16_t kc_1, keyrecord_t *record);
bool process_record_ss(char str[], keyrecord_t *record);



// clang-format off

#define DF_MOD    DF_MODE_FORWARD
#define DF_RMOD   DF_MODE_REVERSE
#define MG_NKRO   MAGIC_TOGGLE_NKRO
#define SKC_BU_EL SKC_BULLET_ELLIPSIS
#define SKC_ND_MD SKC_NDASH_MDASH

// clang-format on

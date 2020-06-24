#include QMK_KEYBOARD_H
#include "tynanbe.h"
#ifdef PROTOCOL_LUFA
#  include "lufa.h"
#  include "split_util.h"
#endif



enum keycodes_keymap {
  SS_SOL = SAFE_RANGE_KEYMAP,
  SS_MERCUR,
  SS_VENUS,
  SS_EARTH,
  SS_MARS,
  SS_JUPITE,
  SS_SATURN,
  SS_URANUS,
  SS_NEPTUN,
  SS_PLUTO,
};



bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SS_SOL:
      return process_record_ss("Sol", record);
    case SS_MERCUR:
      return process_record_ss("Mercury", record);
    case SS_VENUS:
      return process_record_ss("Venus", record);
    case SS_EARTH:
      return process_record_ss("Earth", record);
    case SS_MARS:
      return process_record_ss("Mars", record);
    case SS_JUPITE:
      return process_record_ss("Jupiter", record);
    case SS_SATURN:
      return process_record_ss("Saturn", record);
    case SS_URANUS:
      return process_record_ss("Uranus", record);
    case SS_NEPTUN:
      return process_record_ss("Neptune", record);
    case SS_PLUTO:
      return process_record_ss("Pluto", record);
    default:
      return true;
  }
}



// clang-format off

#define LAYOUT_COMMON(                                                         \
    K00, K01, K02, K03, K04,      K05, K06, K07, K08, K09,                     \
    K10, K11, K12, K13, K14,      K15, K16, K17, K18, K19,                     \
    K20, K21, K22, K23, K24,      K25, K26, K27, K28, K29,                     \
              K30, K31, K32,      K33, K34, K35                                \
  )                                                                            \
  LAYOUT_UNFOLD(                                                               \
    ___, ___, ___, ___, ___, ___, ___,      ___, ___, ___, ___, ___, ___, ___, \
    ___, K00, K01, K02, K03, K04, ___,      ___, K05, K06, K07, K08, K09, ___, \
    ___, K10, K11, K12, K13, K14, ___,      ___, K15, K16, K17, K18, K19, ___, \
    ___, K20, K21, K22, K23, K24, ___,      ___, K25, K26, K27, K28, K29, ___, \
    ___, ___, ___, ___, K30, K31, K32,      K33, K34, K35, ___, ___, ___, ___, \
                             K31, K32,      K33, K34                           \
  )
#define LAYOUT_COMMON_UNFOLD(...) LAYOUT_COMMON(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CMK_DHM] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_COLEMAK_DHM
  ),
  [_QWERTY] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_QWERTY
  ),
  [_DVORAK] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_DVORAK
  ),
  [_CMK] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_COLEMAK
  ),
  [_SYS] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_SYSTEM
  ),
  [_NAV] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_NAVIGATION
  ),
  [_NUM_E] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_NUMERAL_ERGO
  ),
  [_NUM_N] = LAYOUT_COMMON_UNFOLD(
    LAYOUT_COMMON_NUMERAL
  ),
  [_SYM] = LAYOUT_UNFOLD(
      _______,    SS_SOL, SS_MERCUR,  SS_VENUS,  SS_EARTH,   SS_MARS,   _______,
      _______, SS_JUPITE, SS_SATURN, SS_URANUS, SS_NEPTUN,  SS_PLUTO,   _______,
      _______, SYMBOL_L1____________________________________________,   _______,
      _______, SYMBOL_R1____________________________________________,   _______,
      _______, SYMBOL_L2_MODS_______________________________________,   _______,
      _______, SYMBOL_R2_MODS_______________________________________,   _______,
      _______, SYMBOL_L3____________________________________________,   _______,
      _______, SYMBOL_R3____________________________________________,   _______,
      _______, _______________________________, SYMBOL_L4______________________,
    SYMBOL_R4______________________, _______________________________,   _______,
                                                           SKC_ND_MD, OSL(_SYM),
    OSL(_SYM), SKC_BU_EL
  ),
};

// clang-format on

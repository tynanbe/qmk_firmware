#pragma once

#include "quantum.h"



// clang-format off

#if (!defined(LAYOUT) && defined(KEYMAP))
#  define LAYOUT KEYMAP
#endif

/* Replace `LAYOUT()` with `LAYOUT_UNFOLD()` in `keymap.c` when using any of the
 * row abstractions below, to ensure that QMK macros will receive the expected
 * number of arguments.
 */
#define LAYOUT_UNFOLD(...) LAYOUT(__VA_ARGS__)



/* Maintain standard 5-key, half-row macros, below these utility macros and
 * automatically apply `MT()` or `TD()` modifiers with
 * the `MODS_L()` and `MODS_R()` utility macros.
 */

#define IS_BASIC(kc) ((uint16_t)(kc) >= (uint16_t)QK_BASIC \
                     && (uint16_t)(kc) <= (uint16_t)QK_BASIC_MAX)

#define MT_OR_TD(mod, kc)                     \
        (((kc) == _______ || (kc) == XXXXXXX) \
        ? (kc)                                \
        : (IS_BASIC(kc))                      \
          ? MT((MOD_ ## mod), (kc))           \
          : TD(kc))

#define MOD_KEYS_L(kc_0, kc_1, kc_2, kc_3, kc_4) \
        MT_OR_TD(LSFT, (kc_0)),                  \
        MT_OR_TD(LCTL, (kc_1)),                  \
        MT_OR_TD(LALT, (kc_2)),                  \
        MT_OR_TD(LGUI, (kc_3)),                  \
        (kc_4)
#define MODS_L(row) MOD_KEYS_L(row)

#define MOD_KEYS_R(kc_4, kc_3, kc_2, kc_1, kc_0) \
        (kc_4),                                  \
        MT_OR_TD(LGUI, (kc_3)),                  \
        MT_OR_TD(LALT, (kc_2)),                  \
        MT_OR_TD(LCTL, (kc_1)),                  \
        MT_OR_TD(LSFT, (kc_0))
#define MODS_R(row) MOD_KEYS_R(row)



#define _____________________________________________________ \
          _______,   _______,   _______,   _______,   _______

#define _______________________________ \
          _______,   _______,   _______

#define ___ _______



#define FUNC_ERGO_L__________________________________________ \
            KC_F7,     KC_F5,     KC_F3,     KC_F1,     KC_F9
#define NUMROW_ERGO_L________________________________________ \
             KC_7,      KC_5,      KC_3,      KC_1,      KC_9
#define NUMROW_ERGO_L_MODS___________________________________ \
 MODS_L(NUMROW_ERGO_L________________________________________)

#define FUNC_ERGO_R__________________________________________ \
            KC_F8,    KC_F10,     KC_F2,     KC_F4,     KC_F6
#define NUMROW_ERGO_R________________________________________ \
             KC_8,      KC_0,      KC_2,      KC_4,      KC_6
#define NUMROW_ERGO_R_MODS___________________________________ \
 MODS_R(NUMROW_ERGO_R________________________________________)



#define FUNC_L_______________________________________________ \
            KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5
#define NUMROW_L_____________________________________________ \
             KC_1,      KC_2,      KC_3,      KC_4,      KC_5
#define NUMROW_L_MODS________________________________________ \
 MODS_L(NUMROW_L_____________________________________________)

#define FUNC_R_______________________________________________ \
            KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10
#define NUMROW_R_____________________________________________ \
             KC_6,      KC_7,      KC_8,      KC_9,      KC_0
#define NUMROW_R_MODS________________________________________ \
 MODS_R(NUMROW_R_____________________________________________)



#define THUMB_ERGO_L___________________ \
        OSM(MOD_LSFT),                  \
        LT(_NAV, KC_BSPC),              \
        OSL(_SYM)

#define THUMB_ERGO_R___________________ \
        OSL(_SYM),                      \
        LT(_NUM, KC_SPC),               \
        OSM(MOD_LSFT)



#define COLEMAK_DHM_L1_______________________________________ \
             KC_Q,      KC_W,      KC_F,      KC_P,      KC_B
#define COLEMAK_DHM_L2_______________________________________ \
             KC_A,      KC_R,      KC_S,      KC_T,      KC_G
#define COLEMAK_DHM_L3_______________________________________ \
             KC_Z,      KC_X,      KC_C,      KC_D,      KC_V
#define COLEMAK_DHM_L2_MODS__________________________________ \
 MODS_L(COLEMAK_DHM_L2_______________________________________)

#define COLEMAK_DHM_R1_______________________________________ \
             KC_J,      KC_L,      KC_U,      KC_Y,   KC_QUOT
#define COLEMAK_DHM_R2_______________________________________ \
             KC_M,      KC_N,      KC_E,      KC_I,      KC_O
#define COLEMAK_DHM_R3_______________________________________ \
             KC_K,      KC_H,   KC_COMM,    KC_DOT,   KC_SCLN
#define COLEMAK_DHM_R2_MODS__________________________________ \
 MODS_R(COLEMAK_DHM_R2_______________________________________)

#define LAYOUT_COMMON_COLEMAK_DHM                              \
        COLEMAK_DHM_L1_______________________________________, \
        COLEMAK_DHM_R1_______________________________________, \
        COLEMAK_DHM_L2_MODS__________________________________, \
        COLEMAK_DHM_R2_MODS__________________________________, \
        COLEMAK_DHM_L3_______________________________________, \
        COLEMAK_DHM_R3_______________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________



#define QWERTY_L1____________________________________________ \
             KC_Q,      KC_W,      KC_E,      KC_R,      KC_T
#define QWERTY_L2____________________________________________ \
             KC_A,      KC_S,      KC_D,      KC_F,      KC_G
#define QWERTY_L3____________________________________________ \
             KC_Z,      KC_X,      KC_C,      KC_V,      KC_B
#define QWERTY_L2_MODS_______________________________________ \
 MODS_L(QWERTY_L2____________________________________________)

#define QWERTY_R1____________________________________________ \
             KC_Y,      KC_U,      KC_I,      KC_O,      KC_P
#define QWERTY_R2____________________________________________ \
             KC_H,      KC_J,      KC_K,      KC_L,   KC_QUOT
#define QWERTY_R3____________________________________________ \
             KC_N,      KC_M,   KC_COMM,    KC_DOT,   KC_SCLN
#define QWERTY_R2_MODS_______________________________________ \
 MODS_R(QWERTY_R2____________________________________________)

#define LAYOUT_COMMON_QWERTY                                   \
        QWERTY_L1____________________________________________, \
        QWERTY_R1____________________________________________, \
        QWERTY_L2_MODS_______________________________________, \
        QWERTY_R2_MODS_______________________________________, \
        QWERTY_L3____________________________________________, \
        QWERTY_R3____________________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________



#define DVORAK_L1____________________________________________ \
          KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y
#define DVORAK_L2____________________________________________ \
             KC_A,      KC_O,      KC_E,      KC_U,      KC_I
#define DVORAK_L3____________________________________________ \
          KC_SCLN,      KC_Q,      KC_J,      KC_K,      KC_X
#define DVORAK_L2_MODS_______________________________________ \
 MODS_L(DVORAK_L2____________________________________________)

#define DVORAK_R1____________________________________________ \
             KC_F,      KC_G,      KC_C,      KC_R,      KC_L
#define DVORAK_R2____________________________________________ \
             KC_D,      KC_H,      KC_T,      KC_N,      KC_S
#define DVORAK_R3____________________________________________ \
             KC_B,      KC_M,      KC_W,      KC_V,      KC_Z
#define DVORAK_R2_MODS_______________________________________ \
 MODS_R(DVORAK_R2____________________________________________)

#define LAYOUT_COMMON_DVORAK                                   \
        DVORAK_L1____________________________________________, \
        DVORAK_R1____________________________________________, \
        DVORAK_L2_MODS_______________________________________, \
        DVORAK_R2_MODS_______________________________________, \
        DVORAK_L3____________________________________________, \
        DVORAK_R3____________________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________



#define COLEMAK_L1___________________________________________ \
             KC_Q,      KC_W,      KC_F,      KC_P,      KC_G
#define COLEMAK_L2___________________________________________ \
             KC_A,      KC_R,      KC_S,      KC_T,      KC_D
#define COLEMAK_L3___________________________________________ \
             KC_Z,      KC_X,      KC_C,      KC_V,      KC_B
#define COLEMAK_L2_MODS______________________________________ \
 MODS_L(COLEMAK_L2___________________________________________)

#define COLEMAK_R1___________________________________________ \
             KC_J,      KC_L,      KC_U,      KC_Y,   KC_QUOT
#define COLEMAK_R2___________________________________________ \
             KC_H,      KC_N,      KC_E,      KC_I,      KC_O
#define COLEMAK_R3___________________________________________ \
             KC_K,      KC_M,   KC_COMM,    KC_DOT,   KC_SCLN
#define COLEMAK_R2_MODS______________________________________ \
 MODS_R(COLEMAK_R2___________________________________________)

#define LAYOUT_COMMON_COLEMAK                                  \
        COLEMAK_L1___________________________________________, \
        COLEMAK_R1___________________________________________, \
        COLEMAK_L2_MODS______________________________________, \
        COLEMAK_R2_MODS______________________________________, \
        COLEMAK_L3___________________________________________, \
        COLEMAK_R3___________________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________



#define SYSTEM_L1____________________________________________ \
            RESET,     DEBUG,   MG_NKRO,    DF_MOD,   RGB_TOG
#define SYSTEM_L2____________________________________________ \
          KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,   _______
#define SYSTEM_L3____________________________________________ \
          _______,   _______,   _______,  TG(_NAV),   _______
#define SYSTEM_L4______________________                       \
        _______________________________

#define SYSTEM_R1____________________________________________ \
          RGB_MOD,   RGB_HUD,   KC_BRID,   KC_BRIU,   RGB_HUI
#define SYSTEM_R2____________________________________________ \
          _______,   KC_MPRV,   KC_MPLY,   KC_MUTE,   KC_MNXT
#define SYSTEM_R3____________________________________________ \
          _______,  TG(_NUM),   KC_VOLD,   KC_VOLU,   _______
#define SYSTEM_R4______________________                       \
        _______________________________

#define LAYOUT_COMMON_SYSTEM                                   \
        SYSTEM_L1____________________________________________, \
        SYSTEM_R1____________________________________________, \
        SYSTEM_L2____________________________________________, \
        SYSTEM_R2____________________________________________, \
        SYSTEM_L3____________________________________________, \
        SYSTEM_R3____________________________________________, \
        SYSTEM_L4______________________,                       \
        SYSTEM_R4______________________



#define NAVIGATION_L1________________________________________ \
          KC_PSCR,   KC_ACL0,   KC_ACL1,   KC_ACL2,   _______
#define NAVIGATION_L2________________________________________ \
          KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,   KC_BTN3
#define NAVIGATION_L3________________________________________ \
          _______,   KC_WH_U,   KC_WH_D,  TG(_NAV),   KC_BTN2
#define NAVIGATION_L4__________________                       \
          _______,   _______,    KC_ESC

#define NAVIGATION_R1________________________________________ \
          KC_BSPC,   KC_HOME,   KC_PGDN,   KC_PGUP,    KC_END
#define NAVIGATION_R2________________________________________ \
          KC_CAPS,   KC_LEFT,   KC_DOWN,     KC_UP,   KC_RGHT
#define NAVIGATION_R3________________________________________ \
          KC_BTN1,   KC_MS_L,   KC_MS_D,   KC_MS_U,   KC_MS_R
#define NAVIGATION_R4__________________                       \
           KC_DEL,    KC_ENT,   _______

#define LAYOUT_COMMON_NAVIGATION                               \
        NAVIGATION_L1________________________________________, \
        NAVIGATION_R1________________________________________, \
        NAVIGATION_L2________________________________________, \
        NAVIGATION_R2________________________________________, \
        NAVIGATION_L3________________________________________, \
        NAVIGATION_R3________________________________________, \
        NAVIGATION_L4__________________,                       \
        NAVIGATION_R4__________________



#define NUMERAL_GEN_L4_________________ \
          _______,    KC_TAB,    KC_ESC

#define NUMERAL_GEN_R4_________________ \
        _______________________________

#define NUMERAL_ERGO_L1______________________________________ \
        FUNC_ERGO_L__________________________________________
#define NUMERAL_ERGO_L2______________________________________ \
        NUMROW_ERGO_L_MODS___________________________________
#define NUMERAL_ERGO_L3______________________________________ \
           KC_F12,    KC_F11,   KC_MINS,    KC_SPC,   KC_BSPC
#define NUMERAL_ERGO_L4________________                       \
        NUMERAL_GEN_L4_________________

#define NUMERAL_ERGO_R1______________________________________ \
        FUNC_ERGO_R__________________________________________
#define NUMERAL_ERGO_R2______________________________________ \
        NUMROW_ERGO_R_MODS___________________________________
#define NUMERAL_ERGO_R3______________________________________ \
           KC_DEL,  TG(_NUM),   _______,   _______,   KC_SLSH
#define NUMERAL_ERGO_R4________________                       \
        NUMERAL_GEN_R4_________________

#define LAYOUT_COMMON_NUMERAL_ERGO                             \
        NUMERAL_ERGO_L1______________________________________, \
        NUMERAL_ERGO_R1______________________________________, \
        NUMERAL_ERGO_L2______________________________________, \
        NUMERAL_ERGO_R2______________________________________, \
        NUMERAL_ERGO_L3______________________________________, \
        NUMERAL_ERGO_R3______________________________________, \
        NUMERAL_ERGO_L4________________,                       \
        NUMERAL_ERGO_R4________________



#define NUMERAL_L1___________________________________________ \
        FUNC_L_______________________________________________
#define NUMERAL_L2___________________________________________ \
        NUMROW_L_MODS________________________________________
#define NUMERAL_L3___________________________________________ \
           KC_F11,    KC_F12,   KC_MINS,    KC_SPC,   KC_BSPC
#define NUMERAL_L4_____________________                       \
        NUMERAL_GEN_L4_________________

#define NUMERAL_R1___________________________________________ \
        FUNC_R_______________________________________________
#define NUMERAL_R2___________________________________________ \
        NUMROW_R_MODS________________________________________
#define NUMERAL_R3___________________________________________ \
           KC_DEL,  TG(_NUM),   _______,   _______,   KC_SLSH
#define NUMERAL_R4_____________________                       \
        NUMERAL_GEN_R4_________________

#define LAYOUT_COMMON_NUMERAL                                  \
        NUMERAL_L1___________________________________________, \
        NUMERAL_R1___________________________________________, \
        NUMERAL_L2___________________________________________, \
        NUMERAL_R2___________________________________________, \
        NUMERAL_L3___________________________________________, \
        NUMERAL_R3___________________________________________, \
        NUMERAL_L4_____________________,                       \
        NUMERAL_GEN_R4_________________



#define SYMBOL_L1____________________________________________ \
          KC_EXLM,     KC_AT,   KC_HASH,    KC_DLR,   KC_PERC
#define SYMBOL_L2____________________________________________ \
          KC_PLUS,    KC_EQL,   KC_LPRN,   KC_RPRN,    KC_DQT
#define SYMBOL_L3____________________________________________ \
            KC_LT,   KC_PIPE,   KC_MINS,     KC_GT,   KC_BSLS
#define SYMBOL_L4______________________ \
          _______, SKC_ND_MD,   _______
#define SYMBOL_L2_MODS_______________________________________ \
 MODS_L(SYMBOL_L2____________________________________________)

#define SYMBOL_R1____________________________________________ \
          KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_QUES,   KC_QUOT
#define SYMBOL_R2____________________________________________ \
          KC_COLN,   KC_RBRC,   KC_LBRC,   KC_RCBR,   KC_LCBR
#define SYMBOL_R3____________________________________________ \
           KC_GRV,   KC_UNDS,   KC_SLSH,   KC_TILD,   KC_SCLN
#define SYMBOL_R4______________________ \
          _______, SKC_BU_EL,   _______
#define SYMBOL_R2_MODS_______________________________________ \
 MODS_R(SYMBOL_R2____________________________________________)

#define LAYOUT_COMMON_SYMBOL                                   \
        SYMBOL_L1____________________________________________, \
        SYMBOL_R1____________________________________________, \
        SYMBOL_L2_MODS_______________________________________, \
        SYMBOL_R2_MODS_______________________________________, \
        SYMBOL_L3____________________________________________, \
        SYMBOL_R3____________________________________________, \
        SYMBOL_L4______________________,                       \
        SYMBOL_R4______________________

// clang-format on

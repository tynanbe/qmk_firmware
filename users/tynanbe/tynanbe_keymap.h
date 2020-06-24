#pragma once

#include "quantum.h"
#include "tynanbe.h"
#include "tynanbe_process_record.h"



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
 * automatically apply `MT(MOD_*, keycode)` mod-tap modifiers with e.g.
 * the `MODS_L()` and `MODS_R()` utility macros.
 */

#define MT_BASIC_L(kc_0, kc_1, kc_2, kc_3, kc_4) \
        MT(MOD_LSFT, (kc_0)),                    \
        MT(MOD_LCTL, (kc_1)),                    \
        MT(MOD_LALT, (kc_2)),                    \
        MT(MOD_LGUI, (kc_3)),                    \
        (kc_4)
#define MODS_L(...) MT_BASIC_L(__VA_ARGS__)

#define MT_BASIC_R(kc_4, kc_3, kc_2, kc_1, kc_0) \
        (kc_4),                                  \
        MT(MOD_LGUI, (kc_3)),                    \
        MT(MOD_LALT, (kc_2)),                    \
        MT(MOD_LCTL, (kc_1)),                    \
        MT(MOD_LSFT, (kc_0))
#define MODS_R(...) MT_BASIC_R(__VA_ARGS__)

#define LT_BASIC_L(kc_0, kc_1, kc_2, kc_3, kc_4) \
        LT(_SYS, (kc_0)),                        \
        (kc_1),                                  \
        (kc_2),                                  \
        (kc_3),                                  \
        (kc_4)
#define LYRS_L(...) LT_BASIC_L(__VA_ARGS__)

#define LT_BASIC_R(kc_4, kc_3, kc_2, kc_1, kc_0) \
        (kc_4),                                  \
        (kc_3),                                  \
        (kc_2),                                  \
        (kc_1),                                  \
        LT(_SYS, (kc_0))
#define LYRS_R(...) LT_BASIC_R(__VA_ARGS__)



/* Advanced mod-tap macros that will automatically supply `process_record_user`
 * with the logic needed to process mod-tap keycodes that can send non-basic
 * keycodes on tap, e.g. shifted keycodes, which are normally not supported.
 *
 * Use `#undef MT_MAP_USER` in the keymap space to totally override userspace
 * invocations of these macros.
 *
 * Use `#def MT_MAP_KEYMAP` in the keymap space to support more layers, in
 * addition to (or instead of), those defined in userspace.
 *
 * The `MT_MAP(layer, row_l, row_r, row_l_mods, row_r_mods)` macro will compare
 * the `row_l` and `row_r` keycodes with their `row_l_mods` and `row_r_mods`
 * counterparts respectively, when `layer` is the highest active layer, sending
 * the `row_l` and `row_r` keycodes on tap actions in place of any `row_l_mods`
 * and `row_r_mods` keycodes that differ.
 *
 * Example:
 * ```
 * #define ROW_L              KC_TILDE,   KC_A, KC_LCBR, KC_RCBR,   KC_D
 * #define ROW_L_MODS  MODS_L(  KC_F21,   KC_A,  KC_F23,  KC_F24,   KC_D)
 * #define ROW_R                   ...,    ...,     ...,     ...,    ...
 * #define ROW_R_MODS  MODS_R(     ..., KC_F21,  KC_F22,  KC_F23, KC_F24)
 *
 * #define MT_MAP_USER \
 *         MT_MAP(_SYM,      ROW_L,      ROW_R, ROW_L_MODS, ROW_R_MODS)
 * ```
 *
 * In the above example, the first key in `row_l_mods` will send `KC_TILDE` when
 * QMK recognizes a tap event, rather than `KC_F21`, simply by recognizing that
 * the keycodes differ. Conversely, the second key in `row_l_mods` will bypass
 * any special processing and send `KC_A` on tap events.
 */

#define MT_MAP_KEYCODE(kc, mt_kc)        \
        case (mt_kc):                    \
          if (record->tap.count > 0      \
          && (kc) != ((mt_kc) & 0xFF)) { \
            if (record->event.pressed) { \
              register_code16((kc));     \
            } else {                     \
              unregister_code16((kc));   \
            }                            \
            handoff = false;             \
          }                              \
          break;

#define MT_MAP_ROW(layer,                             \
                    kc_0,  kc_1,  kc_2,  kc_3, _kc_4, \
                   _kc_5,  kc_6,  kc_7,  kc_8,  kc_9, \
                    mt_0,  mt_1,  mt_2,  mt_3, _mt_4, \
                   _mt_5,  mt_6,  mt_7,  mt_8,  mt_9) \
        case (layer):                                 \
          switch(keycode) {                           \
            MT_MAP_KEYCODE((kc_0), (mt_0))            \
            MT_MAP_KEYCODE((kc_1), (mt_1))            \
            MT_MAP_KEYCODE((kc_2), (mt_2))            \
            MT_MAP_KEYCODE((kc_3), (mt_3))            \
            MT_MAP_KEYCODE((kc_6), (mt_6))            \
            MT_MAP_KEYCODE((kc_7), (mt_7))            \
            MT_MAP_KEYCODE((kc_8), (mt_8))            \
            MT_MAP_KEYCODE((kc_9), (mt_9))            \
          }                                           \
          break;

#define MT_MAP(...) MT_MAP_ROW(__VA_ARGS__)



#define _____________________________________________________ \
          _______,   _______,   _______,   _______,   _______

#define _______________________________                       \
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



#define THUMB_ERGO_L___________________                       \
                  OSM(MOD_LSFT), LT(_NAV, KC_BSPC), OSL(_SYM)

#define THUMB_ERGO_R___________________                       \
        OSL(_SYM), LT(_NUM, KC_SPC), OSM(MOD_LSFT)



#define COLEMAK_DHM_L1_______________________________________ \
             KC_Q,      KC_W,      KC_F,      KC_P,      KC_B
#define COLEMAK_DHM_L2_______________________________________ \
             KC_A,      KC_R,      KC_S,      KC_T,      KC_G
#define COLEMAK_DHM_L3_______________________________________ \
             KC_Z,      KC_X,      KC_C,      KC_D,      KC_V
#define COLEMAK_DHM_L2_MODS__________________________________ \
 MODS_L(COLEMAK_DHM_L2_______________________________________)
#define COLEMAK_DHM_L3_LYRS__________________________________ \
 LYRS_L(COLEMAK_DHM_L3_______________________________________)

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
        COLEMAK_DHM_L3_LYRS__________________________________, \
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
#define QWERTY_L3_LYRS_______________________________________ \
 LYRS_L(QWERTY_L3____________________________________________)

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
        QWERTY_L3_LYRS_______________________________________, \
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
#define DVORAK_L3_LYRS_______________________________________ \
 LYRS_L(DVORAK_L3____________________________________________)

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
        DVORAK_L3_LYRS_______________________________________, \
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
#define COLEMAK_L3_LYRS______________________________________ \
 LYRS_L(COLEMAK_L3___________________________________________)

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
        COLEMAK_L3_LYRS______________________________________, \
        COLEMAK_R3___________________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________



#define SYSTEM_L1____________________________________________ \
            RESET,     DEBUG,   MG_NKRO,    DF_MOD,   RGB_TOG
#define SYSTEM_L2____________________________________________ \
          KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,   KC_CAPS
#define SYSTEM_L3____________________________________________ \
          _______,   _______,   _______,  TG(_NAV),   _______
#define SYSTEM_L4______________________                       \
                              _______________________________

#define SYSTEM_R1____________________________________________ \
          RGB_MOD,   RGB_SPI,   RGB_HUI,   RGB_SAI,   RGB_VAI
#define SYSTEM_R2____________________________________________ \
          KC_BRIU,   KC_MPRV,   KC_MPLY,   KC_MUTE,   KC_MNXT
#define SYSTEM_R3____________________________________________ \
          KC_BRID,  TG(_NUM),   KC_VOLD,   KC_VOLU,   _______
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
          _______,   KC_WH_U,   KC_WH_D,  TG(_NAV),    KC_INS
#define NAVIGATION_L4__________________                       \
                                _______,   _______,    KC_ESC

#define NAVIGATION_R1________________________________________ \
          KC_BSPC,   KC_HOME,   KC_PGDN,   KC_PGUP,    KC_END
#define NAVIGATION_R2________________________________________ \
          KC_BTN2,   KC_LEFT,   KC_DOWN,     KC_UP,   KC_RGHT
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



#define NUMERAL_GEN_L4_________________                       \
                                _______,    KC_TAB,    KC_ESC

#define NUMERAL_GEN_R4_________________                       \
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
#define SYMBOL_L4______________________                       \
                                _______, SKC_ND_MD,   _______
#define SYMBOL_L2_MODS_______________________________________ \
 MODS_L(   KC_F21,    KC_EQL,    KC_F23,    KC_F24,    KC_DQT)


#define SYMBOL_R1____________________________________________ \
          KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_QUES,   KC_QUOT
#define SYMBOL_R2____________________________________________ \
          KC_COLN,   KC_RBRC,   KC_LBRC,   KC_RCBR,   KC_LCBR
#define SYMBOL_R3____________________________________________ \
           KC_GRV,   KC_UNDS,   KC_SLSH,   KC_TILD,   KC_SCLN
#define SYMBOL_R4______________________                       \
          _______, SKC_BU_EL,   _______
#define SYMBOL_R2_MODS_______________________________________ \
 MODS_R(  KC_COLN,   KC_RBRC,   KC_LBRC,    KC_F23,    KC_F24)

#define LAYOUT_COMMON_SYMBOL                                   \
        SYMBOL_L1____________________________________________, \
        SYMBOL_R1____________________________________________, \
        SYMBOL_L2_MODS_______________________________________, \
        SYMBOL_R2_MODS_______________________________________, \
        SYMBOL_L3____________________________________________, \
        SYMBOL_R3____________________________________________, \
        SYMBOL_L4______________________,                       \
        SYMBOL_R4______________________



#define MT_MAP_USER                                                   \
        MT_MAP(_SYM,                                                  \
               SYMBOL_L2____________________________________________, \
               SYMBOL_R2____________________________________________, \
               SYMBOL_L2_MODS_______________________________________, \
               SYMBOL_R2_MODS_______________________________________)

// clang-format on

#pragma once

#include "tynanbe.h"
#include "tynanbe_keymap.h"
#include "quantum.h"
#include "process_tap_dance.h"



// clang-format off

/* Utility Macros */
/* Reusable tap dance action that handles all common mod-tap-style tap dances.
 */
#define ACTION_TAP_DANCE_TD_MT_COMMON                                   \
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mt_finished, td_mt_reset)

#define TAP_DANCE_ACTIONS_KEYS( kc_0,  kc_1,  kc_2,  kc_3, _kc_4, \
                               _kc_5,  kc_6,  kc_7,  kc_8,  kc_9) \
        [kc_0] = ACTION_TAP_DANCE_TD_MT_COMMON,                   \
        [kc_1] = ACTION_TAP_DANCE_TD_MT_COMMON,                   \
        [kc_2] = ACTION_TAP_DANCE_TD_MT_COMMON,                   \
        [kc_3] = ACTION_TAP_DANCE_TD_MT_COMMON,                   \
        [kc_6] = ACTION_TAP_DANCE_TD_MT_COMMON,                   \
        [kc_7] = ACTION_TAP_DANCE_TD_MT_COMMON,                   \
        [kc_8] = ACTION_TAP_DANCE_TD_MT_COMMON,                   \
        [kc_9] = ACTION_TAP_DANCE_TD_MT_COMMON

#define TAP_DANCE_ACTIONS_ROW(...) TAP_DANCE_ACTIONS_KEYS(__VA_ARGS__)

#define TAP_DANCE_ACTIONS(layer)                   \
        TAP_DANCE_ACTIONS_ROW(TD_MT_ROW_ ## layer)



/* Maintain common user `tap_dance_action` macros here.
 *
 * Must be maintained manually.
 * Do NOT end any of these macros with a trailing comma.
 */

/* Maintain here rows containing non-basic keycodes that will be mod-tap-like.
 *
 * Must be maintained manually.
 * Do NOT end with a trailing comma.
 * Use e.g. `{SYMBOL_L2___, SYMBOL_R2___}` rather than
 * e.g. `{SYMBOL_L2_MODS___, SYMBOL_R2_MODS___}`
 */
#define TD_MT_ROW__SYM                                         \
        SYMBOL_L2____________________________________________, \
        SYMBOL_R2____________________________________________

/* Maintain here a partial array of tap dance actions.
 * Useful for including common tap dance actions in individual `keymap.c` files.
 *
 * Maps each layer number to a single 10-key, full-row array.
 * Must be maintained manually.
 * Do NOT end with a trailing comma.
 */
#define TAP_DANCE_ACTIONS_USER   \
        TAP_DANCE_ACTIONS(_SYM)

/* Maintain here a map of rows, indexed by layer, formatted as a partial array.
 * These rows should contain non-basic keycodes that will have mod-tap behavior.
 *
 * Maps each layer number to a single 10-key, full-row array.
 * Used in `td_mt_finished()` and `td_mt_reset()` via `td_mt_map[]`
 * Must be maintained manually.
 * Do NOT end with a trailing comma.
 */
#define TD_MT_MAP_USER             \
        [_SYM] = {TD_MT_ROW__SYM}



/* Logical expression to map common modifiers to a full 10-key row of keycodes.
 * Use with advanced keycodes that do not work with the basic mod-tap macro.
 *
 * Used in `td_mt_finished()` and `td_mt_reset()`
 */
#define TD_MOD(kc, row)                          \
        (((kc) == row[0] || (kc) == row[9])      \
        ? KC_LSFT                                \
        : ((kc) == row[1] || (kc) == row[8])     \
          ? KC_LCTL                              \
          : ((kc) == row[2] || (kc) == row[7])   \
            ? KC_LALT                            \
            : ((kc) == row[3] || (kc) == row[6]) \
              ? KC_LGUI                          \
              : XXXXXXX)

// clang-format on



void td_mt_finished(qk_tap_dance_state_t *state, void *user_data);
void td_mt_reset(qk_tap_dance_state_t *state, void *user_data);

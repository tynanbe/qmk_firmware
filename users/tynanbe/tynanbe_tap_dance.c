#include "tynanbe_tap_dance.h"



// clang-format off

const uint16_t td_mt_map[][10] = {
  TD_MT_MAP_USER,
};

// clang-format on



void td_mt_finished(qk_tap_dance_state_t *state, void *user_data) {
  for (int taps = state->count - 1; taps > 0; taps--) {
    tap_code16(state->keycode);
  }
  if (state->pressed) {
    for (int layer = LAYERS_ADVANCED_MAX; layer >= LAYERS_ADVANCED; layer--) {
      if (layer_state_cmp(layer_state, layer)) {
        register_mods(MOD_BIT(TD_MOD(state->keycode, td_mt_map[layer])));
        return;
      }
    }
  }
  else {
    register_code16(state->keycode);
  }
}

void td_mt_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->pressed) {
    for (int layer = LAYERS_ADVANCED_MAX; layer >= LAYERS_ADVANCED; layer--) {
      if (layer_state_cmp(layer_state, layer)) {
        unregister_mods(MOD_BIT(TD_MOD(state->keycode, td_mt_map[layer])));
        return;
      }
    }
  }
  else {
    unregister_code16(state->keycode);
  }
}

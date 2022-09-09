#ifndef REDOX_AH_UTIL_MACRO_H_
#define REDOX_AH_UTIL_MACRO_H_

#define AH_SINGLE_TD(_name_, key1, key2)                                       \
  void dance_finished_##_name_(qk_tap_dance_state_t* state, void* user_data) { \
    if (state->count == 1) {                                                   \
      register_code(key1);                                                     \
    } else {                                                                   \
      register_code(key2);                                                     \
      register_code(key1);                                                     \
    }                                                                          \
  }                                                                            \
  void dance_reset_##_name_(qk_tap_dance_state_t* state, void* user_data) {    \
    if (state->count == 1) {                                                   \
      unregister_code(key1);                                                   \
    } else {                                                                   \
      unregister_code(key2);                                                   \
      unregister_code(key1);                                                   \
    }                                                                          \
  }

#define AH_STATIC_LIGHT(COLOR)                        \
  rgblight_enable_noeeprom();                         \
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); \
  rgblight_sethsv_noeeprom(COLOR);

#define AH_SEND_KEY_OR_SHIFT_THEN(key, key_then) \
  if (record->event.pressed) {                   \
    if (get_mods() & MOD_MASK_SHIFT) {           \
      SEND_STRING((key_then));                   \
    } else {                                     \
      SEND_STRING((key));                        \
    }                                            \
  }

#endif

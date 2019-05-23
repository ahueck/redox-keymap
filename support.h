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

#endif

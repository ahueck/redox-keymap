#include QMK_KEYBOARD_H
#include "version.h"

extern keymap_config_t keymap_config;

#include "support.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _SYMB_EXT 2
#define _ADJUST 3
#define _STD 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMB,
  SYMB_EXT,
  ADJUST,
  STD,
  ASC_SAR,
  ASC_VERS,
  M_AE,
  M_OE,
  M_UE,
  M_ESZ,
  M_MU,
  M_EUR
};

// Tap dance keycodes
enum tap_dance { TD_ESC_CAPS = 0 };

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

// Send custom strings
// For Umlauts etc.: // setxkbmap -option compose:ralt
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed) {
    const uint8_t mods = get_mods();

    switch (keycode) {
      case ASC_SAR:
        AH_SEND_KEY_OR_SHIFT_THEN("->", "=>")
        return false;
      case ASC_VERS:
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_BUILDDATE " : " QMK_VERSION);
        return false;
      case M_AE:
        SEND_STRING(SS_RALT(SS_LSFT("'")) "a");
        return false;
      case M_OE:
        SEND_STRING(SS_RALT(SS_RSFT("'")) "o");
        return false;
      case M_UE:
        SEND_STRING(SS_RALT(SS_RSFT("'")) "u");
        return false;
      case M_ESZ:
        SEND_STRING(SS_RALT("ss"));
        return false;
      case M_MU:
        SEND_STRING(SS_RALT("/u"));
        return false;
      case M_EUR:
        SEND_STRING(SS_RALT("c="));
        return false;
    }
  }
  return true;
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_disable_noeeprom();
}

// Change LED colors depending on the layer.
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _SYMB:
      AH_STATIC_LIGHT(HSV_GREEN);
      break;
    case _SYMB_EXT:
      AH_STATIC_LIGHT(HSV_BLUE);
      break;
    case _ADJUST:
      AH_STATIC_LIGHT(HSV_RED);
      break;
    default:
      rgblight_disable_noeeprom();
      break;
  }
  return state;
};
#endif

// Shortcut to make keymap more readable
#define KC_BKSL KC_BSLASH
#define SYM_L MO(_SYMB)

#define KC_SYSP LT(_SYMB, KC_SPC)   // symbol layer or space
#define KC_SYBS LT(_SYMB, KC_BSPC)  // symbol layer or backspace

#define KC_SYEEN LT(_SYMB_EXT, KC_ENT)  // ext. symbol layer or enter
#define KC_SYEDE LT(_SYMB_EXT, KC_DEL)  // ext. symbol layer or delete

#define KC_RSBS RSFT_T(KC_BSLS)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

#define TDKC_ESC TD(TD_ESC_CAPS)

#define KC_CTSP LCTL(KC_SPC)
#define KC_CTQU RCTL_T(KC_QUOT)

#define KC_VOLM KC_AUDIO_MUTE
#define KC_CALC KC_CALCULATOR

#define KC_CTME MT(MOD_LCTL | MOD_LGUI, KC_TILD)
#define KC_CTSH MT(MOD_LCTL | MOD_LSFT, KC_PMNS)
#define KC_CTAL MT(MOD_LCTL | MOD_LALT, KC_PPLS)

#define OC_CTSH OSM(MOD_LCTL | MOD_LSFT)
#define OC_CTAL OSM(MOD_LCTL | MOD_LALT)

#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(KC_Y)
#define KC_CPY LCTL(KC_C)
#define KC_PST LCTL(KC_V)
#define KC_CUT LCTL(KC_X)

#define TO_BASE TO(_QWERTY)
#define TO_STD TO(_STD)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_CAPS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_CPY  ,                          KC_PSCR ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_UNDO ,                          KC_REDO ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_CTQU ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSBS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,OC_CTSH ,OC_CTAL ,KC_LALT ,     KC_LCTL ,    KC_SYBS ,KC_SYEDE,        KC_SYEEN,KC_SYSP ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_CTME ,KC_TILD ,KC_HASH ,KC_LPRN ,KC_RPRN ,_______ ,                          _______ ,KC_T    ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,KC_F12 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_CTSH ,KC_UNDS ,KC_EQL  ,KC_LCBR ,KC_RCBR ,_______ ,                          _______ ,KC_P    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_CTAL ,KC_AMPR ,KC_ASTR ,KC_LBRC ,KC_RBRC ,_______ ,_______ ,        _______ ,_______ ,KC_CTSP ,ASC_SAR ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    KC_RCTRL,     KC_VOLD ,KC_VOLU ,KC_VOLM ,KC_CALC 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB_EXT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,KC_CLEAR,KC_BSPC ,XXXXXXX ,M_EUR   ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_REDO ,KC_CUT  ,KC_CPY  ,KC_PST  ,KC_UNDO ,_______ ,                          _______ ,KC_PAST ,KC_KP_7 ,KC_KP_8 ,KC_KP_9 ,KC_CALC ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_CTSH ,KC_ENT  ,KC_SPC  ,KC_BSPC ,KC_DEL  ,_______ ,                          _______ ,KC_PSLS ,KC_KP_4 ,KC_KP_5 ,KC_KP_6 ,KC_PCMM ,KC_PENT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_CTAL ,M_AE    ,M_OE    ,M_UE    ,M_ESZ   ,_______ ,_______ ,        _______ ,_______ ,KC_PMNS ,KC_KP_1 ,KC_KP_2 ,KC_KP_3 ,KC_PDOT ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    KC_PPLS ,     KC_KP_0 ,KC_KP_0 ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,QK_BOOT ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                          RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,TO_STD  ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,ASC_VERS,XXXXXXX ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_STD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          TO_BASE ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_PGUP ,_______ ,        _______ ,KC_END  ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,_______ ,     _______ ,    KC_BSPC ,KC_DEL  ,        KC_ENT  ,KC_SPC  ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};
// clang-format on

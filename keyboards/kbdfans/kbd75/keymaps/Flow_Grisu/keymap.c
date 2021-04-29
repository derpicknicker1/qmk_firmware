#include QMK_KEYBOARD_H

bool autoshift_enabled = false;


void matrix_init_user(void){
  autoshift_disable();
}


enum custom_keycodes {
  CK_TEST = SAFE_RANGE,
  AS_TGGL,
  MK_CODE
};


void custom_autoshift_toggle(void){
      if (autoshift_enabled) {
        autoshift_enabled = false;
        autoshift_disable();
        writePinHigh(B2);   // Disable CAPS LED
        //breathing_disable();
      }
      else {
        autoshift_enabled = true;
        autoshift_enable();
        writePinLow(B2); // Enable CAPS LED
        //breathing_enable();
      }
}


void dance_L_SHIFT_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    register_code (KC_CAPS);
  }
  else if (state->count == 2) {
    custom_autoshift_toggle();
  }
  else {
    register_code (KC_LSFT);
  }
}


void dance_L_SHIFT_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    unregister_code (KC_CAPS);
  }
  else if (state->count == 2) {
    //unregister_code (KC_LSFT);
  }
  else {
    unregister_code (KC_LSFT);
  }
}


void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK) || autoshift_enabled) {
    writePinLow(B2);
  } else {
    writePinHigh(B2);
  }

  led_set_user(usb_led);
}


//Tap Dance Declarations
enum {
  TD_LS = 0,
};


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LS] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_L_SHIFT_finished, dance_L_SHIFT_reset)
};

//tedddddddddst
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // DEFAULT
	[0] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_HOME,  KC_INS,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   _______,  KC_BSPC,  KC_PGUP,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN ,
    MO(5),    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_DEL,
    TD(TD_LS),KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_HOME),    KC_UP,    KC_END ,
    KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,   KC_SPC,   KC_SPC,                       KC_RALT,  LT(5,KC_APP),KC_RCTL,KC_LEFT, KC_DOWN,  KC_RGHT
  ),

    // Functions, activated by CAPS LOCK
	[5] = LAYOUT(
    DF(0),    RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,  _______,  _______,  _______,  RESET,    KC_SLCK,  KC_PAUS,
    DF(1),    RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  BL_DEC,   BL_INC,   BL_STEP,  MK_CODE,  _______,  KC_BSPC,  KC_ASUP,
    KC_CAPS,  _______,  KC_WH_U,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_VOLU,  KC_MUTE,            KC_ASRP,
    _______,  KC_WH_L,  KC_WH_D,  KC_WH_R,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_F20,                       KC_CALC,  KC_ASDN,
    AS_TGGL,  _______,  _______,  _______,  _______,  _______,  _______,  KC_NLCK,  _______,  _______,  _______,  KC_VOLD,  KC_RSFT,            KC_PGUP,  _______,
    _______,  KC_RGUI,  CK_TEST,                      KC_MPLY,  KC_MPLY,  KC_MPLY,                      KC_MSTP,  KC_MPRV,  KC_MNXT,  KC_HOME,  KC_PGDN,  KC_END
  ), // BL_TOGG,  BL_STEP,

  // GAMING / PLAIN
	[1] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    KC_LSFT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_RSFT,            _______,  _______,
    _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  MO(5),    _______,  _______,  _______,  _______
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case CK_TEST:
      if (record->event.pressed) {
        // when keycode is pressed
        SEND_STRING("post@florian-schuette.de");
      } else {
        // when keycode is released
      }
      break;

    case MK_CODE:
      if (record->event.pressed) {
        // when keycode is pressed
        SEND_STRING("+ + + ");
      } else {
        // when keycode is released
      }
      break;

    case AS_TGGL:
      if (record->event.pressed) {
        custom_autoshift_toggle();
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key

  }
  return true;
};

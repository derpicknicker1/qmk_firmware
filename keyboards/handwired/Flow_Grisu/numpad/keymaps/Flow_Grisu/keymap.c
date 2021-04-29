#include QMK_KEYBOARD_H


//Tap Dance Declarations
enum {
  TD_DOT_COMMAS = 0,
  TD_NUM = 1
};

enum custom_keycodes {
  DP_CALC = SAFE_RANGE
};

void dance_NUM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_invert(1);
  }
  else if (state->count == 2) {
    register_code (KC_NLCK);
  }
  else if (state->count == 3) {
    layer_invert(2);
  }
  else if (state->count == 4) {
    layer_invert(3);
  }
  else if (state->count == 5) {
      reset_keyboard();
  }
  else {
  789278--++--++  register_code (KC_NLCK);
  }
}


void dance_NUM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {

  }
  else if (state->count == 2) {
    unregister_code (KC_NLCK);
  }
  else if (state->count == 3) {

  }
  else if (state->count == 4) {

  }
  else if (state->count == 5) {
      //reset_keyboard();
  }
  else {
    unregister_code (KC_NLCK);
  }
}



//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_DOT_COMMAS]  = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMMA),
  [TD_NUM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_NUM_finished, dance_NUM_reset)

};

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 0, HSV_RED}
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 15, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 15, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 7, 3, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,     // Overrides other layers
    my_layer3_layer,     // Overrides other layers
    my_layer4_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
    writePin(D4, true);
    writePin(B6, false);
}

/*
bool led_update_user(led_t led_state) {

    writePinLow(B4);
    writePinLow(B5);

    writePin(B4, led_state.num_lock);
    writePin(B5, !led_state.num_lock);

    return true;
}
*/

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(0, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));

    writePinLow(D4);
    writePinLow(B6);

    writePin(D4, !layer_state_cmp(state, 1));
    writePin(B6, layer_state_cmp(state, 1));
    return state;
}

bool led_update_user(led_t led_state) {

    //rgblight_set_layer_state(0, !led_state.num_lock);

    // Indicate NumLock on NumLock LED

    rgblight_set_layer_state(1, !led_state.num_lock);


    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case DP_CALC:
        if (record->event.pressed) {
            layer_invert(1);
            register_code(KC_CALC);
        } else {
            unregister_code(KC_CALC);
        }

        return false;
  }
  return true;

};

//In Layer declaration, add tap dance item in place of a key code

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Custom Macro-Pad
  [0] = LAYOUT_numpad_5x4(
    TD(TD_NUM),   KC_MPLY, KC_MUTE, KC_VOLD,
    KC_P7,   KC_P8,   KC_P9,
    KC_P4,   KC_P5,   KC_P6,        KC_VOLU,
    KC_P1,   KC_P2,   KC_P3,
    LT(3, KC_P0), TD(TD_DOT_COMMAS), KC_PENT
  ),
// Default numpad
   [1] = LAYOUT_numpad_5x4(
    _______,    KC_PSLS, KC_PAST,   KC_PMNS,
    KC_P7,      KC_P8,   KC_P9,
    KC_P4,      KC_P5,   KC_P6,     KC_PPLS,
    KC_P1,      KC_P2,   KC_P3,
    KC_P0,               KC_COMMA,  KC_PENT
  ),

  [2] = LAYOUT_numpad_5x4(
    _______,    KC_NO,      KC_MUTE,       KC_VOLD,
    KC_HOME,    KC_MS_UP,   KC_MS_WH_UP,
    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,   KC_VOLU,
    KC_END,     KC_MS_DOWN, KC_MS_WH_DOWN,
    KC_MS_BTN1,             KC_MS_BTN3,    KC_MS_BTN2
  ),

  [3] = LAYOUT_numpad_5x4(
    _______,   RGB_MOD,  RGB_TOG, RGB_HUD,
    RGB_VAI,   RGB_SAI,  KC_PGUP,
    KC_BSPC,   KC_ESC,   KC_MPLY, RGB_HUI,
    RGB_VAD,   RGB_SAD,  KC_PGDN,
    KC_NO,     KC_PDOT,           DP_CALC
  )
};

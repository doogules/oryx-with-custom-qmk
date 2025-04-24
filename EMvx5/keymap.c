#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_GRAVE,       KC_F12,         KC_MEDIA_PLAY_PAUSE,KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,                                KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_PSCR,        TG(2),          KC_DELETE,      KC_BSLS,
    KC_LEFT_GUI,    KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_SCLN,
    KC_LEFT_ALT,    KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_BSPC,        KC_QUOTE,
    KC_LEFT_CTRL,   KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_MINUS,       KC_QUES,
                                                    KC_LEFT_SHIFT,  MO(1),                                          KC_ENTER,       KC_SPACE
  ),
  [1] = LAYOUT_voyager(
    KC_TILD,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_PIPE,
    KC_TRANSPARENT, KC_PAGE_UP,     KC_7,           KC_8,           KC_9,           KC_LBRC,                                        KC_RBRC,        KC_HOME,        KC_UP,          KC_END,         KC_TRANSPARENT, KC_COLN,
    KC_TRANSPARENT, KC_0,           KC_4,           KC_5,           KC_6,           KC_LPRN,                                        KC_RPRN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_DQUO,
    KC_TRANSPARENT, KC_PGDN,        KC_1,           KC_2,           KC_3,           KC_LCBR,                                        KC_RCBR,        KC_PLUS,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MODE_FORWARD,RGB_SLD,        RGB_VAD,        RGB_VAI,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HSV_0_255_255,  HSV_74_255_255, HSV_169_255_255,
                                                    KC_TRANSPARENT, KC_SPACE,                                       KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

const uint16_t PROGMEM combo0[] = { KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo1[] = { KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo2[] = { KC_H, KC_K, COMBO_END};
const uint16_t PROGMEM combo3[] = { KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo4[] = { KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo5[] = { KC_C, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, KC_UNDS),
    COMBO(combo1, KC_COLN),
    COMBO(combo2, KC_SLASH),
    COMBO(combo3, KC_ESCAPE),
    COMBO(combo4, KC_TAB),
    COMBO(combo5, KC_EQUAL),
};


extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [1] = { {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255}, {152,255,255} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

static uint16_t idle_timer = 0;

void matrix_scan_user(void) {
    if (idle_timer && timer_expired(timer_read(), idle_timer)) {
    // keyboard is idle
        idle_timer = 0;
    }
}

// list of keys for timer to ignore
const uint16_t idle_timer_ignore_list[] = {
    KC_ENT, KC_ESC, KC_TAB, KC_BSPC, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, KC_UNDS, KC_COLN, KC_EQL, KC_EXLM, KC_SLSH
};
// function to check if a keycode is in the list
bool is_key_in_list(uint16_t keycode) {
    for (size_t i = 0; i < sizeof(idle_timer_ignore_list) / sizeof(idle_timer_ignore_list[0]); i++) {
        if (keycode == idle_timer_ignore_list[i]) {
            return true;
        }
    }
    return false;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    // only enable combos if keyboard is idle
    return idle_timer == 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!is_key_in_list(keycode)) {  // combo timer
    idle_timer = (record->event.time + IDLE_TIMEOUT_MS) | 1;
  }

  switch (keycode) {

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_0_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,255,255);
      }
      return false;
    case HSV_74_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(74,255,255);
      }
      return false;
    case HSV_169_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(169,255,255);
      }
      return false;
  }
  return true;
}




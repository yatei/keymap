#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
};

#define _______ KC_TRNS
#define XXX KC_NO
#define KC_LOWR LOWER

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY = QWERTY Keymap Layer
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |      |   7  |   8  |   9  |   0  |   -  |   =  | Bksp |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  | Bksp |      |   ]  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  | Del  |      | Ctrl |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |      | Shift|   N  |   M  |   ,  |   .  |   /  |   \  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Esc  | GUI  | Alt  | Lower| Bksp | Space| Enter|      | Enter| Space| GUI  | Left |  Up  | Down | Right|
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_QWERTY] = KEYMAP(
KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5  ,KC_6   , KC_7   ,KC_8   ,KC_9  ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,
KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T  ,KC_BSPC, KC_RBRC,KC_Y  ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,
KC_LCTL,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G  ,KC_DEL , KC_RCTL,KC_H  ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B  ,KC_N   , KC_RSFT,KC_N  ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
KC_ESC,KC_LGUI,KC_LALT ,LOWER  ,KC_BSPC,KC_SPC,KC_ENT , KC_ENT ,KC_SPC,KC_RGUI,KC_LEFT,KC_UP  ,KC_DOWN,KC_RIGHT
  ),

/* LOWER = Top: Fn Keys, Left: Mouse and Media, Right(Rotate 90°): Numpad
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  Esc |  Fn1 |  Fn2 |  Fn3 |  Fn4 |  Fn5 |  Fn6 |      |  Fn7 |  Fn8 |  Fn9 | Fn10 | Fn11 | Fn12 | Ins  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Tab |↑Wheel|LClick|   ↑  |RClick|↑Wheel| VolUp|      |      |      |   -  |   +  |   +  | Enter| Enter|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl |←Wheel|   ←  |   ↓  |   →  |→Wheel|VolDwn|      |      |      |   *  |   9  |   6  |   3  |   .  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shift|↓Wheel|Speed0|Speed1|Speed2|↓Wheel| Mute |      |      |      |   /  |   8  |   5  |   2  |   0  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Esc |  GUI |  Alt | Lower| Space|PrvMsc|NxtMsc|      |      |      |NumLck|   7  |   4  |   1  |   0  |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_LOWER] = KEYMAP(
KC_ESC ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  , KC_F7  ,KC_F8,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_INS ,
KC_TAB ,KC_WH_U,KC_BTN1,KC_MS_U,KC_BTN2,KC_WH_U,KC_VOLU, XXX    ,XXX  ,KC_PMNS,KC_PPLS,KC_PPLS,KC_PENT,KC_PENT,
KC_LCTL,KC_WH_L,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_R,KC_VOLD, XXX    ,XXX  ,KC_PAST,KC_P9  ,KC_P6  ,KC_P3  ,KC_PDOT,
KC_LSFT,KC_WH_D,KC_ACL0,KC_ACL1,KC_ACL2,KC_WH_D,KC_MUTE, XXX    ,XXX  ,KC_PSLS,KC_P8  ,KC_P5  ,KC_P2  ,KC_P0  ,
KC_ESC ,KC_LGUI,KC_LALT,_______,KC_SPC ,KC_MPRV,KC_MNXT, XXX    ,XXX  ,KC_NLCK,KC_P7  ,KC_P4  ,KC_P1  ,KC_P0
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
  }
  return true;
}

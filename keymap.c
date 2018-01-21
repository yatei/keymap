#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_AJST ADJUST
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define XXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY = QWERTY Keymap Layer
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |      |   7  |   8  |   9  |   0  |   -  |   =  | Bksp |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  | Lower|      |   [  |   ]  |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  | Lower|      |   ;  |   '  |   H  |   J  |   K  |   L  | Enter|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | Del  |      |   /  |   \  |   N  |   M  |   ,  |   .  |  Up  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Esc  | GUI  | Alt  |      | Space| Space| Enter|      | Enter| Space| Space| Space| Left | Right| Down |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_QWERTY] = KEYMAP(
KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4  ,KC_5  ,KC_6   , KC_7   ,KC_8   ,KC_9  ,KC_0  ,KC_MINS,KC_EQL ,KC_BSPC,
KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R  ,KC_T  ,KC_LOWR, KC_LBRC,KC_RBRC,KC_Y  ,KC_U  ,KC_I   ,KC_O   ,KC_P   ,
KC_LCTL,KC_A   ,KC_S   ,KC_D   ,KC_F  ,KC_G  ,KC_LOWR, KC_SCLN,KC_QUOT,KC_H  ,KC_J  ,KC_K   ,KC_L   ,KC_ENT ,
KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V  ,KC_B  ,KC_DEL , KC_SLSH,KC_BSLS,KC_N  ,KC_M  ,KC_COMM,KC_DOT ,KC_UP  ,
KC_ESC ,KC_LGUI,KC_LALT,XXX    ,KC_SPC,KC_SPC,KC_ENT , KC_ENT ,KC_SPC ,KC_SPC,KC_SPC,KC_LEFT,KC_RGHT,KC_DOWN
  ),

/* LOWER = Top: Fn Keys, Left: Mouse and Media, Right(Rotate 90°): Numpad
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  Esc |  Fn1 |  Fn2 |  Fn3 |  Fn4 |  Fn5 |  Fn6 |      |  Fn7 |  Fn8 |  Fn9 | Fn10 | Fn11 | Fn12 | Ins  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |  Tab |↑Wheel|LClick|   ↑  |RClick|↑Wheel|      |      |      |      |   -  |   +  |   +  | Enter| Enter|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Ctrl |←Wheel|   ←  |   ↓  |   →  |→Wheel|      |      |      |      |   *  |   9  |   6  |   3  |   .  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shift|↓Wheel|Speed0|Speed1|Speed2|↓Wheel| VolUp|      |      |      |   /  |   8  |   5  |   2  |   0  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | L-QW |  GUI |  Alt |PrvMsc|NxtMsc| Mute |VolDwn|      | L-QW |      |NumLck|   7  |   4  |   1  |   0  |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_LOWER] = KEYMAP(
KC_ESC ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  , KC_F7  ,KC_F8,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_INS ,
KC_TAB ,KC_WH_U,KC_BTN1,KC_MS_U,KC_BTN2,KC_WH_U,XXX    , XXX    ,XXX  ,KC_PMNS,KC_PPLS,KC_PPLS,KC_PENT,KC_PENT,
KC_LCTL,KC_WH_L,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_R,XXX    , XXX    ,XXX  ,KC_PAST,KC_P9  ,KC_P6  ,KC_P3  ,KC_PDOT,
KC_LSFT,KC_WH_D,KC_ACL0,KC_ACL1,KC_ACL2,KC_WH_D,KC_VOLU, XXX    ,XXX  ,KC_PSLS,KC_P8  ,KC_P5  ,KC_P2  ,KC_P0  ,
KC_RASE,KC_LGUI,KC_LALT,KC_MPRV,KC_MNXT,KC_MUTE,KC_VOLD, KC_RASE,XXX  ,KC_NLCK,KC_P7  ,KC_P4  ,KC_P1  ,KC_P0
  ),

/* Raise
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   _  |      |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   {  |   }  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   +  |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   -  |   =  |   [  |   ]  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |ISO # |ISO / |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,TILD, F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     UNDS,    , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,LCBR,RCBR,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PLUS,    , F1 , F2 , F3 , F4 , F5 ,      F6 ,MINS,PLUS,LBRC,RBRC,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    , F7 , F8 , F9 ,F10 ,F11 ,     F12 ,NUHS,NUBS,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,MNXT,VOLD,VOLU,MPLY,MUTE
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_ADJUST] = KEYMAP(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
    _______, _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL,  _______, \
    _______, _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

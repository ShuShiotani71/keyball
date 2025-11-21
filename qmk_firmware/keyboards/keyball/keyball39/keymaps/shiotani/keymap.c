/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "ascii_arts/reze.h"


// const key_override_t comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_TILD);
// const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_HASH);

// const key_override_t **key_overrides = (const key_override_t *[]){
	// &comm_key_override,
	// &dot_key_override,
	// NULL
// };


enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    NAME,
    REZE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case EMAIL:
        if (record->event.pressed) {
            SEND_STRING("shu.shiotani70@gmail.com");
        }
        return false;
    case NAME:
        if (record->event.pressed) {
            SEND_STRING("Shu Shiotani");
        }
        return false;
    case REZE:
        if (record->event.pressed) {
            SEND_STRING(REZE_ASCII);
        }
        return false;
    }
    return true;
};


#define D_LGUI MT(MOD_LGUI, KC_D)
#define F_LALT MT(MOD_LALT, KC_F)
#define K_RGUI MT(MOD_RGUI, KC_K)
#define J_RALT MT(MOD_RALT, KC_J)
#define L_LT3 LT(3, KC_L)

#define SPC_RCTL MT(MOD_RCTL, KC_SPC)

#define SCRN_SHT LSFT(LGUI(KC_S))
#define WIN_SEC LCTL(LALT(KC_DEL))
#define CH_LANG RCTL(KC_SPC)

#define SCR_LEFT KC_MS_WH_LEFT
#define SCR_DOWN KC_MS_WH_DOWN
#define SCR_UP KC_MS_WH_UP
#define SCR_RGHT KC_MS_WH_RIGHT

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
      KC_Q         , KC_W         , KC_E         , KC_R         , KC_T         ,                               KC_Y         , KC_U         , KC_I         , KC_O         , KC_P         ,
      KC_A         , KC_S         , D_LGUI       , F_LALT       , KC_G         ,                               KC_H         , J_RALT       , K_RGUI       , L_LT3        , KC_BSPC      ,
      KC_Z         , KC_X         , KC_C         , KC_V         , KC_B         ,                               KC_N         , KC_M         , KC_COMM      , KC_DOT       , KC_ENT       ,
      _______      , _______      , _______      , _______      , MO(1)        , KC_LSFT      , SPC_RCTL     , MO(2)        , _______      , _______      , _______      , _______
  ),

  [1] = LAYOUT_universal(
      _______      , KC_PERC      , KC_CIRC      , KC_DLR       , KC_GRV       ,                               KC_AT        , KC_QUOT      , KC_LBRC      , KC_RBRC      , _______      ,
      KC_EXLM      , KC_QUES      , KC_MINS      , KC_UNDS      , KC_PIPE      ,                               KC_SCLN      , KC_DQT       , KC_LPRN      , KC_RPRN      , KC_COLN      ,
      KC_ASTR      , KC_TILD      , KC_HASH      , KC_AMPR      , KC_BSLS      ,                               KC_PLUS      , KC_EQL       , KC_LCBR      , KC_RCBR      , KC_SLSH      ,
      _______      , _______      , _______      , _______      , _______      , _______      , SPC_RCTL     , _______      , _______      , _______      , _______      , _______
  ),

  [2] = LAYOUT_universal(
      _______      , KC_1         , KC_2         , KC_3         , _______      ,                               _______      , _______      , KC_DEL       , CH_LANG      , _______      ,
      KC_0         , KC_4         , KC_5         , KC_6         , _______      ,                               KC_LEFT      , KC_DOWN      , KC_UP        , KC_RGHT      , KC_ESC       ,
      _______      , KC_7         , KC_8         , KC_9         , _______      ,                               SCR_LEFT     , SCR_DOWN     , SCR_UP       , SCR_RGHT     , _______      ,
      _______      , _______      , _______      , _______      , _______      , KC_LSFT      , _______      , _______      , _______      , _______      , _______      , _______
  ),

  [3] = LAYOUT_universal(
      DT_PRNT      , DT_DOWN      , DT_UP        , _______      , EMAIL        ,                               _______      , _______      , _______      , _______      , _______      ,
      KC_MUTE      , KC_VOLD      , KC_VOLU      , SCRN_SHT     , NAME         ,                               _______      , KC_MS_BTN4   , KC_MS_BTN5   , _______      , _______      ,
      _______      , KC_BRID      , KC_BRIU      , WIN_SEC      , REZE         ,                               _______      , _______      , _______      , _______      , _______      ,
      _______      , _______      , _______      , _______      , _______      , KC_LSFT      , SPC_RCTL     , _______      , _______      , _______      , _______      , _______
  ),


};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif


// custom settings
#ifdef COMBO_ENABLE
enum combos{
  BTN1,
  BTN2,
  TAB,
  ENTER,
  ESC,
};
const uint16_t PROGMEM btn1[] = {MT(MOD_RGUI, KC_K), LT(3, KC_L), COMBO_END};
const uint16_t PROGMEM btn2[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM tab[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM enter[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM esc[] = {KC_S, KC_D, COMBO_END};

combo_t key_combos[] = {
  [BTN1] = COMBO(btn1, KC_BTN1),
  [BTN2] = COMBO(btn2, KC_BTN2),
  [TAB] = COMBO(tab, KC_TAB),
  [ENTER] = COMBO(enter, KC_ENT),
  [ESC] = COMBO(esc, KC_ESC),
};
#endif

// per key tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_RCTL, KC_SPC):
            return g_tapping_term - 50; // g_tapping_term used instead of TAPPING_TERM since dynamic_tapping_term enabled
        default:
            return g_tapping_term;
    }
}
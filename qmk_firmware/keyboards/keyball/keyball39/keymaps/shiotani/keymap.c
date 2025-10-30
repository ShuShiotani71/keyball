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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , LT(3, KC_L), KC_BSPC  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_ENT   ,
    _______  , _______  , _______  , _______  , TO(1)    , KC_ENT   ,      KC_SPC   , TO(2)    , _______  , _______  , _______  , _______
  ),

  [1] = LAYOUT_universal(
    KC_GRV   , KC_PERC  , KC_CIRC  , KC_DLR   , KC_PIPE  ,                            KC_AT    , KC_TILD  , KC_LBRC  , KC_RBRC  , KC_SCLN  ,
    KC_EXLM  , KC_QUES  , KC_MINS  , KC_UNDS  , KC_HASH  ,                            KC_QUOT  , KC_DQT   , KC_LPRN  , KC_RPRN  , KC_COLN  ,
    KC_ASTR  , KC_LABK  , KC_RABK  , KC_AMPR  , KC_BSLS  ,                            KC_PLUS  , KC_EQL   , KC_LCBR  , KC_RCBR  , KC_SLSH  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      KC_SPC   , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_1     , KC_2     , KC_3     , _______  ,                            _______  , KC_DEL   , KC_TAB   ,RCTL(KC_SPC), _______,
    KC_0     , KC_4     , KC_5     , KC_6     , _______  ,                            KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_ESC   ,
    _______  , KC_7     , KC_8     , KC_9     , _______  ,                            KC_MS_WH_LEFT  , KS_MS_WH_DOWN  , KC_MS_WH_UP  , KC_MS_WH_RGHT  , KC_CAPS  ,
    _______  , _______  , _______  , _______  , _______  , KC_LSFT  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    DT_PRNT  , DT_DOWN  , DT_UP    , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_MUTE  , KC_VOLD  , KC_VOLU  , LSFT(LGUI(KC_S))  , _______ ,                    _______  , KC_MS_BTN4  , KC_MS_BTN5  , _______  , _______  ,
    _______  , KC_BRID  , KC_BRIU  , LCTL(LALT(KC_DEL)), _______ ,                    _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
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
};
const uint16_t PROGMEM btn1[] = {KC_K, LT(3, KC_L), COMBO_END};
const uint16_t PROGMEM btn2[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[] = {
  [BTN1] = COMBO(btn1, KC_BTN1),
  [BTN2] = COMBO(btn2, KC_BTN2),
};
#endif

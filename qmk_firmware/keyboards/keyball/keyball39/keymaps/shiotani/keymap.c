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

const key_override_t **key_overrides = (const key_override_t*[]) {
    // When KC_RSFT + KC_COMM (Shift + ,) is pressed, it becomes KC_EXLM (!)
    &((key_override_t){.key_code = KC_COMM, .mods = MOD_BIT(KC_LSFT), .override_code = KC_SCLN}),

    // When KC_LSFT + KC_DOT (Shift + .) is pressed, it becomes KC_QUES (?)
    &((key_override_t){.key_code = KC_DOT, .mods = MOD_BIT(KC_LSFT), .override_code = KC_COLN}),

    // Use MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT) for both shift keys
    &((key_override_t){.key_code = KC_EXLM, .mods = MOD_BIT(KC_LSFT), .override_code = KC_QUES}),

    NULL
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , LT(3, KC_L), KC_BSPC  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_EXLM   ,
    _______  , _______  , _______  , _______  , TO(1)    , KC_ENT   ,      KC_SPC   , TO(2)    , _______  , _______  , _______  , _______
  ),

  [1] = LAYOUT_universal(
    _______  , KC_DEL   , KC_TAB   , KC_ESC   , _______  ,                            _______  , KC_DEL   , KC_TAB   ,RCTL(KC_SPC), _______ ,
    OS_LGUI  , OS_LALT  , OS_LCTL  , OS_LSFT  , RTL(KC_SPC)  ,                            KC_LEFT  , KC_DOWN  , KC_UP  , KC_RIGHT  , KC_ESC    ,
    _______  , _______  , _______  , _______  , _______  ,                            KC_MS_WH_LEFT  , KC_MS_WH_DOWN , KC_MS_WH_UP  , KC_MS_WH_RIGHT  , KC_CAPS  ,
    _______  , _______  , _______  , _______  , _______  , _______ ,        KC_SPC  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    KC_GRV   , KC_PERC  , KC_CIRC  , KC_DLR   , KC_PIPE  ,                            KC_AT    , KC_TILD  , KC_LBRC  , KC_RBRC  , KC_MINS  ,
    KC_QUOT  , KC_DQT   , KC_LPRN  , KC_RPRN  , KC_UNDS  ,                            KC_HASH  , OS_RSFT  , OS_RCTL  , OS_RALT  , OS_RGUI   ,
    KC_ASTR  , KC_LABK  , KC_RABK  , KC_AMPR  , KC_BSLS  ,                            KC_PLUS  , KC_EQL   , KC_LCBR  , KC_RCBR  , KC_SLSH  ,
    _______  , _______  , _______  , _______  , _______  , KC_ENT  ,       _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    DT_PRNT  , DT_DOWN  , DT_UP    , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_MUTE  , KC_VOLD  , KC_VOLU  , LSFT(LGUI(KC_S))  , _______ ,                    _______  , KC_MS_BTN4  , KC_MS_BTN5  , _______  , _______  ,
    _______  , KC_BRID  , KC_BRIU  , LCTL(LALT(KC_DEL)), _______ ,                    _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    kc_1     , kc_2     , kc_3     , kc_4     , kc_5     ,                            kc_6     , kc_7     , kc_8     , kc_9     , kc_0     ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______
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
  LAYER4,
};
const uint16_t PROGMEM btn1[] = {KC_K, LT(3, KC_L), COMBO_END};
const uint16_t PROGMEM btn2[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM layer4[] = {TO(1), TO(2), COMBO_END};

combo_t key_combos[] = {
  [BTN1] = COMBO(btn1, KC_BTN1),
  [BTN2] = COMBO(btn2, KC_BTN2),
  [LAYER4] = COMBO(layer4, TO(4)),
};
#endif

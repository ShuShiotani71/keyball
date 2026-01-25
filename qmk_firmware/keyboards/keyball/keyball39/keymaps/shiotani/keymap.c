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
#include "ascii_arts/ascii_arts.h"
#include "os_detection.h"

const key_override_t comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_BSLS);
const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_GRV);
const key_override_t bspc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_ESC);

const key_override_t **key_overrides = (const key_override_t *[]){
    &comm_key_override,
    &dot_key_override,
    &bspc_key_override,
    NULL
};

bool is_alt_tab_active = false;
bool is_alt_sft_tab_active = false;
bool is_ctl_tab_active = false;
bool is_ctl_sft_tab_active = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    if (is_alt_tab_active) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
    if (is_alt_sft_tab_active) {
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
        is_alt_sft_tab_active = false;
    }
    if (is_ctl_tab_active) {
        unregister_code(KC_LCTL);
        is_ctl_tab_active = false;
    }
    if (is_ctl_sft_tab_active) {
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        is_ctl_sft_tab_active = false;
    }
    return state;
}

enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    NAME,
    BUNNY,
    THUMBSUP,
    ALT_TAB,
    ALT_SFT_TAB,
    CTL_TAB,
    CTL_SFT_TAB,
    TOGGLE_JP,
    TOGGLE_EN,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // custom strings
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
        case BUNNY:
            if (record->event.pressed) {
                send_string(BUNNY_ASCII);
            }
            return false;
        case THUMBSUP:
            if (record->event.pressed) {
                send_string(THUMBSUP_ASCII);
            }
            return false;

        // custom alt-tab, ctl-tab but with layer key instead
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        case ALT_SFT_TAB:
            if (record->event.pressed) {
                if (!is_alt_sft_tab_active) {
                    is_alt_sft_tab_active = true;
                    register_code(KC_LALT);
                    register_code(KC_LSFT);
                }
		// order is super important here; must register shift and then tab
                register_code(KC_LSFT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_TAB);
            }
            return false;
        case CTL_TAB:
            if (record->event.pressed) {
                if (!is_ctl_tab_active) {
                    is_ctl_tab_active = true;
                    register_code(KC_LCTL);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        case CTL_SFT_TAB:
            if (record->event.pressed) {
                if (!is_ctl_sft_tab_active) {
                    is_ctl_sft_tab_active = true;
                    register_code(KC_LCTL);
                    register_code(KC_LSFT);
                }
		// order is super important here; must register shift and then tab
                register_code(KC_LSFT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_TAB);
            }
            return false;

        // custom keys for toggling lang
        case TOGGLE_JP:
            if (record->event.pressed) {
                switch (detected_host_os()) {
                  case OS_MACOS:
                      // JIS_HENKAN
                      tap_code(KC_INT4);
                      break;
                  case OS_IOS:
                  case OS_WINDOWS:
                      // HANGUL/ENG
                      tap_code(KC_LNG1);
                      break;
                  case OS_LINUX:
                      // JIS_HENKAN
                      tap_code(KC_INT4);
                      break;
                  default:
                      // HANGUL/ENG
                      tap_code(KC_LNG1);
                      break;
                }
            }
            return false;
        case TOGGLE_EN:
            if (record->event.pressed) {
                switch (detected_host_os()) {
                    case OS_MACOS:
                        // JIS_MUHENKAN
                        tap_code(KC_INT5);
                        break;
                    case OS_IOS:
                    case OS_WINDOWS:
                        // HANJA
                        tap_code(KC_LNG2);
                        break;
                    case OS_LINUX:
                        // JIS_MUHENKAN
                        tap_code(KC_INT5);
                        break;
                    default:
                        // HANJA
                        tap_code(KC_LNG2);
                        break;
                  }
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
#define S_LT4 LT(4, KC_S)

#define TAB_RCTL MT(MOD_RCTL, KC_TAB)
#define SPC_RSFT MT(MOD_RSFT, KC_SPC)
#define ENT_L1 LT(1, KC_ENT)
#define ESC_L2 LT(2, KC_ESC) // might do backspace

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
      KC_A         , S_LT4        , D_LGUI       , F_LALT       , KC_G         ,                               KC_H         , J_RALT       , K_RGUI       , L_LT3        , KC_BSPC      ,
      KC_Z         , KC_X         , KC_C         , KC_V         , KC_B         ,                               KC_N         , KC_M         , KC_COMM      , KC_DOT       , TOGGLE_EN    ,
      _______      , _______      , _______      , _______      , ENT_L1       , ESC_L2       , TAB_RCTL     , SPC_RSFT     , _______      , _______      , _______      , _______
  ),

  [1] = LAYOUT_universal(
      KC_CIRC      , KC_LBRC      , KC_RBRC      , KC_DLR       , KC_PERC      ,                               KC_AT        , KC_PIPE      , KC_BSLS      , KC_GRV       , KC_SCLN      ,
      KC_MINS      , KC_LPRN      , KC_RPRN      , KC_UNDS      , KC_ASTR      ,                               KC_HASH      , KC_DQT       , KC_QUOT      , KC_EQL       , KC_COLN      ,
      KC_LABK      , KC_LCBR      , KC_RCBR      , KC_RABK      , KC_AMPR      ,                               KC_QUES      , KC_EXLM      , KC_PLUS      , KC_SLSH      , KC_TILD      ,
      _______      , _______      , _______      , _______      , ENT_L1       , ESC_L2       , TAB_RCTL     , SPC_RSFT     , _______      , _______      , _______      , _______
  ),

  [2] = LAYOUT_universal(
      _______      , KC_1         , KC_2         , KC_3         , _______      ,                               ALT_SFT_TAB  , ALT_TAB      , CTL_SFT_TAB  , CTL_TAB      , KC_DEL       ,
      KC_0         , KC_4         , KC_5         , KC_6         , CH_LANG      ,                               KC_LEFT      , KC_DOWN      , KC_UP        , KC_RIGHT     , KC_BSPC      ,
      _______      , KC_7         , KC_8         , KC_9         , _______      ,                               SCR_LEFT     , SCR_DOWN     , SCR_UP       , SCR_RGHT     , TOGGLE_JP    ,
      _______      , _______      , _______      , _______      , ENT_L1       , ESC_L2       , TAB_RCTL     , SPC_RSFT     , _______      , _______      , _______      , _______
  ),

  [3] = LAYOUT_universal(
      _______      , DT_DOWN      , DT_UP        , DT_PRNT      , _______      ,                               _______      , _______      , _______      , _______      , _______      ,
      KC_MUTE      , KC_VOLD      , KC_VOLU      , SCRN_SHT     , _______      ,                               _______      , _______      , _______      , _______      , _______      ,
      _______      , KC_BRID      , KC_BRIU      , WIN_SEC      , _______      ,                               _______      , _______      , _______      , _______      , _______      ,
      _______      , _______      , _______      , _______      , ENT_L1       , ESC_L2       , TAB_RCTL     , SPC_RSFT     , _______      , _______      , _______      , _______
  ),

  [4] = LAYOUT_universal(
      _______      , _______      , _______      , _______      , _______      ,                               _______      , BUNNY        , THUMBSUP     , _______      , _______      ,
      _______      , _______      , _______      , _______      , _______      ,                               _______      , EMAIL        , NAME         , _______      , _______      ,
      _______      , _______      , _______      , _______      , _______      ,                               _______      , _______      , _______      , _______      , _______      ,
      _______      , _______      , _______      , _______      , ENT_L1       , ESC_L2       , TAB_RCTL     , SPC_RSFT     , _______      , _______      , _______      , _______
  ),


};
// clang-format on


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
  BTN4,
  BTN5,
  TAB,
  ENTER,
  DELETE,
};
const uint16_t PROGMEM btn1[] = {K_RGUI, L_LT3, COMBO_END};
const uint16_t PROGMEM btn2[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM btn4[] = {J_RALT, K_RGUI, COMBO_END};
const uint16_t PROGMEM btn5[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM tab[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM enter[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM delete[] = {KC_X, KC_C, COMBO_END};

combo_t key_combos[] = {
  [BTN1] = COMBO(btn1, KC_BTN1),
  [BTN2] = COMBO(btn2, KC_BTN2),
  [BTN4] = COMBO(btn4, KC_BTN4),
  [BTN5] = COMBO(btn5, KC_BTN5),
  [TAB] = COMBO(tab, KC_TAB),
  [ENTER] = COMBO(enter, KC_ENT),
  [DELETE] = COMBO(delete, KC_DEL),
};
#endif

// per key tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ENT_L1:
            return g_tapping_term - 150;
        case ESC_L2:
            return g_tapping_term - 150;
        case TAB_RCTL:
            return g_tapping_term - 150;
        case SPC_RSFT:
            return g_tapping_term - 150;
        default:
            return g_tapping_term;
    }
}



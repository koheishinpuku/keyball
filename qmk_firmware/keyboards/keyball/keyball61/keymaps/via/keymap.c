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
  [0] = LAYOUT_universal(
    KC_GRV   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPC ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LBRC  ,              KC_RBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_EQL  ,
    KC_LSFT  , KC_LCTL  , KC_LALT  , KC_LGUI  , MO(1)    ,KC_SPC    , G(KC_SPC),              KC_ENT , MO(2)    ,_______   ,_______   , _______  , KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    KC_ESC  , S(KC_1)  , S(KC_2)  , S(KC_3)         , S(KC_4)      , S(KC_5)       ,                                   S(KC_6)  ,S(KC_QUOT), S(KC_8)    , S(KC_9)   , S(KC_9)    , KC_DEL     ,
    KC_TAB  , S(KC_Q)  , S(KC_W)  , LCTL(S(KC_TAB)) , RCTL(KC_UP)  , LCTL(KC_TAB)  ,                                   S(KC_Y)  , S(KC_U)  , S(KC_I)    , S(KC_O)   , G(KC_P)    , S(KC_INT3) ,
    KC_TAB  , S(KC_A)  , S(KC_S)  , RCTL(KC_LEFT)   , G(KC_F)      , RCTL(KC_RGHT) ,                                   S(KC_H)   , S(KC_J)  , S(KC_K)  , S(KC_L)    , KC_QUOT   , S(KC_2)     ,
    KC_LSFT , G(KC_Z)  , G(KC_X)  , G(KC_C)         , G(KC_V)      , G(KC_B)       , S(KC_LBRC) ,          S(KC_RBRC), S(KC_N)  , S(KC_M)  , S(KC_COMM) , S(KC_DOT) , S(KC_SLSH) , S(KC_RSFT) ,
    KC_LSFT , KC_LCTL  ,KC_LALT   , KC_LGUI         , _______      , _______       , _______    ,          _______   , _______  , _______  , S(KC_RGUI) , _______   , S(KC_RALT) , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , S(G(KC_F4)), S(G(KC_F5)) ,                                 KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , _______  , KC_7     , KC_8     , KC_9       , _______     ,                                 _______  , KC_LEFT  , KC_UP    , KC_RGHT  , G(KC_P)  , KC_F12   ,
    _______  , _______  , KC_4     , KC_5     , KC_6       , S(KC_SCLN)  ,                                 KC_PGUP  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_BTN3  , _______  ,
    KC_LSFT  , _______  , KC_1     , KC_2     , KC_3       , S(KC_MINS)  , S(KC_8)  ,            S(KC_9) , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    KC_LSFT  , KC_LCTL  , KC_LALT  , KC_LGUI  , _______    , _______     , _______  ,             KC_DEL , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EEP_RST  ,            EEP_RST  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    RESET    , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , RESET
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F12   , KC_F11   ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , KC_LEFT  , KC_UP    , KC_RGHT  , G(KC_P)  , _______   ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , G(KC_Z)  , G(KC_X)  , G(KC_C)  , G(KC_V)  , G(KC_B)  ,S(KC_LBRC) ,            _______ , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,             _______ , _______  , _______  , _______  , _______  , _______  , G(KC_R)
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 3:
            // Auto enable scroll mode when the highest layer is 3
            // remove_auto_mouse_target must be called to adjust state *before* setting enable
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

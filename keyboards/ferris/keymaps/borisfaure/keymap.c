/*
Copyright 2021 Boris Faure

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include QMK_KEYBOARD_H
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif
#include "keycodes.h"
#include "print.h"

enum ferris_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _NUMBERS,
    _MISC,
    _TMUX,
};

// clang-format off
/**
  [VOID] = LAYOUT(
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _______ , _______ , _______ , _______ , _______     ,     _______ , _______ , _______ , _______ , _______ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _______ , _______ , _______ , _______ , _______     ,     _______ , _______ , _______ , _______ , _______ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _______ , _______ , _______ , _______ , _______     ,     _______ , _______ , _______ , _______ , _______ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
                                 _______ , _______     ,     _______ , _______
                              //---------+---------+---+---+---------+---------//
  ),
**/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   ___Q___ , _W_GUI_ , ___E___ , ___R___ , _T_MISC     ,     _Y_MISC , ___U___ , ___I___ , _O_GUI_ , ___P___ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _A_CTL_ , ___S___ , ___D___ , _F_TMUX , ___G___     ,     ___H___ , ___J___ , ___K___ , ___L___ , _SC_CTR ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   ESC_LSH , _X_ALT_ , ___C___ , ___V___ , _B_NUM_     ,     _N_NUM_ , ___M___ , _COMMA_ , DOT_ALT , SLS_RSH ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
                                 TAB_LWR , _SPACE_     ,     _ENTER_ , _BS_RSE
                              //---------+---------+---+---+---------+---------//
),
[_LOWER] = LAYOUT(
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _EXCLM_ , _HASH__ , _DOLLR_ , _LPARN_ , _RPARN_     ,     _CIRCF_ , _AMPRS_ , _SH_INS , _ASTER_ , _TILDE_ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _EQUAL_ , _MINUS_ , _GRAVE_ , _LCBRC_ , _RCBRC_     ,     _LEFT__ , _PG_DN_ , _PG_UP_ , _RIGHT_ , _BSLSH_ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   __AT___ , _AMPRS_ , _PERCT_ , _LBRAC_ , _RBRAC_     ,     _______ , _______ , _______ , _SQUOT_ , _DQUOT_ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
                                 _______ , _RALT__     ,     _______ , __DEL__
                              //---------+---------+---+---+---------+---------//
),
[_RAISE] = LAYOUT( \
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _______ , _______ , _E_ACU_ , _E_CIR_ , _E_GRV_     ,     ___Z___ , _U_GRV_ , _I_CIR_ , _O_CIR_ , _PRTSCR ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _A_GRV_ , _UNDRS_ , _PLUS__ , _AMPRS_ , _PIPE__     ,     _LEFT__ , _DOWN__ , __UP___ , _RIGHT_ , _PG_UP_ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _EURO__ , __OE___ , _C_CED_ , _CAP_LK , _NUM_LK     ,     __END__ , _MENU__ , _HOME__ , _______ , _PG_DN_ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
                                 __BSPC_ , _RALT__     ,     _______ , _______
                              //---------+---------+---+---+---------+---------//
),
[_NUMBERS] = LAYOUT( \
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   __DOT__ , ___4___ , ___5___ , ___6___ , _PLUS__     ,     _SLASH_ , __F1___ , __F2___ , __F3___ , __F4___ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   ___0___ , ___1___ , ___2___ , ___3___ , _MINUS_     ,     _ASTER_ , __F5___ , __F6___ , __F7___ , __F8___ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _COMMA_ , ___7___ , ___8___ , ___9___ , _N_UNLK     ,     _______ , __F9___ , __F10__ , __F11__ , __F12__ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
                                 TAB_LWR , _SPACE_     ,     _ENTER_ , _BS_RSE
                              //---------+---------+---+---+---------+---------//
),
  [_MISC] = LAYOUT( \
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _PAUSE_ , _______ , _______ , _______ , _______     ,     _M_UP_L , _M_UP_R , _______ , _______ , _M_W_UP ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _______ , _VOL_DN , _MUTE__ , _VOL_UP , _______     ,     _M_LEFT , _M_DOWN , _M_UP__ , _M_RIGH , _M_WCLK ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _RGB_TG , _NXT_TR , _PLAY__ , _PRV_TR , _______     ,     _M_DN_L , _M_DN_R , _______ , _______ , _M_W_DN ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
                                 _______ , _M_RCLK     ,     _M_CLK_ , _______
                              //---------+---------+---+---+---------+---------//
),
  [_TMUX] = LAYOUT( \
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _T_6___ , _T_7___ , _T_8___ , _T_9___ , _T_0___     ,     _T_1___ , _T_2___ , _T_3___ , _T_4___ , _T_5___ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _T_LAST , _______ , _______ , _______ , _______     ,     _T_PREV , _______ , _T_SCRL , _T_NEXT , _T_CMD_ ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
   _______ , _______ , _T_NEW_ , _T_COPY , _T_PAST     ,     _______ , _______ , _T_RNAM , _T_MOVE , _T_PAST ,
//---------+---------+---------+---------+---------         ---------+---------+---------+---------+---------//
                                 _______ , _______     ,     _______ , _______
                              //---------+---------+---+---+---------+---------//
),
};
// clang-format on

#define TMUX_PREFIX SS_DOWN(X_LCTL) "a" SS_UP(X_LCTL)
/// Handle events when on the TMUX layer
static bool process_record_tmux(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    switch (keycode) {
        case _T_NEW_:
            SEND_STRING(TMUX_PREFIX "c");
            return false;
        case _T_PREV:
            SEND_STRING(TMUX_PREFIX "p");
            return false;
        case _T_NEXT:
            SEND_STRING(TMUX_PREFIX "n");
            return false;
        case _T_LAST:
            SEND_STRING(TMUX_PREFIX "l");
            return false;
        case _T_CMD_:
            SEND_STRING(TMUX_PREFIX ":");
            return false;
        case _T_COPY:
            SEND_STRING(TMUX_PREFIX "[");
            return false;
        case _T_PAST:
            SEND_STRING(TMUX_PREFIX "]");
            return false;
        case _T_SCRL:
            SEND_STRING(TMUX_PREFIX SS_TAP(X_PGUP));
            return false;
        case _T_MOVE:
            SEND_STRING(TMUX_PREFIX ".");
            return false;
        case _T_RNAM:
            SEND_STRING(TMUX_PREFIX ",");
            return false;
        case _T_1___:
            SEND_STRING(TMUX_PREFIX "1");
            return false;
        case _T_2___:
            SEND_STRING(TMUX_PREFIX "2");
            return false;
        case _T_3___:
            SEND_STRING(TMUX_PREFIX "3");
            return false;
        case _T_4___:
            SEND_STRING(TMUX_PREFIX "4");
            return false;
        case _T_5___:
            SEND_STRING(TMUX_PREFIX "5");
            return false;
        case _T_6___:
            SEND_STRING(TMUX_PREFIX "6");
            return false;
        case _T_7___:
            SEND_STRING(TMUX_PREFIX "7");
            return false;
        case _T_8___:
            SEND_STRING(TMUX_PREFIX "8");
            return false;
        case _T_9___:
            SEND_STRING(TMUX_PREFIX "9");
            return false;
        case _T_0___:
            SEND_STRING(TMUX_PREFIX "0");
            return false;
    }
    return true;
}

#ifdef MOUSEKEY_ENABLE
// process diagonal mouse keys
static bool process_record_diagonal_mouse(uint16_t     keycode,
                                          keyrecord_t *record) {
    switch (keycode) {
        case _M_UP_L:
            if (record->event.pressed) {
                register_code(KC_MS_UP);
                register_code(KC_MS_LEFT);
            } else {
                unregister_code(KC_MS_UP);
                unregister_code(KC_MS_LEFT);
            }
            break;
        case _M_UP_R:
            if (record->event.pressed) {
                register_code(KC_MS_UP);
                register_code(KC_MS_RIGHT);
            } else {
                unregister_code(KC_MS_UP);
                unregister_code(KC_MS_RIGHT);
            }
            break;
        case _M_DN_L:
            if (record->event.pressed) {
                register_code(KC_MS_UP);
                register_code(KC_MS_RIGHT);
            } else {
                unregister_code(KC_MS_UP);
                unregister_code(KC_MS_RIGHT);
            }
            break;
        case _M_DN_R:
            if (record->event.pressed) {
                register_code(KC_MS_UP);
                register_code(KC_MS_RIGHT);
            } else {
                unregister_code(KC_MS_UP);
                unregister_code(KC_MS_RIGHT);
            }
            break;
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) == _TMUX) {
        return process_record_tmux(keycode, record);
    }
    if (host_keyboard_led_state().caps_lock) {
        // In case of caps lock, change behaviour of those keys
        switch (keycode) {
            case ESC_LSH:
                if (record->event.pressed) {
                    // unlock caps lock
                    SEND_STRING(SS_TAP(X_CAPSLOCK));
                }
                return false;
            case TAB_LWR:
                if (record->event.pressed) {
                    // send underscore
                    SEND_STRING("_");
                }
                return false;
        }
    }
#ifdef MOUSEKEY_ENABLE
    if (_M_UP_L <= keycode && keycode <= _M_DN_R) {
        return process_record_diagonal_mouse(keycode, record);
    }
#endif
    switch (keycode) {
        case _A_GRV_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "`A" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "`A" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "`a");
                }
            }
            return false;
        case _E_GRV_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "`E" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "`E" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "`e");
                }
            }
            return false;
        case _U_GRV_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "`U" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "`U" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "`u");
                }
            }
            return false;
        case _E_ACU_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "'E" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "'E" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "'e");
                }
            }
            return false;
        case _E_CIR_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "^E" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "^E" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "^e");
                }
            }
            return false;
        case _I_CIR_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "^I" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "^I" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "^i");
                }
            }
            return false;
        case _O_CIR_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "^O" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "^O" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "^o");
                }
            }
            return false;
        case _C_CED_:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) ",C" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) ",C" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) ",c");
                }
            }
            return false;
        case __OE___:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING(SS_UP(X_LSFT)
                                    SS_TAP(X_RALT) "OE" SS_DOWN(X_LSFT));
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(SS_UP(X_RSFT)
                                    SS_TAP(X_RALT) "OE" SS_DOWN(X_RSFT));
                } else {
                    SEND_STRING(SS_TAP(X_RALT) "oe");
                }
            }
            return false;
        case _EURO__:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_RALT) "=E");
            }
            return false;
    }
    return true;
}

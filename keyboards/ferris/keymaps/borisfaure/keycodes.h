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

#define ___A___ KC_A
#define ___B___ KC_B
#define ___C___ KC_C
#define ___D___ KC_D
#define ___E___ KC_E
#define ___F___ KC_F
#define ___G___ KC_G
#define ___H___ KC_H
#define ___I___ KC_I
#define ___J___ KC_J
#define ___K___ KC_K
#define ___L___ KC_L
#define ___M___ KC_M
#define ___N___ KC_N
#define ___O___ KC_O
#define ___P___ KC_P
#define ___Q___ KC_Q
#define ___R___ KC_R
#define ___S___ KC_S
#define ___T___ KC_T
#define ___U___ KC_U
#define ___V___ KC_V
#define ___W___ KC_W
#define ___X___ KC_X
#define ___Y___ KC_Y
#define ___Z___ KC_Z

#define ___0___ KC_0
#define ___1___ KC_1
#define ___2___ KC_2
#define ___3___ KC_3
#define ___4___ KC_4
#define ___5___ KC_5
#define ___6___ KC_6
#define ___7___ KC_7
#define ___8___ KC_8
#define ___9___ KC_9

#define _LPARN_ KC_LEFT_PAREN
#define _RPARN_ KC_RIGHT_PAREN
#define _LCBRC_ KC_LEFT_CURLY_BRACE
#define _RCBRC_ KC_RIGHT_CURLY_BRACE
#define _LBRAC_ KC_LBRACKET
#define _RBRAC_ KC_RBRACKET
#define _LABRC_ KC_LEFT_ANGLE_BRACKET
#define _RABRC_ KC_RIGHT_ANGLE_BRACKET

#define __DOT__ KC_DOT
#define _COMMA_ KC_COMMA
#define _SQUOT_ KC_QUOTE
#define _DQUOT_ KC_DOUBLE_QUOTE
#define _COLON_ KC_COLON
#define _SCOLN_ KC_SCOLON
#define _TILDE_ KC_TILD
#define _GRAVE_ KC_GRAVE
#define _UNDRS_ KC_UNDERSCORE
#define _EQUAL_ KC_EQUAL
#define _MINUS_ KC_MINUS
#define _PLUS__ KC_PLUS
#define _ASTER_ KC_ASTERISK
#define _HASH__ KC_HASH
#define _DOLLR_ KC_DOLLAR
#define _SLASH_ KC_SLASH
#define _BSLSH_ KC_BSLASH
#define _PERCT_ KC_PERCENT
#define _AMPRS_ KC_AMPERSAND
#define _QUEST_ KC_QUESTION
#define _EXCLM_ KC_EXCLAIM
#define _CIRCF_ KC_CIRCUMFLEX
#define _PIPE__ KC_PIPE
#define __AT___ KC_AT

#define _SPACE_ KC_SPACE
#define _ENTER_ KC_ENTER

#define _LEFT__ KC_LEFT
#define __UP___ KC_UP
#define _DOWN__ KC_DOWN
#define _RIGHT_ KC_RIGHT

#define _PG_DN_ KC_PGDN
#define _PG_UP_ KC_PGUP

#define __ESC__ KC_ESC
#define __TAB__ KC_TAB
#define __END__ KC_END
#define _MENU__ KC_MENU
#define _HOME__ KC_HOME
#define __DEL__ KC_DEL
#define __BSPC_ KC_BSPC
#define _PRTSCR KC_PSCR
#define _PAUSE_ KC_PAUSE
#define _RALT__ KC_RALT

#define __F1___ KC_F1
#define __F2___ KC_F2
#define __F3___ KC_F3
#define __F4___ KC_F4
#define __F5___ KC_F5
#define __F6___ KC_F6
#define __F7___ KC_F7
#define __F8___ KC_F8
#define __F9___ KC_F9
#define __F10__ KC_F10
#define __F11__ KC_F11
#define __F12__ KC_F12

/* QWERTY right hand */
#define _SC_CTR RCTL_T(KC_SCOLON)
#define SLS_RSH RSFT_T(KC_SLSH)
#define _O_GUI_ RGUI_T(KC_O)
#define DOT_ALT LALT_T(KC_DOT)
#define _BS_RSE LT(_RAISE, KC_BSPC)
#define _N_NUM_ LT(_NUMBERS, KC_N)
#define _Y_MISC LT(_MISC, KC_Y)

/* QWERTY left hand */
#define _A_CTL_ LCTL_T(KC_A)
#define ESC_LSH LSFT_T(KC_ESC)
#define _W_GUI_ LGUI_T(KC_W)
#define _X_ALT_ LALT_T(KC_X)
#define TAB_LWR LT(_LOWER, KC_TAB)
#define _B_NUM_ LT(_NUMBERS, KC_B)
#define _T_MISC LT(_MISC, KC_T)
#define _F_TMUX LT(_TMUX, KC_F)

#define _CAP_LK KC_CAPSLOCK

#define _NUM_LK DF(_NUMBERS)
#define _N_UNLK DF(_QWERTY)

/* MEDIA / VOLUME */
#define _VOL_DN KC_AUDIO_VOL_DOWN
#define _VOL_UP KC_AUDIO_VOL_UP
#define _MUTE__ KC_AUDIO_MUTE
#define _PLAY__ KC_MEDIA_PLAY_PAUSE
#define _NXT_TR KC_MEDIA_NEXT_TRACK
#define _PRV_TR KC_MEDIA_PREV_TRACK

#define _RGB_TG RGB_TOG

#define _RESET_ RESET
/* LOWER */
#define _SH_INS S(KC_INS)

/* MOUSE */
#define _M_RCLK KC_MS_BTN3
#define _M_CLK_ KC_MS_BTN1
#define _M_UP__ KC_MS_UP
#define _M_DOWN KC_MS_DOWN
#define _M_RIGH KC_MS_RIGHT
#define _M_LEFT KC_MS_LEFT
#define _M_WCLK KC_MS_BTN2
#define _M_W_UP KC_MS_WH_UP
#define _M_W_DN KC_MS_WH_DOWN

enum custom_keycodes {
    _A_GRV_ = SAFE_RANGE,  // à
    _E_GRV_,               // è
    _U_GRV_,               // ù
    _E_ACU_,               // é
    _E_CIR_,               // ê
    _I_CIR_,               // î
    _O_CIR_,               // ô
    _C_CED_,               // ç
    __OE___,               // œ
    _EURO__,               // €
    _T_NEW_,               // tmux new
    _T_PREV,               // tmux prev-window
    _T_NEXT,               // tmux next-window
    _T_LAST,               // tmux last-window
    _T_CMD_,               // tmux command
    _T_COPY,               // tmux copy-mode
    _T_PAST,               // tmux paste-buffer
    _T_SCRL,               // tmux scroll
    _T_MOVE,               // tmux move-window
    _T_RNAM,               // tmux rename-window
    _T_1___,               // tmux select-window -t 1
    _T_2___,               // tmux select-window -t 2
    _T_3___,               // tmux select-window -t 3
    _T_4___,               // tmux select-window -t 4
    _T_5___,               // tmux select-window -t 5
    _T_6___,               // tmux select-window -t 6
    _T_7___,               // tmux select-window -t 7
    _T_8___,               // tmux select-window -t 8
    _T_9___,               // tmux select-window -t 9
    _T_0___,               // tmux select-window -t 0
#ifdef MOUSEKEY_ENABLE
    _M_UP_L,  // mouse up left
    _M_UP_R,  // mouse up right
    _M_DN_L,  // mouse down left
    _M_DN_R,  // mouse down right
#endif
};

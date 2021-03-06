#include QMK_KEYBOARD_H
#ifdef PIMORONI_TRACKBALL_ENABLE
#    include "pimoroni_trackball.h"
#endif

#ifdef OLED_DRIVER_ENABLE
#    include <stdio.h>
#endif

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _MISC,
    _NUMBERS,
    _TMUX,
    _GAMING,
    _GAMING_MISC,
};

enum custom_keycodes {
    KC_MB1 = SAFE_RANGE,
    KC_MB2,
    KC_MB3,
    KC_AGRV,  // à
    KC_EGRV,  // è
    KC_UGRV,  // ù
    KC_EACU,  // é
    KC_ECIR,  // ê
    KC_ICIR,  // î
    KC_OCIR,  // ô
    KC_CCED,  // ç
    KC_OE,    // œ
    KC_EURO,  // €
    T_NEW,    // tmux new
    T_PREV,   // tmux prev-window
    T_NEXT,   // tmux next-window
    T_LAST,   // tmux last-window
    T_CMD,    // tmux command
    T_COPY,   // tmux copy-mode
    T_PASTE,  // tmux paste-buffer
    T_SCROL,  // tmux scroll
    T_MOVE,   // tmux move-window
    T_RENAM,  // tmux rename-window
    T_1,      // tmux select-window -t 1
    T_2,      // tmux select-window -t 2
    T_3,      // tmux select-window -t 3
    T_4,      // tmux select-window -t 4
    T_5,      // tmux select-window -t 5
    T_6,      // tmux select-window -t 6
    T_7,      // tmux select-window -t 7
    T_8,      // tmux select-window -t 8
    T_9,      // tmux select-window -t 9
    T_0,      // tmux select-window -t 0
};

uint8_t  MOUSE_BUTTONS;
uint16_t trackball_led_time;

// clang-format off
/*
 * Grid
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |      | /      /        \      \  |      |      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
#if 0
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, XXXXXXX, \
  XXXXXXX, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, XXXXXXX, \
  XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX,   XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, \
                    XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,   _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCtrl |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift| Esc  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |  [  | LGUI | LAlt |LOWER | /Space /        \Enter \  |RAISE | RAlt | MISC |   ]  |
 *             `----------------------------------'          '------------------------------------'
 */

/* right hand */
#define KC_CTRQ RCTL_T(KC_QUOT)
#define KC_CTRP RCTL_T(KC_P)
#define KC_STRS RSFT_T(KC_SLSH)
#define KC_GUIO RGUI_T(KC_O)
#define ALT_DOT LALT_T(KC_DOT)
#define KC_RSE LT(_RAISE, KC_BSPC)
#define NUM_N LT(_NUMBERS, KC_N)
#define MISC_Y LT(_MISC, KC_Y)

/* left hand */
#define KC_CTLQ LCTL_T(KC_Q)
#define LSH_ESC LSFT_T(KC_ESC)
#define KC_GUIW LGUI_T(KC_W)
#define ALT_X LALT_T(KC_X)
#define KC_LWR LT(_LOWER, KC_TAB)
#define NUM_B LT(_NUMBERS, KC_B)
#define MISC_T LT(_MISC, KC_T)
#define TMUX_F LT(_TMUX, KC_F)

[_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,    KC_2,    KC_3,  KC_4,   KC_5,                           KC_6,  KC_7, KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_CTLQ, KC_GUIW, KC_E,  KC_R,   MISC_T,                       MISC_Y,  KC_U, KC_I,    KC_GUIO, KC_CTRP, KC_BSLS, \
  KC_LCTRL, KC_A,    KC_S,    KC_D,  TMUX_F, KC_G,                           KC_H,  KC_J, KC_K,    KC_L,    KC_SCLN, KC_CTRQ, \
  KC_LSFT,  LSH_ESC, ALT_X,   KC_C,  KC_V,   NUM_B, KC_MUTE,       XXXXXXX, NUM_N,  KC_M, KC_COMM, ALT_DOT, KC_STRS, KC_RSFT, \
                 KC_LBRC ,KC_LGUI, KC_LALT,  KC_LWR, KC_SPC,      KC_ENT, KC_RSE, KC_RALT, MO(_MISC), KC_RBRC \
),
/* LOWER / Symbols
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |  !   |   #  |  $   |   (  |   )  |                    |   ^  |  &   | S-Ins|   *  |  ~   | PgUp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ∨  |  =   |   -  |  `   |   {  |   }  |-------.    ,-------|   ←  | PgDn | PgUp |   →  |  \   | PgDn |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |   ∨  |  @   |   &  |   %  |   [  |   ]  |-------|    |-------|  End | Menu | Home |   '  |  "   |   ∨  |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |      | / RAlt /        \Enter \  |MISC_DEL|     |     |      |
 *             `----------------------------------'          '------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,     KC_F9,    KC_F10,  KC_DEL, \
  KC_GRV,   KC_EXLM, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN,                     KC_CIRC, KC_AMPR, S(KC_INS), KC_ASTR,  KC_TILD, KC_PGUP, \
  _______,  KC_EQL,  KC_MINS, KC_GRV,  KC_LCBR, KC_RCBR,                     KC_LEFT, KC_PGDN, KC_PGUP,   KC_RIGHT, KC_BSLS, KC_PGDN, \
  _______,  KC_AT,   KC_AMPR, KC_PERC, KC_LBRC, KC_RBRC, XXXXXXX,   XXXXXXX, KC_END,  KC_MENU, KC_HOME,   KC_QUOT,  KC_DQUO, _______, \
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT,  KC_ENT, KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX\
),
/* RAISE / French
 * ,----------------------------------------.                     ,-----------------------------------------.
 * | Pause|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |  ESC |  #   |   é  |   ê  |   è  |                    |  Z   |  ù   |  î   |  ô   |PrtScr| PgUp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ∨  |  à   |   _  |   +  |   &  |   |  |-------.    ,-------|   ←  |  ↓   |   ↑  |   →  | PgUp | PgDn |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |   ∨  |  €   |  œ   |   ç  |   [  |   ]  |-------|    |-------| End  | Menu | Home | Pause| PgDn |   ∨  |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |  DEL | / RAlt /        \Enter \  |RAISE |      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_PAUSE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6, KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_DEL, \
  KC_GRV,   KC_ESC,  KC_HASH, KC_EACU, KC_ECIR, KC_EGRV,                        KC_Z, KC_UGRV, KC_ICIR, KC_OCIR,  KC_PSCR, KC_PGUP, \
  _______,  KC_AGRV, KC_UNDS, KC_PLUS, KC_AMPR, KC_PIPE,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_PGUP, KC_PGDN, \
  _______,  KC_EURO,   KC_OE, KC_CCED, KC_LBRC, KC_RBRC, XXXXXXX,   XXXXXXX,  KC_END, KC_MENU, KC_HOME, _______,  KC_PGDN, _______, \
                     XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  KC_RALT,   KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
),
/* MISC (Media/Mouse)
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |GAMING|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |Reset |      |      |      |      |                    |      |      |M_WH_U|      |M_ACL2|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | VOL_U| MUTE | VOL_D|      |-------.    ,-------|      |M_BTN1|M_BTN2|M_BTN3|M_ACL1|      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | M_PRV| PLAY | M_NXT|      |-------|    |-------|      |      |M_WH_D|      |M_ACL0|      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      | TAB  | / SPC  /        \ MB1  \  | BS   |      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
#define GAMING  DF(_GAMING)
  [_MISC] = LAYOUT( \
   GAMING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, KC_WH_U, XXXXXXX, KC_ACL2, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX,                     XXXXXXX,  KC_MB1,  KC_MB3,  KC_MB2, KC_ACL1, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, XXXXXXX, KC_ACL0, XXXXXXX, \
                    _______, _______, _______, KC_TAB,  KC_SPC,    KC_MB1,  KC_BSPC, _______, _______, _______\
  ),
/* Numbers / Fx keys
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  .   |  4   |   5  |  6   |   +  |                    |  /   |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  0   |  1   |   2  |  3   |   -  |-------.    ,-------|  *   |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  ,   |  7   |   8  |  9   |      |-------|    |-------|      |  F9  | F10  | F11  | F12  |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |      | /      /        \      \  |      |      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
  [_NUMBERS] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX,  KC_DOT,    KC_4,    KC_5,    KC_6, KC_PLUS,                     KC_STRS,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX, \
  XXXXXXX,    KC_0,    KC_1,    KC_2,    KC_3, KC_MINS,                     KC_ASTR,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX, \
  XXXXXXX, KC_COMM,    KC_7,    KC_8,    KC_9, KC_EQL,  XXXXXXX,   XXXXXXX,  KC_EQL,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, \
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______\
  ),
/*
 * TMUX
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  6   |  7   |  8   |  9   |  0   |                    |  1   |  2   |  3   |  4   |  5   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Last |      |      |      |      |-------.    ,-------| Prev |      |Scroll| Next | Cmd  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      | New  | Copy |Paste |-------|    |-------|      |      |Rename| Move | Paste|      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |      | /      /        \      \  |      |      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
  [_TMUX] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX,     T_6,     T_7,     T_8,     T_9,     T_0,                         T_1,     T_2,     T_3,     T_4,     T_5, XXXXXXX, \
  XXXXXXX,  T_LAST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      T_PREV, XXXXXXX, T_SCROL,  T_NEXT,   T_CMD, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX,   T_NEW, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, T_RENAM,  T_MOVE, T_PASTE, XXXXXXX, \
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
/*
 * GAMING QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCtrl |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |  [  | LGUI | LAlt |LOWER | /Space /        \Enter \  |RAISE | RAlt | MISC |   ]  |
 *             `----------------------------------'          '------------------------------------'
 */

/* right hand */
#define G_MISC  MO(_GAMING_MISC)

[_GAMING] = LAYOUT( \
  KC_ESC,   KC_1, KC_2, KC_3,  KC_4, KC_5,                         KC_6,  KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q, KC_W, KC_E,  KC_R, KC_T,                         KC_Y,  KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_LCTRL, KC_A, KC_S, KC_D,  KC_F, KC_G,                         KC_H,  KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z, KC_X, KC_C,  KC_V, KC_B, KC_MUTE,      XXXXXXX,  KC_N,  KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
         KC_LBRC ,KC_LGUI, KC_LALT, G_MISC, KC_SPC,      KC_ENT, G_MISC, KC_RALT, MO(_MISC), KC_RBRC \
),
/* GAMING MISC
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |      |      |      |      |      |                    |      |      |      |      |      | PgUp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  =   |   _  |   +  |   -  |      |-------.    ,-------|   ←  |  ↓   |   ↑  |   →  |      | PgDn |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|  End | Menu | Home |      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |QWERTY| / RAlt /        \Enter \  |QWERTY|      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
#define TO_QWER  DF(_QWERTY)
[_GAMING_MISC] = LAYOUT( \
  KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11, \
  KC_GRV,   _______, _______, _______, _______, _______,                     _______, _______, _______, _______,  _______, KC_F12, \
  _______,  KC_EQL,  KC_UNDS, KC_PLUS, KC_MINS, _______,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, KC_PGUP, \
  _______,  _______, _______, _______, _______, _______, XXXXXXX,   XXXXXXX, KC_END,  KC_MENU, KC_HOME, _______,  _______, KC_PGDN, \
                     _______, _______, _______, TO_QWER, _______,   _______, TO_QWER, _______, _______, _______\
),
};
// clang-format on

#ifdef PIMORONI_TRACKBALL_ENABLE
void pointing_device_task() {
    report_mouse_t mouse_report = pointing_device_get_report();

    trackball_set_timed_rgbw(0, 0, 0, 80);

    if (!is_keyboard_left() || !is_keyboard_master()) {
        process_mouse(&mouse_report);
    }

    mouse_report.buttons = MOUSE_BUTTONS;

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            trackball_set_timed_rgbw(0, 0, 0, 80);
            break;
        case _RAISE:
            trackball_set_rgbw(153, 113, 0, 0);
            break;
        case _LOWER:
            trackball_set_rgbw(0, 153, 95, 0);
            break;
        case _MISC:
            trackball_set_rgbw(153, 0, 110, 0);
            break;
        case _NUMBERS:
            trackball_set_rgbw(255, 0, 0, 0);
            break;
        default:
            trackball_set_timed_rgbw(0, 0, 0, 80);
    }

    if (layer_state_is(_LOWER) || layer_state_is(_RAISE)) {
        trackball_set_scrolling(true);
    } else {
        trackball_set_scrolling(false);
    }

    pointing_device_set_report(mouse_report);
    pointing_device_send();
}

#endif

#ifdef OLED_DRIVER_ENABLE

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE "), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Qwrt"), false);
            break;
        case _GAMING:
            oled_write_P(PSTR("Game"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _MISC:
            oled_write_P(PSTR("Misc\n"), false);
            break;
        case _NUMBERS:
            oled_write_P(PSTR("NumFx\n"), false);
            break;
        case _TMUX:
            oled_write_P(PSTR("Tmux\n"), false);
            break;
        case _GAMING:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _GAMING_MISC:
            oled_write_P(PSTR("Misc\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_task_user(void) { print_status_narrow(); }

#endif

#define TMUX_PREFIX SS_DOWN(X_LCTL) "a" SS_UP(X_LCTL)
/// Handle events when on the TMUX layer
static bool process_record_tmux(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    switch (keycode) {
        case T_NEW:
            SEND_STRING(TMUX_PREFIX "c");
            return false;
        case T_PREV:
            SEND_STRING(TMUX_PREFIX "p");
            return false;
        case T_NEXT:
            SEND_STRING(TMUX_PREFIX "n");
            return false;
        case T_LAST:
            SEND_STRING(TMUX_PREFIX "l");
            return false;
        case T_CMD:
            SEND_STRING(TMUX_PREFIX ":");
            return false;
        case T_COPY:
            SEND_STRING(TMUX_PREFIX "[");
            return false;
        case T_PASTE:
            SEND_STRING(TMUX_PREFIX "]");
            return false;
        case T_SCROL:
            SEND_STRING(TMUX_PREFIX SS_TAP(X_PGUP));
            return false;
        case T_MOVE:
            SEND_STRING(TMUX_PREFIX ".");
            return false;
        case T_RENAM:
            SEND_STRING(TMUX_PREFIX ",");
            return false;
        case T_1:
            SEND_STRING(TMUX_PREFIX "1");
            return false;
        case T_2:
            SEND_STRING(TMUX_PREFIX "2");
            return false;
        case T_3:
            SEND_STRING(TMUX_PREFIX "3");
            return false;
        case T_4:
            SEND_STRING(TMUX_PREFIX "4");
            return false;
        case T_5:
            SEND_STRING(TMUX_PREFIX "5");
            return false;
        case T_6:
            SEND_STRING(TMUX_PREFIX "6");
            return false;
        case T_7:
            SEND_STRING(TMUX_PREFIX "7");
            return false;
        case T_8:
            SEND_STRING(TMUX_PREFIX "8");
            return false;
        case T_9:
            SEND_STRING(TMUX_PREFIX "9");
            return false;
        case T_0:
            SEND_STRING(TMUX_PREFIX "0");
            return false;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) == _TMUX) {
        return process_record_tmux(keycode, record);
    }
    switch (keycode) {
        case KC_SPC:
            if (record->event.pressed && get_mods() & MOD_MASK_SHIFT) {
                clear_mods();
                register_code(KC_TAB);
                return false;
            }
            return true;
        case KC_AGRV:
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
        case KC_EGRV:
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
        case KC_UGRV:
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
        case KC_EACU:
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
        case KC_ECIR:
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
        case KC_ICIR:
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
        case KC_OCIR:
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
        case KC_CCED:
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
        case KC_OE:
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
        case KC_EURO:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_RALT) "=E");
            }
            return false;
        case KC_MB1:
            if (record->event.pressed) {
                MOUSE_BUTTONS |= (1 << 0);
            } else {
                MOUSE_BUTTONS &= ~(1 << 0);
            }
            return false;
        case KC_MB2:
            if (record->event.pressed) {
                MOUSE_BUTTONS |= (1 << 1);
            } else {
                MOUSE_BUTTONS &= ~(1 << 1);
            }
            return false;
        case KC_MB3:
            if (record->event.pressed) {
                MOUSE_BUTTONS |= (1 << 2);
            } else {
                MOUSE_BUTTONS &= ~(1 << 2);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
            }
            break;

        case _LOWER:
        case _RAISE:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_MPRV);
                } else {
                    tap_code(KC_MNXT);
                }
            }
            break;
    }
}

#endif

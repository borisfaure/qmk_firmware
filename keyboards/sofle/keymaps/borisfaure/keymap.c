#include QMK_KEYBOARD_H
#ifdef PIMORONI_TRACKBALL_ENABLE
#    include "pimoroni_trackball.h"
#endif

#ifdef OLED_DRIVER_ENABLE
#    include <stdio.h>

char wpm_str[4];
#endif

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _FN,
};

enum custom_keycodes {
    KC_LOWER = SAFE_RANGE,
    KC_RAISE,
    KC_FN,
    KC_AGRV,  // à
    KC_EGRV,  // è
    KC_UGRV,  // ù
    KC_EACU,  // é
    KC_ECIR,  // ê
    KC_ICIR,  // î
    KC_OCIR,  // ô
    KC_CCED,  // ç
    KC_MB1,
    KC_MB2,
    KC_MB3,
};

uint8_t  MOUSE_BUTTONS;
uint16_t trackball_led_timer;

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
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |  [  | LGUI | LAlt |LOWER | /Space /        \Enter \  |RAISE | RAlt | RCtrl|   ]  |
 *             `----------------------------------'          '------------------------------------'
 */

/* right hand */
#define KC_CTRQ RCTL_T(KC_QUOT)
#define KC_CTRS RCTL_T(KC_SCLN)
#define KC_STRS RSFT_T(KC_SLSH)
#define KC_GUIO RGUI_T(KC_O)
#define KC_RSE LT(_RAISE, KC_BSPC)

/* left hand */
#define KC_CTLA LCTL_T(KC_A)
#define KC_LSHZ LSFT_T(KC_Z)
#define KC_GUIW LGUI_T(KC_W)
#define KC_LWR LT(_LOWER, KC_TAB)

[_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,    KC_2,    KC_3,  KC_4,  KC_5,                         KC_6,  KC_7, KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,    KC_GUIW, KC_E,  KC_R,  KC_T,                         KC_Y,  KC_U, KC_I,    KC_GUIO, KC_P,    KC_BSLS, \
  KC_LCTRL, KC_CTLA, KC_S,    KC_D,  KC_F,  KC_G,                         KC_H,  KC_J, KC_K,    KC_L,    KC_CTRS, KC_CTRQ, \
  KC_LSFT,  KC_LSHZ, KC_X,    KC_C,  KC_V,  KC_B, KC_MUTE,       XXXXXXX, KC_N,  KC_M, KC_COMM, KC_DOT,  KC_STRS, KC_RSFT, \
                 KC_LBRC ,KC_LGUI, KC_LALT, KC_LWR, KC_SPC,      KC_ENT, KC_RSE, KC_RALT, KC_FN, KC_RBRC \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  | F11  | F12  |   é  |   ê  |   è  |                    |      | End  | S-Ins| Home |   -  | PgUp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ∨  |   =  |   -  |   +  |   {  |   }  |-------.    ,-------|   ←  | PgDn | PgUp |   →  |      | PgDn |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |   ∨  | Undo | Cut  | Copy | Paste|      |-------|    |-------|      | Menu |      |      |      |   ∨  |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |LOWER | /Space /        \ MB1  \  |      |      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,     KC_F9,    KC_F10,  KC_DEL, \
  KC_GRV,   KC_F11,  KC_F12,  KC_EACU, KC_ECIR, KC_EGRV,                      XXXXXXX, KC_END,  S(KC_INS), KC_HOME,  KC_MINS, KC_PGUP, \
  _______,  KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,                      KC_LEFT, KC_PGDN, KC_PGUP,   KC_RIGHT, XXXXXXX, KC_PGDN, \
  _______,  KC_UNDO, KC_CUT, KC_COPY,  KC_PASTE, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_MENU, XXXXXXX,   XXXXXXX,  XXXXXXX, _______, \
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,   KC_MB1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
),
/* RAISE / French
 * ,----------------------------------------.                     ,-----------------------------------------.
 * | Pause|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  | F11  | F12  |   é  |   ê  |   è  |                    |      |  ù   |  î   |  ô   |PrtScr| PgUp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ∨  |  à   |   _  |   +  |   {  |   }  |-------.    ,-------|   ←  |  ↓   |   ↑  |   →  |      | PgDn |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |   ∨  |      |      |   ç  |   [  |   ]  |-------|    |-------|      | Menu |      |      |      |   ∨  |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |      | /Space /        \Enter \  |RAISE |      |      |      |
 *             `----------------------------------'          '------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_PAUSE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_DEL, \
  KC_GRV,   KC_F11,  KC_F12,  KC_EACU, KC_ECIR, KC_EGRV,                     XXXXXXX, KC_UGRV, KC_ICIR, KC_OCIR,  KC_PSCR, KC_PGUP, \
  _______,  KC_AGRV, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, KC_PGDN, \
  _______,  XXXXXXX, XXXXXXX, KC_CCED, KC_LBRC, KC_RBRC, XXXXXXX,   XXXXXXX, XXXXXXX, KC_MENU, XXXXXXX, XXXXXXX,  XXXXXXX, _______, \
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,   KC_ENT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
),
/* FN
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      | F13  | F14  | F15  | F16  | F17  |                    | F18  | F19  | F20  | F21  | F22  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | F23  | F24  |      |      |      |                    |M_ACL2|      |M_WH_U|      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | VOL_U| MUTE | VOL_D|      |-------.    ,-------|M_ACL1|M_BTN1|M_BTN2|M_BTN3|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      | M_PRV| PLAY | M_NXT|      |-------|    |-------|M_ACL0|      |M_WH_D|      |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *             |     |      |      |      | /      /        \      \  |      |      |  FN  |      |
 *             `----------------------------------'          '------------------------------------'
 */
  [_FN] = LAYOUT( \
  XXXXXXX, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,                      KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  XXXXXXX, \
  XXXXXXX, KC_F23,  KC_F24,  XXXXXXX, XXXXXXX, XXXXXXX,                     KC_ACL2, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX,                     KC_ACL1, KC_MB1,  KC_MB3,  KC_MB2, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,   XXXXXXX, KC_ACL0, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, \
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, KC_FN, XXXXXXX\
  )
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
        case _FN:
            trackball_set_rgbw(153, 0, 110, 0);
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
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_task_user(void) { print_status_narrow(); }

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
        case KC_FN:
            if (record->event.pressed) {
                layer_on(_FN);
            } else {
                layer_off(_FN);
            }
            return false;
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

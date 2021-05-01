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

[_QWERTY] = LAYOUT( \
  KC_ESC,    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,  KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC, \
  KC_TAB,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,  KC_BSLS, \
  KC_LCTRL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,  KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LSFT,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    XXXXXXX, KC_N,  KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_LBRC ,KC_LGUI, KC_LALT, KC_LOWER, KC_SPC,     KC_ENT, KC_RAISE, KC_RALT, KC_FN, KC_RBRC \
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
                      XXXXXXX, XXXXXXX, XXXXXXX, KC_LOWER, KC_SPC,   KC_MB1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
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
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,   KC_ENT, KC_RAISE, XXXXXXX, XXXXXXX, XXXXXXX\
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

/*
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}
*/

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

/* Animation bit by j-inc
 * https://github.com/qmk/qmk_firmware/tree/master/keyboards/kyria/keymaps/j-inc
 */
// WPM-responsive animation stuff here
#    define IDLE_FRAMES 5
#    define IDLE_SPEED 40  // below this wpm value your animation will idle

// #define PREP_FRAMES 1 // uncomment if >1

#    define TAP_FRAMES 2
#    define TAP_SPEED \
        60  // above this wpm value typing animation to triggere

#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm,
// needs fixing
#    define ANIM_SIZE \
        320  // number of bytes in array, minimize for adequate firmware
             // size, max is 1024

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;
// uint8_t current_prep_frame = 0; // uncomment if PREP_FRAMES >1
uint8_t current_tap_frame = 0;

// Implementation credit j-inc(/James Incandenza), pixelbenny, and obosob.
// Bongo cat images changed and adapted for sofle keyboard oled size.
// Original gif can be found here:
// https://www.pixilart.com/art/bongo-cat-bd2a8e9323aa705
static void render_anim(void) {
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {{
        0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00,
        0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83,
        0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
        0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30,
        0xc0, 0x00, 0xe0, 0x1f, 0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04, 0x00, 0x00,
        0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0,
        0x3f, 0x03, 0x80, 0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05, 0x00, 0x00, 0xf0,
        0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80,
        0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38,
        0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1e, 0x01, 0x00,
        0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x0c, 0x30, 0xc0,
        0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x80, 0x00, 0x00, 0xe1,
        0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0e,
        0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0,
        0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19, 0x19, 0x41,
        0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09,
        0x70, 0x80, 0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02,
        0x01,
    }};
    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE]   = {
        {
            0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff,
            0xff, 0xff, 0x7c, 0x70, 0x40, 0x40, 0x61, 0x5e, 0x80, 0xc0,
            0xbc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87,
            0x00, 0x03, 0x0f, 0x3f, 0xf8, 0xf0, 0xf0, 0x20, 0x40, 0x80,
            0x80, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
            0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x87,
            0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80,
            0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0xf0, 0xcf,
            0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80,
            0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
            0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1e,
            0x01, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80,
            0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c,
            0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x07, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xf0, 0x0f, 0x80,
            0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x18, 0x60, 0x80, 0x00, 0x00, 0xe1, 0x1e, 0x01,
            0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0e, 0x0e,
            0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01,
            0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19,
            0x19, 0x41, 0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00,
            0xf0, 0x0f, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80, 0x00, 0x00,
            0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08,
            0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01,
        },
        {0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00,
         0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83,
         0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
         0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30,
         0xc0, 0x00, 0xe0, 0x1f, 0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04, 0x00, 0x00,
         0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0,
         0x3f, 0x03, 0x80, 0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
         0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05, 0x00, 0x00, 0xf0,
         0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80,
         0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38,
         0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe, 0xff, 0xff,
         0xff, 0xfc, 0xf0, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x0f, 0x3f, 0xff,
         0x03, 0x01, 0x03, 0x07, 0x18, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x80, 0x00, 0x0f, 0xf0,
         0x00, 0x00, 0x00, 0x00, 0x03, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x0e,
         0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf3,
         0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09,
         0x70, 0x80, 0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10,
         0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
         0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02,
         0x01},
    };

    // assumes 1 frame prep stage
    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            /*
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES-1)-current_idle_frame)],
            ANIM_SIZE);
            */
            oled_write_raw_P(idle[0], ANIM_SIZE);
        }
        /*
        if(get_current_wpm() >IDLE_SPEED && get_current_wpm() <TAP_SPEED){
            //
        oled_write_raw_P(prep[abs((PREP_FRAMES-1)-current_prep_frame)],
        ANIM_SIZE); // uncomment if IDLE_FRAMES >1 oled_write_raw_P(prep[0],
        ANIM_SIZE);  // remove if IDLE_FRAMES >1
        }*/
        if (get_current_wpm() >= TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)],
                             ANIM_SIZE);
        }
    }
    if (get_current_wpm() != 000) {
        oled_on();  // not essential but turns on animation OLED with any
                    // alpha keypress
        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_anim();
        oled_set_cursor(0, 12);
        sprintf(wpm_str, "WPM\n%03d", get_current_wpm());
        oled_write(wpm_str, false);
    }
}

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

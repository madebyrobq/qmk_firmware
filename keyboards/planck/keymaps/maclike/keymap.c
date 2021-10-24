// Maclike by Robert Quinn
//
// Maclike is a keymap that emulates the muscle memory and shortcuts from macOS in Windows.
//
// The modifiers on a Mac are | Ctrl | Alt | Cmd |
//
// On the Windows layer, Cmd becomes (right) Ctrl as well. 
//
// Some special cases are:
//     Task Switcher: Cmd + Tab emulates Alt + Tab
//     Home/End: Cmd + Left/Right does Home/End, which Windows does not have a shortcut for already
//     Move cursor by word: Alt + Left/Right emulates Ctrl + Left/Right
//     Ctrl + Backspace sends Delte instead 
//
// Maclike also intentionally disables tapping Alt to focus the menu bar in Windows.

// Compile: make planck/rev6:maclike

#include QMK_KEYBOARD_H
#include "muse.h"
#include "quantum.h"
#include "maclike.h"

//=============================//
//                             //
//                             //
//           Key maps          //
//                             //
//                             //
//=============================//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;'  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,!  |  .?  |  Up  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | CMD  | Raise| Space Space | Space/Raise | Cmd  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 *                   2u =      | Space       | Space/Raise |
 */
[DefaultLayer] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    ESC_FN,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    COLQUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    COMMEX,  DOTQUES, KC_UP,   KC_RSFT,
    KC_LCTL, KC_LALT, KC_LCMD, RAISE,   KC_SPC,  KC_SPC,  SPC_RSE, SPC_RSE, KC_RCMD, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Numpad and Symbols
 * ,-----------------------------------------------------------------------------------.
 * |   -  |   1  |   2  |   3  |   4  |   (  |   )  |   _  |   -  |   +  |   =  |  [v] |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  [v] |   4  |   5  |   6  |   0  |   {  |   }  |   |  |   /  |   *  |   =  |  [v] |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  [v] |   7  |   8  |   9  |   .  |   [  |   ]  |   &  |   <  |   >  |  [v] |  [v] |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  [v] | ALT. | CMD0 |   .  | Space/QMK   |  Space/QMK  |  [v] |  [v] |  [v] |  [v] |
 * `-----------------------------------------------------------------------------------'
 *                   2u =      | Space/QMK   |  Space/QMK  |
 */
[RaiseLayer] = LAYOUT_planck_grid(
    KC_MINS, KC_1,    KC_2,    KC_3,    KC_4,    KC_LPRN, KC_RPRN, KC_UNDS, KC_MINS, KC_PPLS, KC_EQL,  _______,
    _______, KC_4,    KC_5,    KC_6,    KC_0,    KC_LCBR, KC_RCBR, KC_PIPE, SLASHES, KC_PAST, KC_EQL,  _______,
    _______, KC_7,    KC_8,    KC_9,    KC_DOT,  KC_LBRC, KC_RBRC, KC_AMPR, KC_LT,   KC_GT,   _______, _______,
    _______, ALTDOT,  CMD0,    KC_DOT,  SPC_QMK, SPC_QMK, SPC_QMK, SPC_QMK, _______, _______, _______, _______
),

/* Fn
 * ,-----------------------------------------------------------------------------------.
 * |  `   |  F1  |  F2  |  F3  |      |      |      |      | ScBr-| ScBr+|WheelU| Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | [v]  |  F4  |  F5  |  F6  |      |      |      | Prev | Play | Next |WheelD| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | [v]  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Mute | Vol- | Vol+ |MouseU|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | [v]  | [v]  | [v]  | [v]  |  M1         |  M2         | [v]  |MouseL|MouseD|MouseR|
 * `-----------------------------------------------------------------------------------'
 *                   2u =      |  M1         |  M2         |
 */
[FnLayer] = LAYOUT_planck_grid(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRMD, KC_BRMU, KC_WH_U, KC_DEL,
    _______, KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, KC_WH_D, FNENT,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MS_U, _______,
    _______, _______, _______, _______, KC_BTN1, KC_BTN1, KC_BTN2, KC_BTN2, _______, KC_MS_L, KC_MS_D, KC_MS_R
),

// Keyboard functions
[QMKLayer] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX,   TOWIN, XXXXXXX,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,   TOMAC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, CK_TOGG, XXXXXXX, XXXXXXX,  MU_MOD,  MU_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
};
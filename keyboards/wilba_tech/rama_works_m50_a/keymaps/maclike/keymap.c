/* Copyright 2020 Jason Williams (Wilba)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



// qmk make wilba_tech/rama_works_m50_a:maclike

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "maclike.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------------------------------------------------------.
 * |      | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Esc/RS|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Ent/FN|
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,!  |  .?  |  Up  |Shift |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | CMD  |RAISE | S/R  |    Space    |  S/R | CMD  | Left | Down |Right |
 * `------------------------------------------------------------------------------------------'
 */
[DEFAULT_LAYER] = LAYOUT(
    KC_1,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_2,    ESC_RSE, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    COL_NAV, ENT_FN,
    KC_3,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
    KC_4,    KC_LCTL, KC_LALT, KC_LCMD, XXXXXXX, SPC_RSE,    KC_SPC,        SPC_RSE, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
),

[WIN_LAYER] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, WIN_CMD, _______, _______,     _______,      _______, _______, _______, _______, _______
),

/* Numpad and Symbols
 * 
 * Left handed numpad for Unity, Blender, etc to keep right hand on the mouse
 * Number order and placement similar to number row
 * Easy access to 0, ., = in the index columns
 * Operators in the middle
 * Symmetric symbol columns prioritizing parentheses in home row
 * 
 * ,------------------------------------------------------------------------------------------.
 * |      |  `   |   1  |   2  |   3  |   4  |   -  |   +  |      |   [  |   ]  |   '  | [v]  |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | [v]  |   4  |   5  |   6  |   0  |   /  |   *  |   =  |   (  |   )  | [v]  | [v]  |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | [v]  |   7  |   8  |   9  |   .  |   |  |   &  |      |   <  |   >  | [v]  | [v]  |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | [v]  |  [v] |  [v] |  [v] |      |             |      |  [v] |  [v] | [v]  | [v]  |
 * `------------------------------------------------------------------------------------------'
 */
[RAISE_LAYER] = LAYOUT(
    _______, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_MINS, KC_PPLS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT, _______,
    _______, KC_ESC,  KC_4,    KC_5,    KC_6,    KC_0,    KC_PSLS, KC_PAST, KC_EQL,  KC_LPRN, KC_RPRN, _______, KC_ENT,
    _______, _______, KC_7,    KC_8,    KC_9,    KC_DOT,  KC_PIPE, KC_AMPR, KC_EQL,  KC_LT,   KC_GT,   _______, _______,
    _______, _______, _______, _______, _______, SPC_QMK,      _______,     SPC_QMK, _______, _______, _______, _______
),

/* Fn
 * ,------------------------------------------------------------------------------------------.
 * |      |  `   |  F1  |  F2  |  F3  |  F4  |      |      |      | ScBr-| ScBr+|      | Del  |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | [v]  |  F5  |  F6  |  F7  |  F8  |      |      | Prev | Play | Next |      |      |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | [v]  |  F9  |  F10 |  F11 | F12  |      |      | Mute | Vol- | Vol+ |      |      |
 * |-------------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | [v]  | [v]  | [v]  | [v]  |      |             |      | [v]  |      |      |      |
 * `------------------------------------------------------------------------------------------'
 */
[FN_LAYER] = LAYOUT(
    _______, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, XXXXXXX, XXXXXXX, KC_BRMD, KC_BRMU, XXXXXXX, KC_DEL,
    _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX, KC_MRWD, KC_MPLY, KC_MFFD, XXXXXXX, _______,
    _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, _______,
    _______, _______, _______, _______, _______, KC_BTN1,      KC_BTN1,     KC_BTN2, _______, XXXXXXX, XXXXXXX, XXXXXXX
),

// Navigation
[NAV_LAYER] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______, KC_BTN1,     KC_BTN1,      KC_BTN2, _______, XXXXXXX, XXXXXXX, XXXXXXX
),

// Keyboard functions
//
// With special RGB for wilba 
//
[QMK_LAYER] = LAYOUT(
    _______, XXXXXXX, XXXXXXX,   TOWIN, XXXXXXX,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX,   TOMAC, XXXXXXX, XXXXXXX, XXXXXXX, BR_INC,  H1_INC,  EF_INC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_LSFT, XXXXXXX, XXXXXXX, CK_TOGG, XXXXXXX, BR_DEC,  H1_DEC,  EF_DEC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,      _______,     _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
),
};

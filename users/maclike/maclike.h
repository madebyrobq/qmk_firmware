// Maclike by Rob Quinn
//
//
// New Keymap: qmk new-keymap -kb [vendor/keyboard] -km maclike
// Compile and flash: make [vendor/keyboard]:maclike:flash
//
// Reminder: keep master fork up to date
//  git checkout master
//  git fetch upstream
//  git pull upstream master
//  git push origin master
//

// Define these in config.h (they have no effect here?)
// #define PERMISSIVE_HOLD // Allow fast nested hold-taps, but not fast rolling ones
// #define QUICK_TAP_TERM 0 // Turn off key repeat on hold-tap keys when double tapped (important for LT Space)
// #define TAPPING_TERM 200 // Adjust as needed

// Prevent key overrides using LALT or LGUI (default values) from triggering tap functions
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18 // KC_RIGHT_CTRL or KC_F18 recommended

#ifndef USERSPACE
#define USERSPACE

#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"

enum maclike_layers
{
    DEFAULT_LAYER,
    WIN_LAYER,
    RAISE_LAYER,
    FN_LAYER,
    NAV_LAYER,
    QMK_LAYER,
};

// Layers
#define RAISE MO(RAISE_LAYER)
#define FN MO(FN_LAYER)
#define NAV MO(NAV_LAYER)
#define QMK MO(QMK_LAYER)

// Layer taps
#define SPC_RSE LT(RAISE_LAYER, KC_SPC)
#define SPC_QMK LT(QMK_LAYER, KC_SPC)

#define COL_NAV LT(NAV_LAYER, KC_SCLN)

// Mod taps for numpad cluster
#define KC0_CMD LCMD_T(KC_0)
#define DOT_CMD LCMD_T(KC_DOT)

// CMD with bespoke effects on Windows
#define WIN_CMD KC_RCTL

typedef enum
{
    MACLIKE_KEYCODES = (SAFE_RANGE),
    TOWIN,
    TOMAC,
} custom_keycodes;

#endif

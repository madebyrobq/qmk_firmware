// Maclike by Rob Quinn
//
//
//
// Compile example: make planck/rev6:maclike
//
// Reminder: keep master fork up to date
//  git checkout master
//  git fetch upstream
//  git pull upstream master
//  git push origin master
//
// Define these in config.h (they have no effect here?)
#define PERMISSIVE_HOLD // Allow fast nested hold-taps, but not fast rolling ones
#define QUICK_TAP_TERM 0 // Turn off key repeat on hold-tap keys when double tapped
#define TAPPING_TERM 200 // Adjust as needed

// Prevent key overrides using LALT or LGUI (default values) from triggering tap functions
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18

#ifndef USERSPACE
#define USERSPACE

#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"

enum maclike_layers {
  DEFAULT_LAYER,
  WIN_LAYER,
  RAISE_LAYER,
  FN_LAYER,
  NAV_LAYER,
  QMK_LAYER,
};

#define COLQUOT TD(TD_COLQUOT)

#define RAISE MO(RAISE_LAYER)
#define QMK MO(QMK_Layer)

#define ESC_RSE LT(RAISE_LAYER, KC_ESC)
#define ESC_FN LT(FN_LAYER, KC_ESC)

#define ENT_RSE LT(RAISE_LAYER, KC_ENT)
#define ENT_FN LT(FN_LAYER, KC_ENT)

#define SPC_RSE LT(RAISE_LAYER, KC_SPC)
#define SPC_QMK LT(QMK_LAYER, KC_SPC)

#define COL_NAV LT(NAV_LAYER, KC_SCLN)

#define WIN_CMD KC_RCTL

typedef enum{
  MACLIKE_KEYCODES = (SAFE_RANGE),
  TOWIN,      // Turn on windows mode
  TOMAC,      // Turn off windows mode
}custom_keycodes;

#endif

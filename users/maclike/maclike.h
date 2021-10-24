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
// Define these in config.h (they have no effect here)
// #define PERMISSIVE_HOLD // Use hold if another key it pressed and released under the tapping term
// #define TAPPING_FORCE_HOLD // Allow double tap to hold, important for spacebar LT
// #define TAPPING_TERM 200

#ifndef USERSPACE
#define USERSPACE

#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"

enum maclike_layers {
  DEFAULT_LAYER,
  RAISE_LAYER,
  FN_LAYER,
  QMK_LAYER,
};

#define COLQUOT TD(TD_COLQUOT)

#define CMD0 LCMD_T(KC_0)
#define ALTDOT LALT_T(KC_DOT)

#define ESC_FN LT(FN_LAYER, KC_ESC)
#define SPC_RSE LT(RAISE_LAYER, KC_SPC)
#define SPC_QMK LT(QMK_LAYER, KC_SPC)
#define RAISE MO(RAISE_LAYER)
#define QMK MO(QMK_Layer)

typedef enum{
  MACLIKE_KEYCODES = (SAFE_RANGE),
  TOWIN,      // Turn on windows mode
  TOMAC,      // Turn off windows mode
}custom_keycodes;

typedef enum{
  TD_COLQUOT = 0
}tapdances;

__attribute__ ((weak)) qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COLQUOT] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT)
};

#endif
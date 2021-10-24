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

typedef enum{
  MACLIKE_KEYCODES = (SAFE_RANGE),
  FNENT,      // Enter in the Fn layer, used for sending rename on windows and mac
  TOWIN,      // Turn on windows mode
  TOMAC,      // Turn off windows mode
  SPC_RSE,
  SPC_QMK,
  ESC_FN,
}custom_keycodes;

typedef enum{
  TD_COLQUOT = 0
}tapdances;

__attribute__ ((weak)) qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COLQUOT] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_QUOT)
};

#define COLQUOT TD(TD_COLQUOT)

#define CMD0 LCMD_T(KC_0)
#define ALTDOT LALT_T(KC_DOT)

#define RAISE MO(RAISE_LAYER)
#define QMK MO(QMK_Layer)

#define PERMISSIVE_HOLD
#define TAPPING_TERM 200

#endif
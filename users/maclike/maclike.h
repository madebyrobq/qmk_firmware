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
  (SAFE_RANGE),
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

const key_override_t comma_exclamation_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_EXCLAIM);
const key_override_t period_question_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_QUESTION);
const key_override_t slash_backslash_override = ko_make_basic(MOD_MASK_SHIFT, KC_PSLS, KC_BSLS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_exclamation_override,
    &period_question_override,
    &slash_backslash_override,
    
    NULL // null terminator
};

#define PERMISSIVE_HOLD
#define TAPPING_TERM 200

#endif
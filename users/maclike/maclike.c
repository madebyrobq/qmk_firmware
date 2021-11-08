#include QMK_KEYBOARD_H
#include "muse.h"
#include "quantum.h"
#include "maclike.h"

const key_override_t comma_exclamation_override = ko_make_with_layers_negmods_and_options(
  MOD_MASK_SHIFT, 
  KC_COMMA, 
  KC_EXCLAIM,
  ~0,
  MOD_MASK_CAG,
  ko_option_activation_trigger_down);
const key_override_t period_question_override = ko_make_with_layers_negmods_and_options(
  MOD_MASK_SHIFT, 
  KC_DOT, 
  KC_QUESTION,
  ~0,
  MOD_MASK_CAG,
  ko_option_activation_trigger_down);
const key_override_t slash_backslash_override = ko_make_with_layers_negmods_and_options(
  MOD_MASK_SHIFT, 
  KC_PSLS, 
  KC_BSLS,
  ~0,
  MOD_MASK_CAG,
  ko_option_activation_trigger_down);

const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_exclamation_override,
    &period_question_override,
    &slash_backslash_override,
    
    NULL // null terminator
};

// In most apps on Windows, tapping Alt focuses the menu bar
// Using the WinAlt and WinLeft/WinRight buttons logically sends an Alt tap
// Which causes every other "move cursor by word" to focus the menu bar instead
// Every time we register Alt, send a 'blank' keycode which is used for literally nothing
// This prevents the Alt tap behavior when using arrow keys as well as all over Windows which is nice
#define BLANK X_F17

bool wintaskswitcheropen = false;
bool wincmdpressed = false;
bool winaltpressed = false;

bool win_mode(void){
  return layer_state_is(WIN_LAYER);
}

bool process_special_case_key(uint16_t keycode, bool pressed){

  // Scrolling for mac needs to be reversed
  if(keycode == KC_WH_D){
    if(pressed){
      if(win_mode())
        register_code(KC_WH_D);
      else
        register_code(KC_WH_U);
    }
    else{
      unregister_code(KC_WH_D);
      unregister_code(KC_WH_U);
    }  
    return false;
  }
  if(keycode == KC_WH_U){
    if(pressed){
      if(win_mode())
        register_code(KC_WH_U);
      else
        register_code(KC_WH_D);
    }
    else{
      unregister_code(KC_WH_D);
      unregister_code(KC_WH_U);
    }
    return false;
  }

  if(keycode == KC_ENT){
    if(pressed){
      if(win_mode() && (IS_LAYER_ON(FN_LAYER) || IS_LAYER_ON(RAISE_LAYER)))
        // Send rename if Windows sends Fn Enter
        SEND_STRING(SS_TAP(X_F2));
      else
        register_code(KC_ENT);
    }
    else
      unregister_code(KC_ENT);
    return false;
  }

  return true;
}

bool process_winmode_key(uint16_t keycode, bool pressed){

  if(keycode == KC_LCMD || keycode == KC_RCMD){
    wincmdpressed = pressed;
    if (pressed)
      register_code(KC_RCTL);
    else {
      unregister_code(KC_RCTL);

      if(wintaskswitcheropen == true){
        // Release the task switcher
        unregister_code(KC_LALT);
        wintaskswitcheropen = false;
      }
    }
    return false;
  }

  if(keycode == KC_LALT){
    winaltpressed = pressed;
    if (pressed) {
      register_code(KC_LALT);
      SEND_STRING(SS_TAP(BLANK));
    } 
    else
      unregister_code(KC_LALT);
    return false;
  }

  if(keycode == KC_TAB){
    if(pressed){
      if(wincmdpressed == true){
        // Swap Ctrl for Alt
        unregister_code(KC_RCTL);
        register_code(KC_LALT);
        wintaskswitcheropen = true;
      }

      // Tab in all cases
      register_code(KC_TAB);
    }
    else
      unregister_code(KC_TAB);
    return false;
  }

  if(keycode == KC_LEFT){
    if(pressed){
      if(wincmdpressed == true && winaltpressed == false){
        // Send a single Home instead of Ctrl+Arrow
        unregister_code(KC_RCTL);
        SEND_STRING(SS_TAP(X_HOME));
        register_code(KC_RCTL);
      }
      else if(winaltpressed == true && wincmdpressed == false){
        // Send a single Ctrl+Arrow instead of Alt+Arrow
        unregister_code(KC_LALT);
        SEND_STRING(SS_RCTL(SS_TAP(X_LEFT)));
        register_code(KC_LALT);
        SEND_STRING(SS_TAP(BLANK));
      }
      else
        register_code(KC_LEFT);
    }
    else
      unregister_code(KC_LEFT);
    return false;
  }

  if(keycode == KC_RIGHT){
    if(pressed){
      if(wincmdpressed == true && winaltpressed == false){
        // Send a single End instead of Ctrl+Arrow
        unregister_code(KC_RCTL);
        SEND_STRING(SS_TAP(X_END));
        register_code(KC_RCTL);
      }
      else if(winaltpressed == true && wincmdpressed == false){
        // Send a single Ctrl+Arrow instead of Alt+Arrow
        unregister_code(KC_LALT);
        SEND_STRING(SS_RCTL(SS_TAP(X_RIGHT)));
        register_code(KC_LALT);
        SEND_STRING(SS_TAP(BLANK));
      }
      else
        register_code(KC_RIGHT);
    }
    else
      unregister_code(KC_RIGHT);
    return false;
  }

  if(keycode == KC_BSPC){
    if(pressed){
      if(wincmdpressed == true){
        unregister_code(KC_RCTL);
        
        // Register Delete
        register_code(KC_DEL);

        register_code(KC_RCTL);
      }
      else
        register_code(KC_BSPC);
    }
    else{
      unregister_code(KC_BSPC);
      unregister_code(KC_DEL);
    }
    return false;
  }

  if(keycode == KC_SPC){
    if(pressed){
      if(wincmdpressed == true){
        
        // Cancel RCtrl from WINCMD, to use Ctrl here use the left one that is still available
        unregister_code(KC_RCTL);

        // Hold Win key instead. Tapping this key brings up the windows start menu, similar to spotlight search on mac.
        SEND_STRING(SS_DOWN(X_LWIN));
      }
      else
        register_code(KC_SPC);
    }
    else{

      // This should continue to work while space is held, so a Win+letter shortcut can be used without holding WINCTL
      SEND_STRING(SS_UP(X_LWIN));

      unregister_code(KC_SPC);
    }
    return false;
  }

  return true;
}

bool process_record_user_maclike(uint16_t keycode, keyrecord_t *record) {

  bool pressed = record -> event.pressed;

  if(win_mode() && !process_winmode_key(keycode, pressed))
    return false;

  if(!process_special_case_key(keycode, pressed))
    return false;
  
  if(keycode == TOWIN){
    if(pressed)
      set_single_persistent_default_layer(WIN_LAYER);
    return false;
  }

  if(keycode == TOMAC){
    if(pressed)
      set_single_persistent_default_layer(DEFAULT_LAYER);
    return false;
  }

  return true;
};

// This can be overridden in a keymap, in which case be sure to include a call to process_record_user_maclike
__attribute__ ((weak)) bool process_record_user(uint16_t keycode, keyrecord_t *record){
  if(!process_record_user_maclike(keycode, record))
    return false;
  return true;
}
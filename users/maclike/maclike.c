#include QMK_KEYBOARD_H
#include "muse.h"
#include "quantum.h"
#include "maclike.h"

// In most apps on Windows, tapping Alt focuses the menu bar
// Using the WinAlt and WinLeft/WinRight buttons logically sends an Alt tap
// Which causes every other "move cursor by word" to focus the menu bar instead
// Every time we register Alt, send a 'blank' keycode which is used for literally nothing
// This prevents the Alt tap behavior when using arrow keys as well as all over Windows which is nice
#define BLANK X_F17

void unfocus_menu_bar(void){
  SEND_STRING(SS_TAP(BLANK));
}

bool wintaskswitcheropen = false;

bool win_mode(void){
  // NOTE: Default layer state actually starts at 1 so it doesn't correspond to the set layer...
  return default_layer_state - 1 == WIN_LAYER;
}

bool process_maclike_key(uint16_t keycode, bool pressed){

  // Scrolling for Mac needs to be reversed
  if(keycode == KC_WH_D && !win_mode()){
    if(pressed)
      register_code(KC_WH_U);
    else
      unregister_code(KC_WH_U);
    return false;
  }
  if(keycode == KC_WH_U && !win_mode()){
    if(pressed)
      register_code(KC_WH_D);
    else
      unregister_code(KC_WH_D);
    return false;
  }
  
  return true;
}

bool process_maclike_win_mode_key(uint16_t keycode, bool pressed){

  if(!win_mode())
    return true;

  bool alt_pressed = get_mods() & MOD_BIT(KC_LALT);
  bool cmd_pressed = get_mods() & MOD_BIT(WIN_CMD);

// Suppress Ctrl and hold Alt to open the task switcher, and continue
  if(keycode == KC_TAB && pressed && cmd_pressed){
    unregister_code(WIN_CMD);
    register_code(KC_LALT);
    wintaskswitcheropen = true;
  }

  // Check to release the task switcher, and continue
  if(keycode == WIN_CMD && !pressed && wintaskswitcheropen){
      unregister_code(KC_LALT);
      wintaskswitcheropen = false;
  }  

  // Suppress annoying menu bar focus immediately after registering Alt
  if(keycode == KC_LALT && pressed){
    register_code(keycode);
    unfocus_menu_bar();
    //return false;
  }

  // Send Ctrl+Arrow instead of Alt+Arrow
  if(keycode == KC_LEFT || keycode == KC_RIGHT){
    if(pressed && alt_pressed && !cmd_pressed){
        unregister_code(KC_LALT);
        if(keycode == KC_LEFT)
          SEND_STRING(SS_RCTL(SS_TAP(X_LEFT)));
        else
          SEND_STRING(SS_RCTL(SS_TAP(X_RIGHT)));
        register_code(KC_LALT);
        unfocus_menu_bar();
        return false;
    }
  }
  
  // Send rename if Windows sends Enter from the Raise/Fn layer
  if(keycode == KC_ENT && (IS_LAYER_ON(FN_LAYER) || IS_LAYER_ON(RAISE_LAYER))){
    if(pressed)
        SEND_STRING(SS_TAP(X_F2));
    return false;
  }

  return true;
}

bool process_record_user_maclike(uint16_t keycode, keyrecord_t *record) {

  bool pressed = record -> event.pressed;

  if(!process_maclike_win_mode_key(keycode, pressed))
    return false;

  if(!process_maclike_key(keycode, pressed))
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

// Basic Shift overrides for different symbols
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

// Win mode overrides
// "Cmd" + L/R = home/end
bool win_mode_key_override(bool pressed, void *context) { return win_mode(); }
const key_override_t cmd_right_override = {
  .trigger_mods          = MOD_BIT(WIN_CMD),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(WIN_CMD),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) MOD_BIT(KC_LALT),
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_RIGHT,
  .replacement            = KC_END,
  .enabled                = NULL};
const key_override_t cmd_left_override = {
  .trigger_mods           = MOD_BIT(WIN_CMD),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(WIN_CMD),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) MOD_BIT(KC_LALT),
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_LEFT,
  .replacement            = KC_HOME,
  .enabled                = NULL};

// Alt + L/R = Ctrl + L/R 
// NOTE: this doesn't work well with key overrides as it focuses the menu bar every other time...
/*const key_override_t alt_right_override = {
  .trigger_mods          = MOD_BIT(KC_LALT),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(KC_LALT),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) (MOD_BIT(KC_LCTL) | MOD_BIT(WIN_CMD)),
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_RIGHT,
  .replacement            = RCTL(KC_RIGHT),
  .enabled                = NULL};
const key_override_t alt_left_override = {
  .trigger_mods           = MOD_BIT(KC_LALT),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(KC_LALT),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) (MOD_BIT(KC_LCTL) | MOD_BIT(WIN_CMD)),
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_LEFT,
  .replacement            = RCTL(KC_LEFT),
  .enabled                = NULL};*/

// "Cmd" + Backspace = Delete
const key_override_t cmd_backspace_override = {
  .trigger_mods           = MOD_BIT(WIN_CMD),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(WIN_CMD),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) 0,
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_BSPC,
  .replacement            = KC_DEL,
  .enabled                = NULL};

// "Cmd" + Space = Windows key (tap for search)
const key_override_t cmd_space_override = {
  .trigger_mods           = MOD_BIT(WIN_CMD),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(WIN_CMD),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) ~MOD_BIT(WIN_CMD),
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_SPC,
  .replacement            = KC_LGUI,
  .enabled                = NULL};

// "Cmd" + LCTRL + Space = emojis
const key_override_t cmd_ctrl_space_override = {
  .trigger_mods           = MOD_BIT(WIN_CMD) | MOD_BIT(KC_LCTL),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(WIN_CMD) | MOD_BIT(KC_LCTL),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) ~(MOD_BIT(WIN_CMD) | MOD_BIT(KC_LCTL)),
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_SPC,
  .replacement            = LGUI(KC_DOT),
  .enabled                = NULL};

// "Cmd" + Tab = Alt + Tab and hold Alt
// NOTE: this doesn't hold the task switcher open which is annoying
/*const key_override_t cmd_tab_override = {
  .trigger_mods           = MOD_BIT(WIN_CMD),
  .layers                 = ~0,
  .suppressed_mods        = MOD_BIT(WIN_CMD),
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) 0,
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = KC_TAB,
  .replacement            = LALT(KC_TAB),
  .enabled                = NULL};*/

const key_override_t cmd_option_esc_override = {
  .trigger_mods           = MOD_BIT(WIN_CMD) | MOD_BIT(KC_LALT),
  .layers                 = ~0,
  .suppressed_mods        = 0,
  .options                = ko_option_activation_trigger_down,
  .negative_mod_mask      = (uint8_t) 0,
  .custom_action          = win_mode_key_override,
  .context                = NULL,
  .trigger                = ESC_RSE,
  .replacement            = LCA(KC_DEL),
  .enabled                = NULL};

const key_override_t **key_overrides = (const key_override_t *[]){
    &comma_exclamation_override,
    &period_question_override,
    &slash_backslash_override,
    &cmd_right_override,
    &cmd_left_override,
    //&alt_right_override,
    //&alt_left_override,
    &cmd_backspace_override,
    &cmd_space_override,
    &cmd_ctrl_space_override,
    //&cmd_tab_override,
    &cmd_option_esc_override,
    
    NULL // null terminator
};
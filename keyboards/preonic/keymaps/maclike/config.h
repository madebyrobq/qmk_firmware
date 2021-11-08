#pragma once

#define ENCODER_RESOLUTION 4

#define PERMISSIVE_HOLD // Use hold if another key it pressed and released under the tapping term
#define TAPPING_FORCE_HOLD // Allow double tap followed by hold, important for spacebar LT
#define TAPPING_TERM 200

#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MOVE_DELTA 3
#define MOUSEKEY_MAX_SPEED 10
#define MOUSEKEY_TIME_TO_MAX 50
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 16
#define MOUSEKEY_WHEEL_MAX_SPEED 1
#define MOUSEKEY_WHEEL_TIME_TO_MAX 50

#ifdef AUDIO_ENABLE

#define AUDIO_CLICKY
#define DAC_SAMPLE_MAX 30000U//65535U

// Mac chord 
#define MAC_SOUND E__NOTE(_FS4), E__NOTE(_AS4), Q__NOTE(_CS5), W__NOTE(_FS5)

// XP Startup
#define WIN_SOUND W__NOTE(_DS5), S__NOTE(_DS4), H__NOTE(_AS4), H__NOTE(_GS4), H__NOTE(_DS4), H__NOTE(_DS5), H__NOTE(_AS4)

#define DEFAULT_LAYER_SONGS { SONG(MAC_SOUND), SONG(WIN_SOUND)}
#endif
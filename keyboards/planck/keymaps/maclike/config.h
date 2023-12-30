#pragma once

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

#define AUDIO_CLICKY

#define DAC_SAMPLE_MAX 30000U//65535U

#ifdef AUDIO_ENABLE

// Mac chord 
#define MAC_SOUND E__NOTE(_FS4), E__NOTE(_AS4), Q__NOTE(_CS5), W__NOTE(_FS5)

// XP Startup
#define WIN_SOUND W__NOTE(_DS5), S__NOTE(_DS4), H__NOTE(_AS4), H__NOTE(_GS4), H__NOTE(_DS4), H__NOTE(_DS5), H__NOTE(_AS4)

#define DEFAULT_LAYER_SONGS { SONG(MAC_SOUND), SONG(WIN_SOUND)}
#endif
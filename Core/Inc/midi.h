#pragma once

#include <stdint.h>

// MIDI Channel Events
#define NOTE_OFF 0x80
#define NOTE_ON 0x90
#define NOTE_AFTERTOUCH 0xA0
#define CONTROLLER 0xB0
#define PROGRAM_CHANGE 0xC0
#define CHANNEL_AFTERTOUCH 0xD0
#define PITCH_BEND 0xE0
#define CHANNEL_EVENT_DOWN 0x80
#define CHANNEL_EVENT_UP 0xEF

// The flag of meta events
#define META_EVENT_PREFIX 0xFF

// MIDI Meta Events
#define META_SEQUENCE_NUMBER 0x00
#define META_TEXT_EVENT 0x01
#define META_COPYRIGHT_NOTICE 0x02
#define META_TRACK_NAME 0x03
#define META_INSTRUMENT_NAME 0x04
#define META_LYRICS 0x05
#define META_MARKER 0x06
#define META_CUE_POINT 0x07
#define META_MIDI_CHANNEL_PREFIX 0x20
#define META_END_OF_TRACK 0x2F
#define META_SET_TEMPO 0x51
#define META_SMPTE_OFFSET 0x54
#define META_TIME_SIGNATURE 0x58
#define META_KEY_SIGNATURE 0x59
#define META_SEQUENCER_SPECIFIC 0x7F
#define META_EVENT_DOWN 0x00
#define META_EVENT_UP 0x7F

// SysEx Events
#define SYSEX_EVENT_1 0xF0
#define SYSEX_EVENT_2 0xF7

typedef struct {
    uint32_t MThd;
    uint32_t size;
    uint16_t format_type;
    uint16_t num_tracks;
    uint16_t time_division;
} MIDI_Header;

typedef struct {
    uint32_t delta_time;
    uint8_t event_type_and_channel;
    uint8_t param1;
    uint8_t param2;
    uint8_t is_meta_event;
} MIDI_Event;

typedef struct {
    uint32_t MTrk;
    uint32_t size;
    uint8_t last_event;
    MIDI_Event events;
} MIDI_Track_Header;


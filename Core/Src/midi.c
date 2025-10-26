#include "midi.h"
#include "string.h"
#include "fatfs.h"

uint8_t decode_status = HEADER_DECODING;
MIDI_Info midi_info;

uint32_t convert32bit (uint32_t data) {
    uint32_t result;

    result = (data & 0x000000FF) << 24;
    result |= (data & 0x0000FF00) << 8;
    result |= (data & 0x00FF0000) >> 8;
    result |= (data & 0xFF000000) >> 24;

    return result;
}

uint16_t convert16bit (uint16_t data) {
    uint16_t result;

    result = (data & 0x00FF) << 8;
    result |= (data & 0xFF00) >> 8;

    return result;
}

int is_midi_header_id (uint8_t* bytes) {
    if (bytes[0] == 0x4D && bytes[1] == 0x54 && bytes[2] == 0x68 && bytes[3] == 0x64) {
        return MIDI_OK;
    }
    else {
        return MIDI_ERROR;
    }
}

int is_midi_track_id (uint8_t* bytes) {
    if (bytes[0] == 0x4D && bytes[1] == 0x54 && bytes[2] == 0x72 && bytes[3] == 0x6B) {
        return MIDI_OK;
    }
    else {
        return MIDI_ERROR;
    }
}

int midi_decode_header (MIDI_Info* midi_info, uint8_t* bytes) {
    if (!is_midi_header_id(bytes)) {
        return MIDI_ERROR;
    }

    midi_info->header.MThd = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    midi_info->header.size = (bytes[4] << 24) | (bytes[5] << 16) | (bytes[6] << 8) | bytes[7];
    midi_info->header.format_type = (bytes[8] << 8) | bytes[9];
    midi_info->header.num_tracks = (bytes[10] << 8) | bytes[11];
    midi_info->header.time_division = (bytes[12] << 8) | bytes[13];

    return MIDI_OK;
}

int midi_decode_track_header (MIDI_Info* midi_info, uint8_t* bytes) {
    if (!is_midi_track_id(bytes)) {
        return MIDI_ERROR;
    }

    midi_info->track.MTrk = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    midi_info->track.size = (bytes[4] << 24) | (bytes[5] << 16) | (bytes[6] << 8) | bytes[7];

    return MIDI_OK;
}

uint32_t get_variable_value (uint8_t* bytes, uint32_t* offset) {
    uint32_t value = 0;

    while (1) {
        value = (value << 7) | (bytes[*offset] & 0x7F);
        if (bytes[*offset] & 0x80) {
            (*offset)++;
        }
        else {
            break;
        }
    }

    (*offset)++;
    return value;
}
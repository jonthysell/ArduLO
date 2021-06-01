// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <avr/pgmspace.h>

#include <ArduboyTonesPitches.h>

#ifndef SOUNDS_H
#define SOUNDS_H

const uint16_t BaseNoteDuration = 64;

const uint16_t MoveSound = NOTE_C4;
const uint16_t MoveSoundDuration = BaseNoteDuration*2;

const uint16_t ToggleSound = NOTE_G4;
const uint16_t ToggleSoundDuration = BaseNoteDuration*2;

const uint16_t LevelComplete1Sound[] PROGMEM = {
    NOTE_B3,BaseNoteDuration*2,
    TONES_END
};

const uint16_t LevelComplete2Sound[] PROGMEM = {
    NOTE_C4,BaseNoteDuration*2,
    TONES_END
};

const uint16_t LevelComplete3Sound[] PROGMEM = {
    NOTE_C4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_DS4,BaseNoteDuration*2,
    TONES_END
};

const uint16_t LevelComplete4Sound[] PROGMEM = {
    NOTE_C4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_E4,BaseNoteDuration*2,
    TONES_END
};

const uint16_t LevelComplete5Sound[] PROGMEM = {
    NOTE_C4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_E4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_FS4,BaseNoteDuration*2,
    TONES_END
};

const uint16_t LevelComplete6Sound[] PROGMEM = {
    NOTE_C4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_E4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_G4,BaseNoteDuration*2,
    TONES_END
};

const uint16_t GameCompleteSound[] PROGMEM = {
    NOTE_C4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_E4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_G4,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_C5,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_E5,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_G5,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_C6,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_E6,BaseNoteDuration*2,
    NOTE_REST,BaseNoteDuration,
    NOTE_G6,BaseNoteDuration*2,
    TONES_END
};

#endif
// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <avr/pgmspace.h>

#ifndef BITMAPS_H
#define BITMAPS_H

const uint8_t TitleBitmapWidth = 120;
const uint8_t TitleBitmapHeight = 39;

const uint8_t TitleBitmap[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0xfc,
    0x7c, 0x3e, 0x1e, 0x8f, 0xef, 0xff, 0xff, 0xff,
    0x3f, 0x07, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfe, 0x7f, 0x1f,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8,
    0xfc, 0xfe, 0x7f, 0x1f, 0x0f, 0x8f, 0x8f, 0xff,
    0xfe, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x80, 0xc0,
    0xe0, 0xf0, 0xf8, 0xfc, 0x7c, 0x3e, 0x1e, 0x1f,
    0x0f, 0x0f, 0x0f, 0x9f, 0xff, 0xfe, 0xfc, 0xf8,
    0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0x7c,
    0x3c, 0x3c, 0x3e, 0x1e, 0x1e, 0x1e, 0x1e, 0xde,
    0xfe, 0xfe, 0xfe, 0xff, 0x3f, 0x1f, 0x1f, 0x1e,
    0xde, 0xfe, 0xfe, 0xff, 0xff, 0x1f, 0x1f, 0x1e,
    0x1e, 0x1e, 0x7e, 0x7c, 0x7f, 0x3f, 0x8f, 0xef,
    0xfe, 0xfe, 0x3e, 0x1e, 0x0e, 0x0e, 0x06, 0x00,
    0xc0, 0xf0, 0xf8, 0xfc, 0x3e, 0x1e, 0x1e, 0x9e,
    0xfc, 0xfe, 0xff, 0x3f, 0x0f, 0x03, 0x00, 0xc0,
    0xf0, 0xfc, 0xfe, 0x3e, 0x0e, 0x00, 0xc0, 0xf0,
    0xfc, 0xfe, 0x7e, 0x0e, 0x00, 0x00, 0x0e, 0x0f,
    0x0f, 0x0f, 0xef, 0xff, 0xff, 0xff, 0xff, 0x1f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07,
    0x07, 0x0f, 0xcf, 0xff, 0xff, 0xff, 0xff, 0x3f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0xef, 0xf7, 0xf7, 0xf3, 0xe1, 0x00,
    0xfc, 0xff, 0xff, 0xff, 0x87, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xc0, 0xf0, 0xfc, 0xff, 0x7f,
    0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0e,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e, 0x1e, 0x1e,
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f,
    0x1f, 0x1f, 0x1e, 0x1e, 0x1e, 0x1e, 0x0e, 0x00,
    0x07, 0x0f, 0x1f, 0x1f, 0x1e, 0x1e, 0x1f, 0x0f,
    0x1f, 0x1f, 0x1e, 0x1e, 0x1e, 0x0e, 0x0f, 0x0f,
    0x1f, 0x1f, 0x1e, 0x1e, 0x1e, 0x0f, 0x0f, 0x1f,
    0x1f, 0x1f, 0x1e, 0x1e, 0x0e, 0x00, 0x00, 0xe0,
    0xfc, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xfe, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0,
    0xf8, 0xfe, 0xff, 0xff, 0x3f, 0x0f, 0x03, 0x00,
    0x00, 0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x1e, 0x1e,
    0x1e, 0x1f, 0x0f, 0x0f, 0x07, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
    0xf0, 0xf8, 0xf8, 0xfc, 0x7c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x3c, 0x3c, 0xbc, 0xfc, 0xfc, 0xff, 0xff,
    0x7f, 0x3f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c,
    0x3c, 0x18, 0x03, 0x0f, 0x0f, 0x1f, 0x1e, 0x3c,
    0x3c, 0x3c, 0x3c, 0x3e, 0x3e, 0x1f, 0x1f, 0x0f,
    0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
    0x1f, 0x3f, 0x3f, 0x7f, 0x7c, 0x78, 0x78, 0x78,
    0x7c, 0x3c, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t LightBitmapSize = 8;

const uint8_t LightBitmap0[] PROGMEM = {
    0x7e, 0x81, 0x81, 0x81, 0x85, 0x8d, 0x81, 0x7e,
};

const uint8_t LightBitmap1[] PROGMEM = {
    0x7e, 0xff, 0xff, 0xff, 0xfb, 0xf3, 0xff, 0x7e,
};

const uint8_t StarBitmapSize = 16;

const uint8_t StarBitmap0[] PROGMEM = {
    0x60, 0x90, 0x10, 0x10, 0x10, 0x18, 0x06, 0x01,
    0x01, 0x06, 0x18, 0x10, 0x10, 0x10, 0x90, 0x60,
    0x00, 0x00, 0x79, 0x46, 0x40, 0x20, 0x20, 0x10,
    0x10, 0x20, 0x20, 0x40, 0x46, 0x79, 0x00, 0x00,
};

const uint8_t StarBitmap1[] PROGMEM = {
    0x60, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xfe, 0xff,
    0x01, 0x06, 0x18, 0x10, 0x10, 0x10, 0x90, 0x60,
    0x00, 0x00, 0x79, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f,
    0x10, 0x20, 0x20, 0x40, 0x46, 0x79, 0x00, 0x00,
};

const uint8_t StarBitmap2[] PROGMEM = {
    0x60, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xfe, 0xff,
    0xff, 0xfe, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0x60,
    0x00, 0x00, 0x79, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f,
    0x1f, 0x3f, 0x3f, 0x7f, 0x7f, 0x79, 0x00, 0x00,
};

#endif

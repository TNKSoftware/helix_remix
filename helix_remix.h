#pragma once

#include "split_util.h"

#ifdef RGBLIGHT_ENABLE
#define HSV_BASE 0, 0, 170
#define HSV_EX1 140, 255, 150
#define HSV_EX2 7, 255, 150

void init_rgblight(bool enable);
#endif

#ifdef OLED_DRIVER_ENABLE
typedef enum _bmp_rotate{
    BmpRotateNone,
    BmpRotate90,
    BmpRotate180,
    BmpRotate270
} bmp_rotate;

void oled_write_pixel_ex(uint8_t x, uint8_t y, bool on);
void draw_bitmap(
    const uint8_t *bmp_ptr,
    int bmp_width, int bmp_height, int bmp_stride,
    int map_x, int map_y,
    int draw_x, int draw_y, bmp_rotate rotation);
#endif

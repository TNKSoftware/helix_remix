#include "helix_remix.h"
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
// 引数が無い関数でもvoidを記述しないとエラー
// (function declaration isn't a prototype)になる
void init_rgblight(void) {
    rgblight_enable_noeeprom();

#if defined(RGBLIGHT_MODE_RGB_TEST)
    // RGBテストモードで点灯する
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
#else
    // 暗い紫で常時点灯させる
    rgblight_sethsv_noeeprom(HSV_BASE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    //rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
#endif
}
#endif

#ifdef OLED_ENABLE
extern uint8_t oled_buffer[OLED_MATRIX_SIZE];
extern OLED_BLOCK_TYPE oled_dirty;  // 0xFFFFですべての領域を更新できる

void oled_write_pixel_ex(uint8_t x, uint8_t y, bool on) {
    if (x >= OLED_DISPLAY_WIDTH || y >= OLED_DISPLAY_HEIGHT) {
        return;
    }

    uint16_t index = x + (y / 8) * OLED_DISPLAY_WIDTH;
    bool old_on = (oled_buffer[index] >> (y % 8)) & 0x01;
    if(old_on != on) {
        if (on) {
            oled_buffer[index] |= (1 << (y % 8));
        } else {
            oled_buffer[index] &= ~(1 << (y % 8));
        }
        oled_dirty |= (1 << (index / OLED_BLOCK_SIZE));
    }
}

// ビットマップの転送
// bmp_ptr : 画像のバイト配列(img2hexツールで作成)
// bmp_width : マップチップあたりの横幅
// bmp_height : マップチップあたりの縦幅
// bmp_stride : 画像の横幅(8bit単位で丸める)
// map_x : マップチップのx位置
// map_y : マップチップのy位置
// draw_x : OLEDの描画x位置
// draw_y : OLEDの描画y位置
// rotation : 画像の回転角度
void draw_bitmap(
    const uint8_t *bmp_ptr,
    int bmp_width, int bmp_height, int bmp_stride,
    int map_x, int map_y,
    int draw_x, int draw_y, bmp_rotate rotation){

    int rx, ry;

    map_x *= bmp_width;
    map_y *= bmp_height;

    int pos, hpos, lpos = -1;
    uint8_t v = 0x00;
    for(int y = 0; y < bmp_height; y++){
        int _y = map_y + y;
        for(int x = 0; x < bmp_width; x++){
            int _x = map_x + x;
            pos = _y * bmp_stride + _x;
            hpos = pos / 8;
            if(hpos != lpos){
                lpos = hpos;
                v = pgm_read_byte(&bmp_ptr[hpos]);
            }

            switch(rotation){
                case BmpRotate90:
                    rx = draw_x + (bmp_height - 1 - y);
                    ry = draw_y + x;
                    break;
                case BmpRotate180:
                    rx = draw_x + (bmp_width - 1 - x);
                    ry = draw_y + (bmp_height - 1 - y);
                    break;
                case BmpRotate270:
                    rx = draw_x + y;
                    ry = draw_y + (bmp_width - 1 - x);
                    break;
                default:
                    rx = draw_x + x;
                    ry = draw_y + y;
                    break;
            }

            oled_write_pixel_ex(rx, ry, (v >> (pos % 8)) & 0x01);
        }
    }
}
#endif

__attribute__((weak))
void suspend_power_down_user(void)
{
    oled_off();
}

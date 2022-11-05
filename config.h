#pragma once

#include "config_common.h"

/* USBデバイスデスクリプタの宣言 */
#define VENDOR_ID       0x3265
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    TNK Software
#define PRODUCT         Helix Remix
#define DESCRIPTION     A split keyboard for the cheap makers
#define USB_MAX_POWER_CONSUMPTION 400

/* 分割キーボードのためのシリアル通信設定 */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

#define SPLIT_TRANSACTION_IDS_USER USER_DATA_SYNC

/* 左側がメインボード */
#define MASTER_LEFT
/* D1ピンの通電状況で左右を判断 */
// #define SPLIT_HAND_PIN D1

/* キーマトリックスのサイズ(5行) */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }

/* はんだ付けしたダイオードの向き */
#define DIODE_DIRECTION COL2ROW

/* 5ms経過したらキー入力を確定する。チャタリング（重複送信）抑止 */
#define DEBOUNCE 5


/* LED照明の設定 */
#ifdef RGBLIGHT_ENABLE

/* スリープモードの時、照明を切る */
#define RGBLIGHT_SLEEP

/* 通信に使用するピン */
#define RGB_DI_PIN D3

/* 最大輝度を低くしておかないと、電力不足で誤動作の原因となる */
#define RGBLIGHT_LIMIT_VAL 35

/* RGB LEDの個数 */
#define RGBLED_NUM 64

/* 分割キーボードにおけるLEDの設定 */
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT {32, 32}

/* 照明レイヤーを有効にする */
#define RGBLIGHT_LAYERS

/* すべてのアニメーションを有効にする */
// #define RGBLIGHT_ANIMATIONS
/* もしくは、使用したいアニメーション効果のみを宣言 */
// #define RGBLIGHT_EFFECT_RGB_TEST

/* LEDマッピングの定義 */
#define LED_LAYOUT( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43, L44, L45, L46, R40, R41, R42, R43, R44, R45, R46 \
) { \
    L05, L04, L03, L02, L01, L00, \
    L10, L11, L12, L13, L14, L15, \
    L25, L24, L23, L22, L21, L20, \
    L30, L31, L32, L33, L34, L35, L36, \
    L46, L45, L44, L43, L42, L41, L40, \
    R00, R01, R02, R03, R04, R05, \
    R15, R14, R13, R12, R11, R10, \
    R20, R21, R22, R23, R24, R25, \
    R36, R35, R34, R33, R32, R31, R30, \
    R40, R41, R42, R43, R44, R45, R46 \
}

#define RGBLIGHT_LED_MAP LED_LAYOUT( \
   0,  1,  2,  3,  4,  5,            37, 36, 35, 34, 33, 32, \
   6,  7,  8,  9, 10, 11,            43, 42, 41, 40, 39, 38, \
  12, 13, 14, 15, 16, 17,            49, 48, 47, 46, 45, 44, \
  18, 19, 20, 21, 22, 23, 24,    56, 55, 54, 53, 52, 51, 50, \
  25, 26, 27, 28, 29, 30, 31,    63, 62, 61, 60, 59, 58, 57)
#endif

#ifdef OLED_ENABLE
/* OLEDの画面をスリープにする間隔(ms) */
#define OLED_TIMEOUT 5000

#define OLED_FONT_H "helixfont.h"
#endif

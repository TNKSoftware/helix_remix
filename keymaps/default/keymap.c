#include QMK_KEYBOARD_H

#ifdef HREMIX_DATA_ENABLE
#include "split_common/transport.h"
#endif

#include "helix_remix.h"
#include "key_layout.h"

#ifdef OLED_DRIVER_ENABLE
#include "oled_pct.h"
#endif

// 日本語キーボード特有のキーを使用する
#include "keymap_jp.h"

// それぞれのわかりやすい名前のレイヤー名は、以降のキーマップマトリクスで使用される
// アンダースコアに特別な意味はなく、自由に設定しても問題ない
// 名前の長さも統一する必要はなく、数字のみにする(enumではなくdefineで定義するなど)こともできる
enum layer_number {
  _BASE = 0,
  _LOWER,
  _UPPER,
  _FF14
};

// 独自のキーコードの定義。SAFE_RANGEにより固有の数値を確保することが保証される
// 独自キーが押されたかの判断はprocess_record_userで調べる
enum custom_keycodes {
  MAC_WIN = SAFE_RANGE
};

// タップダンスの定義
enum custom_tap_dance {
  TAPDANCE_FF14
};

#define TD_FF14 TD(TAPDANCE_FF14)

static bool tap_dance_active = false;

void on_tapdance_finished(qk_tap_dance_state_t *state, void *user_data) {
    // 1回のタップならワンショットレイヤーを、2回以上ならレイヤーを切り替える
    // もう一度レイヤーキーを押すとレイヤーを解除
    if (state->count == 1) {
        if(tap_dance_active){
            reset_oneshot_layer();
            tap_dance_active = false;
        }else if(IS_LAYER_ON(_FF14)){
            layer_off(_FF14);
        }else{
            set_oneshot_layer(_FF14, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            tap_dance_active = true;
        }
    } else {
        layer_invert(_FF14);
    }
}

// 全てのタップダンス関数はここに定義します。ここでは1つだけ示します。
qk_tap_dance_action_t tap_dance_actions[] = {
    [TAPDANCE_FF14] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_tapdance_finished, NULL),
};


// レイヤーモード
// DF - デフォルトレイヤー
// MO - 押している間だけ切り替え
// TG - 押すごとに切り替え
// OSL - 何かしらのキーが押されたら直前のレイヤーに戻る
#define DL_BAS  DF(_BASE)
#define ML_LOW  MO(_LOWER)
#define ML_UPP  MO(_UPPER)
#define ML_FF14 TG(_FF14)

// ______ - 下層レイヤーのキーを引き継ぐ
// XXXXXX - ほかのレイヤーのキーは引き継がず、無効にする
// C() - Ctrlキーとの組み合わせ
// S() - Shiftキーとの組み合わせ
// A() - Altキーとの組み合わせ
// C(S()) - Ctrl+Shiftの組み合わせ
// MT(A,B) - おしたままならA(ShiftやAltなどのMODキー限定)をタップならBを実行
// OSM() - 何かしらのキーが押されるまでは()内のキーを有効にする

// keymapviz keymap.c -k helix -t json -o hremix{}.json

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = KEY_LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, \
    JP_ZHTG, KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,   \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_DEL, KC_DEL, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,  \
    KC_LCTL, KC_LALT, KC_LGUI, TD_FF14, ML_UPP, ML_LOW, KC_SPC, KC_SPC, ML_LOW, ML_UPP, KC_PSCR, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

  [_LOWER] = KEY_LAYOUT( \
    S(KC_SCLN), KC_MINS,   S(JP_COLN), KC_SLSH,    S(KC_5),    S(KC_MINS),                   JP_CIRC,    JP_YEN,     KC_PEQL, KC_PSLS,  KC_PAST, KC_PMNS, \
    S(JP_YEN),  S(KC_6),   S(KC_1),    S(KC_SLSH), JP_AT,      JP_YEN,                       JP_AT,      JP_LBRC,    KC_P7,   KC_P8,    KC_P9,   KC_BSPC,  \
    S(KC_8),    S(KC_9),   JP_LBRC,    JP_RBRC,    S(JP_LBRC), S(JP_RBRC),                   JP_COLN,    JP_RBRC,    KC_P4,   KC_P5,    KC_P6,   KC_PENT, \
    S(KC_COMM), S(KC_DOT), S(JP_BSLS), JP_CIRC,    S(JP_AT),   S(JP_CIRC), KC_ENT,  KC_BSPC, KC_SLSH,    JP_BSLS,    KC_P1,   KC_P2,    KC_P3,   KC_RALT, \
    _______,    _______,   _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    _______, _______, S(KC_SLSH), S(JP_BSLS), KC_P0,   KC_COMMA, KC_PDOT, KC_PPLS \
    ),

  [_UPPER] = KEY_LAYOUT( \
    KC_F1,      KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11 , KC_F12 , \
    S(KC_CAPS), KC_NLCK, KC_CALC, KC_MYCM, KC_MAIL, KC_WHOM,                   _______, _______, KC_NLCK, KC_PSCR, KC_SLCK, KC_PAUSE, \
    KC_VOLD,    KC_VOLU, KC_MUTE, KC_MPLY, KC_MPRV, KC_MNXT,                   _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP,  \
    _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_END,  KC_PGDN,  \
    _______,    _______, MAC_WIN, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
    ),

  [_FF14] =  KEY_LAYOUT( \
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                      KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,    JP_CIRC , \
    C(KC_1), C(KC_2), C(KC_3), C(KC_4), C(KC_5), C(KC_6),                   C(KC_7), C(KC_8), C(KC_9), C(KC_0), C(KC_MINS), C(JP_CIRC) , \
    S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6),                   S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_MINS), S(JP_CIRC) , \
    A(KC_1), A(KC_2), A(KC_3), A(KC_4), A(KC_5), A(KC_6), KC_ENT,  KC_ESC,  A(KC_7), A(KC_8), A(KC_9), A(KC_0), A(KC_MINS), A(JP_CIRC) , \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______  \
    )
};


#ifdef RGBLIGHT_LAYERS

#define HSV_KEY_NONE 0,0,0
#define HSV_KEY_BASE 0,0,255
#define HSV_KEY_FUNC 6,210,255
#define HSV_KEY_ARROW 38,252,255
#define HSV_KEY_TENKEY 115,206,214
#define HSV_KEY_SPACE 182,150,241
#define HSV_KEY_LAYER_LOW 68,206,219
#define HSV_KEY_LAYER_HIGH 166,216,227
#define HSV_KEY_LAYER_FF14 187,167,232


const rgblight_segment_t PROGMEM led_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_KEY_FUNC },
    {6, 1, HSV_KEY_FUNC},
    {12, 1, HSV_KEY_FUNC},
    {18, 1, HSV_KEY_FUNC}, {24, 1, HSV_KEY_FUNC},
    {25, 3, HSV_KEY_FUNC}, {28, 1, HSV_KEY_LAYER_FF14 },
      {29, 1, HSV_KEY_LAYER_HIGH }, {30, 1, HSV_KEY_LAYER_LOW },
      {31, 1, HSV_KEY_SPACE },

    {38, 1, HSV_KEY_FUNC},
    {44, 1, HSV_KEY_FUNC},
    {50, 1, HSV_KEY_FUNC}, { 51, 1, HSV_KEY_ARROW }, { 56, 1, HSV_KEY_FUNC },
    {57, 3, HSV_KEY_ARROW}, { 60, 1, HSV_KEY_FUNC },
      {61, 1, HSV_KEY_LAYER_HIGH}, {62, 1, HSV_KEY_LAYER_LOW},
      {63, 1, HSV_KEY_SPACE }
);

const rgblight_segment_t PROGMEM rgb_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_KEY_LAYER_LOW},
    {6, 6, HSV_KEY_LAYER_LOW},
    {12, 6, HSV_KEY_LAYER_LOW},
    {18, 6, HSV_KEY_LAYER_LOW},

    {32, 4, HSV_KEY_TENKEY}, {36, 2, HSV_KEY_LAYER_LOW},
    {38, 1, HSV_KEY_FUNC}, {37, 3, HSV_KEY_TENKEY}, {42, 2, HSV_KEY_LAYER_LOW},
    {44, 1, HSV_KEY_FUNC}, {45, 3, HSV_KEY_TENKEY}, {48, 2, HSV_KEY_LAYER_LOW},
    {50, 1, HSV_KEY_FUNC}, {51, 3, HSV_KEY_TENKEY}, {54, 2, HSV_KEY_LAYER_LOW},
    {57, 4, HSV_KEY_TENKEY}, {61, 2, HSV_KEY_LAYER_LOW}
);

const rgblight_segment_t PROGMEM rgb_high_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_KEY_LAYER_HIGH},
    {6, 5, HSV_KEY_LAYER_HIGH},
    {12, 6, HSV_KEY_LAYER_HIGH},

    {32, 6, HSV_KEY_LAYER_HIGH},
    {38, 4, HSV_KEY_LAYER_HIGH},
    {44, 3, HSV_KEY_LAYER_HIGH},
    {50, 3, HSV_KEY_LAYER_HIGH}
);

const rgblight_segment_t PROGMEM rgb_ff14_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_KEY_LAYER_FF14},
    {6, 6, HSV_KEY_LAYER_FF14},
    {12, 6, HSV_KEY_LAYER_FF14},
    {18, 6, HSV_KEY_LAYER_FF14}, {24, 1, HSV_KEY_NONE},

    {32, 6, HSV_KEY_LAYER_FF14},
    {38, 6, HSV_KEY_LAYER_FF14},
    {44, 6, HSV_KEY_LAYER_FF14},
    {50, 6, HSV_KEY_LAYER_FF14}, {56, 1, HSV_KEY_NONE}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    led_base_layer,
    rgb_lower_layer,
    rgb_high_layer,
    rgb_ff14_layer
);

void init_rgb_layers(void){
    // 左側のボードなら色キャッシュ配列の0~31番を、
    // 右側のボードなら色キャッシュ配列の32～63番を反映させる
    rgblight_set_clipping_range(is_keyboard_master() ? 0 : 32, 32);

    // QMKが予約している変数に代入することで、照明レイヤーを初期化
    rgblight_layers = rgb_layers;

    rgblight_set_layer_state(0, true);
}
#endif

typedef union {
  uint32_t raw;
  struct {
    bool swap_alt_gui:1;
    bool enable_led:1;
  };
} user_config_t;
user_config_t user_config;

// サブキーボードに同期するデータ
typedef union {
  uint8_t raw;
  struct {
    bool swap_gui:1;
    bool mod_gui:1;
    bool caps_lock:1;
    bool num_lock:1;
    bool sc_lock:1;
  };
} key_state_r_t;
key_state_r_t key_state_r;

extern user_config_t user_config;

#ifdef OLED_DRIVER_ENABLE
// ビットマップ転送は負荷がかかるので、更新を必要最低限に
static bool require_oled_update = true;

void oled_update(bool update_left){
    bool m = is_keyboard_master();
    if(m == update_left) {
        require_oled_update = true;
    }else if(m == true){
        set_hremix_value(key_state_r.raw);
    }
}
#else
#define oled_update(ul)
#endif

// GUIキーとALTキーの位置を入れ替えるMacモード
void swap_alt_gui(bool swap) {
    key_state_r.swap_gui = swap;
    oled_update(false);

    if(user_config.swap_alt_gui != swap){
        user_config.swap_alt_gui = swap;
        keymap_config.swap_lalt_lgui = !swap;
        keymap_config.swap_ralt_rgui = !swap;

        eeconfig_update_user(user_config.raw);
    }
}

// EEPROMの初期化が必要なときに呼ばれる
void eeconfig_init_user(void) {
    user_config.raw = 0x00;
    eeconfig_update_user(user_config.raw);
}

// キーボード初期化後に呼ばれる
void keyboard_post_init_user(void) {
    key_state_r.raw = 0x00;

    // 設定の読み込み
    user_config.raw = eeconfig_read_user();
    swap_alt_gui(user_config.swap_alt_gui);

#ifdef RGBLIGHT_ENABLE
    init_rgblight(user_config.enable_led);
#endif

#ifdef RGBLIGHT_LAYERS
    init_rgb_layers();
#endif
}

// レイヤー状態が変更されたときに呼び出される
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_LAYERS
    // 変更されたレイヤーと一致する照明レイヤーのみを適用
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _UPPER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _FF14));

    oled_update(true);
#endif

    return state;
}

// キーが押されたときに呼び出される関数
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode != TD_FF14) tap_dance_active = false;

    switch (keycode) {
    case KC_LSFT:
    case KC_RSFT:
    case KC_LALT:
    case KC_RALT:
    case KC_LCTL:
    case KC_RCTL:
        oled_update(true);
        break;
    case KC_LGUI:
    case KC_RGUI:
        key_state_r.mod_gui = record->event.pressed;
        oled_update(false);
        break;
    case MAC_WIN:
        if (record->event.pressed) swap_alt_gui(!user_config.swap_alt_gui);
        oled_update(false);
        break;
    case RGB_TOG:
        user_config.enable_led = !rgblight_is_enabled();
        eeconfig_update_user(user_config.raw);
        break;
    }
    return true;
}

bool led_update_user(led_t led_state){
    key_state_r.caps_lock = led_state.caps_lock;
    key_state_r.num_lock = led_state.num_lock;
    key_state_r.sc_lock = led_state.scroll_lock;

    oled_update(false);

    return true;
}


#ifdef OLED_DRIVER_ENABLE
// OLEDを初期化するときに呼ばれる関数。戻り値は実際に適用する回転角度
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

void draw_state_bitmap(int index, int dx, int dy){
    draw_bitmap(oled_pct_layer,
        OP_LAYER_BW, OP_LAYER_BH, OP_LAYER_STRIDE,
        index % OP_LAYER_BX, index / OP_LAYER_BX,
        dx, dy, BmpRotate90);
}

void draw_left_status(void){
    const int dy = 1;
    int dx = OLED_DISPLAY_WIDTH;

    int index = 0;
    if(layer_state_cmp(layer_state, _FF14)){
        index = 3;
    }else if(layer_state_cmp(layer_state, _UPPER)){
        index = 2;
    }else if(layer_state_cmp(layer_state, _LOWER)){
        index = 1;
    }

    dx -= OP_LAYER_BH;
    draw_state_bitmap(index, dx, dy);

    int mods = get_mods();
    for(int i = 0; i < 3; i++){
        dx -= (OP_LAYER_BH + 1);

        bool on = false;
        switch(i){
        case 0: on = (mods & MOD_MASK_SHIFT) != 0; break;
        case 1: on = (mods & MOD_MASK_CTRL) != 0; break;
        case 2: on = (mods & MOD_MASK_ALT) != 0; break;
        }
        index = (8 + i * 2) + (on ? 1 : 0);

        draw_state_bitmap(index, dx, dy);
    }
}

void draw_right_status(void){
    const int dy = 1;
    int dx = OLED_DISPLAY_WIDTH;

    key_state_r.raw = get_hremix_value();
    int index = (key_state_r.swap_gui ? 4 : 6) + (key_state_r.mod_gui ? 1 : 0);

    dx -= OP_LAYER_BH;
    draw_state_bitmap(index, dx, dy);

    for(int i = 0; i < 3; i++){
        dx -= (OP_LAYER_BH + 1);

        bool on = false;
        switch(i){
        case 0: on = key_state_r.caps_lock; break;
        case 1: on = key_state_r.num_lock; break;
        case 2: on = key_state_r.sc_lock; break;
        }
        index = (14 + i * 2) + (on ? 1 : 0);

        draw_state_bitmap(index, dx, dy);
    }
}

// OLEDが更新されるときに呼び出される関数
void oled_task_user(void) {
    static uint8_t last_state = 0;
    uint8_t current_state = get_hremix_value();
    if(last_state != current_state){
        require_oled_update = true;
        last_state = current_state;
    }

    if(require_oled_update == false){
        return;
    }

    require_oled_update = false;

    if(is_keyboard_master()){
        draw_left_status();
    }else{
        draw_right_status();
    }
}
#endif

#include QMK_KEYBOARD_H

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
#define _LAYER6 6

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
    LAYER5,
    LAYER6,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                                       KC_Y, KC_U, KC_I, KC_O, KC_P,
        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,       KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN),
        KC_Z, KC_X, KC_C, KC_V, KC_B,                                       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        LT(_LAYER1,KC_ESC), LT(_LAYER2,KC_SPC), LT(_LAYER3,KC_ENT),         LT(_LAYER4,KC_DEL), LT(_LAYER5,KC_BSPC), LT(_LAYER6,KC_TAB),
        KC_MPLY
    ),
    [_LAYER1] = LAYOUT_split_3x5_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,                                 KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,                                                KC_MSTP, KC_MPLY, KC_MUTE,
        KC_MPLY
    ),
    [_LAYER2] = LAYOUT_split_3x5_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  LCTL(KC_Y), LCTL(KC_V), LCTL(KC_C), LCTL(KC_X), LCTL(KC_Z),
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                          LGUI(KC_TAB), KC_LEFT, KC_UP, KC_DOWN, KC_RGHT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  KC_INS, KC_HOME, KC_PGUP, KC_PGDN, KC_END,
        KC_NO, KC_NO, KC_NO,                                                KC_DEL, KC_BSPC, KC_TAB,
        KC_MPLY
    ),
    [_LAYER3] = LAYOUT_split_3x5_3(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  LCTL(KC_Y), LCTL(KC_V), LCTL(KC_C), LCTL(KC_X), LCTL(KC_Z),
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,                          KC_NO, KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                  KC_NO, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R,
        KC_NO, KC_NO, KC_NO,                                                KC_BTN2, KC_BTN1, KC_BTN3,
        KC_MPLY
    ),
    [_LAYER4] = LAYOUT_split_3x5_3(
        KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_COLN, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS,                         KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE,                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LPRN, KC_RPRN, KC_UNDS,                                          KC_NO, KC_NO, KC_NO,
        KC_MPLY
    ),
    [_LAYER5] = LAYOUT_split_3x5_3(
        KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_QUOT, KC_4, KC_5, KC_6, KC_EQL,                                  KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
        KC_GRV, KC_1, KC_2, KC_3, KC_BSLS,                                  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_DOT, KC_0, KC_MINS,                                              KC_NO, KC_NO, KC_NO,
        KC_MPLY
    ),
    [_LAYER6] = LAYOUT_split_3x5_3(
        KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL,                               KC_NO, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
        KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS,                               KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_APP, KC_SPC, KC_TAB,                                             KC_NO, KC_NO, KC_NO,
        KC_MPLY
    )
};
//
//const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    [0] = LAYOUT_split_3x5_3(
//        KC_Q, KC_W, KC_E, KC_R, KC_T,                                      KC_Y, KC_U, KC_I, KC_O, KC_P,
//        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,      KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN),
//        KC_Z, KC_X, KC_C, KC_V, KC_B,                                      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
//        KC_ESC, KC_SPC, KC_TAB,                                            MO(1), KC_BSPC, KC_ENT, KC_MPLY
//    ),
//    [1] = LAYOUT_split_3x5_3(
//        KC_NO, KC_7, KC_8, KC_9, KC_MINS,                                  KC_QUOT, KC_LBRC, KC_RBRC, KC_9, KC_0,
//        KC_NO, KC_4, KC_5, KC_6, KC_EQL,                                   KC_BSLS, KC_LPRN, KC_RPRN, KC_CIRC, KC_NO,
//        KC_NO, KC_1, KC_2, KC_3, MO(0),                                    KC_TILD, KC_NO, KC_COMM, KC_DOT, KC_NO,
//        KC_ESC, KC_SPC, KC_TAB,                                            MO(2), KC_BSPC, KC_ENT, KC_MPLY
//    ),
//    [2] = LAYOUT_split_3x5_3(
//        KC_NO, KC_F7, KC_F8, KC_F9, KC_F10,                                KC_PSCR, KC_SCRL, KC_PAUS, KC_LPRN, KC_RPRN,
//        KC_NO, KC_F4, KC_F5, KC_F6, KC_F11,                                KC_INS, KC_HOME, KC_PGUP, KC_RBRC, KC_BSLS,
//        KC_NO, KC_F1, KC_F2, KC_F3, KC_F12,                                KC_DEL, KC_END, KC_PGDN, KC_RCBR, KC_PIPE,
//        KC_ESC, KC_SPC, KC_TAB,                                            MO(3), KC_BSPC, KC_ENT, KC_MPLY
//    ),
//    [3] = LAYOUT_split_3x5_3(
//        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//        RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_NO,                         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//        RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_NO,                         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//        KC_ESC, KC_SPC, KC_TAB,                                            KC_TRNS, KC_ENT, KC_RALT, KC_MPLY
//    ),
//    [4] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
//    [5] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
//    [6] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
//    [7] = LAYOUT_split_3x5_3(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
//};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [1] =   { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)  },
    [2] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)  },
    [3] =   { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
    [4] =   { ENCODER_CCW_CW(KC_NO,KC_NO)  },
    [5] =   { ENCODER_CCW_CW(KC_NO,KC_NO)  },
    [6] =   { ENCODER_CCW_CW(KC_NO,KC_NO)  }//,
//    [7] =   { ENCODER_CCW_CW(KC_NO,KC_NO)  }
    //                  Encoder 1                                     Encoder 2
};

// Chordal Hold handedness configuration
// Define which keys are on the left (L) vs right (R) hand
// The encoder key in the middle is marked as '*' to exempt it from the opposite hands rule
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x5_3(
        'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',        'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L',                  'R', 'R', 'R', '*'
    );

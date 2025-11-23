// Reverie keymap for Iris Rev 8 split ortholinear keyboard
// Author: Matthew Spangler, github.com/mattyspangler
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    TURBO = SAFE_RANGE,
    JIGGLER,
};

bool jiggle_macro = false;
bool turbo_macro = false;

enum iris_layers {
    _BASE,        
    _FUNCTION,    
    _NUMBERS,     
    _SYMBOLS,     
    _SYSTEM,      
    _GAMING,      
    _MACRO,       
};

// Layer Aliases
#define QWERTY_LAYER _BASE
#define FN_LAYER _FUNCTION
#define NUM_LAYER _NUMBERS
#define SYM_LAYER _SYMBOLS
#define SYS_LAYER _SYSTEM
#define GAMING_LAYER _GAMING
#define MACRO_LAYER _MACRO

// Transparent key for readability
#define _______ KC_TRNS

// Custom HSV colors matching keymap-drawer-config.yaml
#define HSV_BASE_PURPLE 24, 255, 255      // #9300ff - Star Platinum Purple
#define HSV_FUNCTION_GREEN 83, 255, 238   // #0fee00 - Squeeze Toy Alien  
#define HSV_NUMBERS_BLUE 0, 255, 255      // #2000ff - Blue Pencil
#define HSV_SYMBOLS_RED 0, 255, 255        // #ff0000 - Red
#define HSV_SYSTEM_YELLOW 44, 255, 255   // #f6ff00 - Busy Bee
#define HSV_GAMING_TURQUOISE 178, 255, 255 // #00fff4 - Turquoise Blue
#define HSV_MACRO_PINK 79, 255, 255      // #ff008e - Pink Panther

// Layer toggling and momentary keys
#define TO_QW TO(QWERTY_LAYER)
#define TO_FN TO(FN_LAYER)
#define TO_NU TO(NUM_LAYER)
#define TO_SY TO(SYM_LAYER)
#define TO_MM TO(SYS_LAYER)
#define TO_GM TO(GAMING_LAYER)
#define TO_MA TO(MACRO_LAYER)

#define MO_FN MO(FN_LAYER)
#define MO_NU MO(NUM_LAYER)
#define MO_SY MO(SYM_LAYER)
#define MO_MM MO(SYS_LAYER)
#define MO_GM MO(GAMING_LAYER)
#define MO_MA MO(MACRO_LAYER)

// MACROS
#define KC_MACW LGUI(LSFT(KC_3)) // capture the whole screen on MacOS
#define KC_MACP LGUI(LSFT(KC_5)) // capture portion of the screen on MacOS
#define GUI_DWN LGUI(KC_DOWN) // jump to the bottom of the document
#define GUI_UP LGUI(KC_UP) // jump to the top of the document

// Tap dance declarations
enum tap_dance_codes {
    TD_LSFT_CAPS, // Left Shift or Caps Lock
    TD_GRV_ESC,   // Grave or Escape
    TD_RALT_ENT,  // Right Alt or Enter
    TD_LCTL_ESC,  // Left Control or Escape
    TD_LSPC,      // Left GUI or Space
    TD_1_L1,      // 1 tap, double-hold to switch to NUM layer
    TD_2_L2,      // 2 tap, double-hold to switch to NUM layer
    TD_3_L3,      // 3 tap, double-hold to switch to SYS layer
    TD_4_L4,      // 4 tap, double-hold to switch to GAMING layer
    TD_5_L5,      // 5 tap, double-hold to switch to MACRO layer
};

// Helper functions for advanced tap dance
typedef struct {
    bool is_press_action;
    uint8_t step;
} tap_state_t;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap_state_t tap_state[5];

uint8_t get_tap_dance_step(tap_dance_state_t *state);

uint8_t get_tap_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

// Tap dance for number 1 - tap for 1, double-hold for NUM layer
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[0].step = get_tap_dance_step(state);
    switch (tap_state[0].step) {
        case SINGLE_TAP: register_code16(KC_1); break;
        case DOUBLE_TAP: register_code16(KC_1); register_code16(KC_1); break;
        case DOUBLE_HOLD: layer_move(_FUNCTION); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_1); register_code16(KC_1); break;
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_1); break;
        case DOUBLE_TAP: unregister_code16(KC_1); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_1); break;
    }
    tap_state[0].step = 0;
}

// Tap dance for number 2 - tap for 2, double-hold for NUM layer
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[1].step = get_tap_dance_step(state);
    switch (tap_state[1].step) {
        case SINGLE_TAP: register_code16(KC_2); break;
        case DOUBLE_TAP: register_code16(KC_2); register_code16(KC_2); break;
        case DOUBLE_HOLD: layer_move(_NUMBERS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_2); register_code16(KC_2); break;
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_2); break;
        case DOUBLE_TAP: unregister_code16(KC_2); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_2); break;
    }
    tap_state[1].step = 0;
}

// Tap dance for number 3 - tap for 3, double-hold for MEDIA_MOUSE layer
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[2].step = get_tap_dance_step(state);
    switch (tap_state[2].step) {
        case SINGLE_TAP: register_code16(KC_3); break;
        case DOUBLE_TAP: register_code16(KC_3); register_code16(KC_3); break;
        case DOUBLE_HOLD: layer_move(_SYSTEM); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3); break;
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_3); break;
        case DOUBLE_TAP: unregister_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;
    }
    tap_state[2].step = 0;
}

// Tap dance for number 4 - tap for 4, double-hold for GAMING layer
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[3].step = get_tap_dance_step(state);
    switch (tap_state[3].step) {
        case SINGLE_TAP: register_code16(KC_4); break;
        case DOUBLE_TAP: register_code16(KC_4); register_code16(KC_4); break;
        case DOUBLE_HOLD: layer_move(GAMING_LAYER); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_4); register_code16(KC_4); break;
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_4); break;
        case DOUBLE_TAP: unregister_code16(KC_4); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_4); break;
    }
    tap_state[3].step = 0;
}

// Tap dance for number 5 - tap for 5, double-hold for MACRO layer
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[4].step = get_tap_dance_step(state);
    switch (tap_state[4].step) {
        case SINGLE_TAP: register_code16(KC_5); break;
        case DOUBLE_TAP: register_code16(KC_5); register_code16(KC_5); break;
        case DOUBLE_HOLD: layer_move(MACRO_LAYER); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_5); register_code16(KC_5); break;
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[4].step) {
        case SINGLE_TAP: unregister_code16(KC_5); break;
        case DOUBLE_TAP: unregister_code16(KC_5); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_5); break;
    }
    tap_state[4].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_GRV_ESC]   = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
    [TD_RALT_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_ENT),
    [TD_LCTL_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_ESC),
    [TD_LSPC]      = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_SPC),
    [TD_1_L1]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_finished, dance_1_reset),
    [TD_2_L2]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_finished, dance_2_reset),
    [TD_3_L3]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_finished, dance_3_reset),
    [TD_4_L4]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_4_finished, dance_4_reset),
    [TD_5_L5]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_finished, dance_5_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       TD(TD_GRV_ESC),   TD(TD_1_L1),    TD(TD_2_L2),    TD(TD_3_L3),    TD(TD_4_L4),    TD(TD_5_L5),                                             KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPC,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TAB,           KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                                    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       TD(TD_LSFT_CAPS), KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                    KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       TD(TD_LCTL_ESC),  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRC,                 KC_RBRC,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,      TD(TD_RALT_ENT),
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                         MO_FN,          TD(TD_LSPC),    KC_SPC,                  KC_SPC,         MO_SY,          TO_MA
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_FUNCTION] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_TRNS,          KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                                   KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_TRNS,        MS_UP,          KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_7,           KC_8,           KC_9,           KC_PLUS,        KC_F12,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_CAPS,          KC_TRNS,        MS_LEFT,        MS_DOWN,        MS_RGHT,        KC_TRNS,                                                 KC_TRNS,        KC_4,           KC_5,           KC_6,           KC_MINS,        KC_PAUS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        MS_BTN1,        MS_BTN3,        MS_BTN2,        KC_TRNS,        KC_TRNS,                 KC_TRNS,        KC_1,           KC_2,           KC_3,           KC_EQL,         KC_TRNS,        KC_TRNS,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                         KC_TRNS,        KC_TRNS,        KC_0,                    KC_0,           KC_DOT,         KC_TRNS
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_NUMBERS] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_TRNS,          KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                                 KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_BSPC,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_UP,          KC_TRNS,        KC_TRNS,                                                 KC_PGUP,        KC_HOME,        KC_UP,          KC_END,         KC_PGDN,        KC_PSCR,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRNS,                                                 KC_TRNS,        KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_INS,         KC_DEL,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_LCBR,        KC_RCBR,        KC_LBRC,        KC_RBRC,        KC_TRNS,                 KC_TRNS,        KC_MINS,        KC_EQL,         KC_SLSH,        KC_BSLS,        KC_QUOT,        KC_TRNS,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                         TO_QW,          KC_TRNS,        KC_TRNS,                 KC_TRNS,        MO_SY,          KC_TRNS
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_SYMBOLS] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                         TO(_BASE),         KC_TRNS,        KC_TRNS,                 KC_TRNS,        TO(_BASE),        KC_TRNS
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_SYSTEM] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        KC_TRNS,        MS_UP,          KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        MS_WHLU,        MS_WHLU,        MS_WHLD,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        MS_LEFT,        MS_DOWN,        MS_RGHT,        KC_TRNS,                                                 KC_TRNS,        MS_WHLL,        MS_WHLD,        MS_WHLR,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,          KC_TRNS,        MS_BTN1,        MS_BTN3,        MS_BTN2,        KC_TRNS,        KC_TRNS,                 KC_TRNS,        MS_BTN1,        MS_BTN3,        MS_BTN2,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                         TO(_FUNCTION),          KC_TRNS,        KC_TRNS,                 KC_TRNS,        TO(_GAMING),          KC_TRNS
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_GAMING] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_ESC,           KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                                    KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPC,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TAB,           KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                                    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_LSFT,          KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                    KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_LCTL,          KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRC,                 KC_RBRC,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_ENT,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
        KC_LGUI,        TO_MM,          KC_SPC,                  KC_SPC,         TO_MA,          KC_RALT
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_MACRO] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       _______,          _______,        _______,        _______,        _______,        TURBO,                                                   _______,        _______,        _______,        _______,        QK_BOOT,        EE_CLR,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       _______,          _______,        _______,        _______,        _______,        _______,                                                 _______,        _______,        _______,        _______,        _______,        _______,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       _______,          _______,        _______,        _______,        _______,        _______,                                                 _______,        JIGGLER,        _______,        _______,        _______,        _______,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       _______,          _______,        _______,        _______,        _______,        _______,        _______,                 _______,        _______,        _______,        _______,        _______,        _______,        _______,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                         _______,        TO(_GAMING),          _______,                 _______,        TO_QW,          _______
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    )
};

// --------------------------
// RGB Lighting Configuration
// --------------------------

/*

LED index mapping:

          (31)              (32)              (33)                                    (67)              (66)              (65)
┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
│0       │1       │2       │3       │4       │5       │                          │39      │38      │37      │36      │35      │34      │
├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
│11      │10      │9       │8       │7       │6       │                          │40      │41      │42      │43      │44      │45      │
├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
│12      │13      │14      │15      │16      │17      │                          │51      │50      │49      │48      │47      │46      │
├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
│23      │22      │21      │20      │19      │18      │27      │        │61      │52      │53      │54      │55      │56      │57      │
└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                               │24      │25      │26      │                 │60      │59      │58      │
                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
          (30)              (29)              (28)                                    (62)              (63)              (64)

*/

const rgblight_segment_t PROGMEM BASE_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side - Base purple (Star Platinum Purple: #9300ff = HSV(280,255,255))
    {0, 6, HSV_BASE_PURPLE},
    {6, 6, HSV_BASE_PURPLE},
    {12, 6, HSV_BASE_PURPLE},
    {18, 6, HSV_BASE_PURPLE},
    {24, 1, HSV_BASE_PURPLE},
    {25, 1, HSV_BASE_PURPLE},
    {26, 1, HSV_BASE_PURPLE},
    {27, 1, HSV_BASE_PURPLE},
    {28, 3, HSV_BASE_PURPLE}, // underglow
    {31, 3, HSV_BASE_PURPLE}, // underglow
    // right side
    {34, 6, HSV_BASE_PURPLE},
    {40, 6, HSV_BASE_PURPLE},
    {46, 6, HSV_BASE_PURPLE},
    {52, 6, HSV_BASE_PURPLE},
    {58, 1, HSV_BASE_PURPLE},
    {59, 1, HSV_BASE_PURPLE},
    {60, 1, HSV_BASE_PURPLE},
    {61, 1, HSV_BASE_PURPLE},
    {62, 3, HSV_BASE_PURPLE}, // underglow
    {65, 3, HSV_BASE_PURPLE} // underglow
);

const rgblight_segment_t PROGMEM FUNCTION_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side - Function green (Squeeze Toy Alien: #0fee00 = HSV(83,255,238))
    {0, 6, HSV_FUNCTION_GREEN},
    {6, 6, HSV_FUNCTION_GREEN},
    {12, 6, HSV_FUNCTION_GREEN},
    {18, 6, HSV_FUNCTION_GREEN},
    {24, 4, HSV_FUNCTION_GREEN},
    {28, 3, HSV_FUNCTION_GREEN}, // underglow
    {31, 3, HSV_FUNCTION_GREEN}, // underglow
    // right side
    {34, 6, HSV_FUNCTION_GREEN},
    {40, 6, HSV_FUNCTION_GREEN},
    {46, 6, HSV_FUNCTION_GREEN},
    {52, 6, HSV_FUNCTION_GREEN},
    {58, 1, HSV_FUNCTION_GREEN},
    {59, 1, HSV_FUNCTION_GREEN},
    {60, 2, HSV_FUNCTION_GREEN},
    {62, 3, HSV_FUNCTION_GREEN}, // underglow
    {65, 3, HSV_FUNCTION_GREEN} // underglow
);

const rgblight_segment_t PROGMEM NUMBERS_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side - Numbers blue (Blue Pencil: #2000ff = HSV(240,255,255))
    {0, 6, HSV_NUMBERS_BLUE},
    {6, 6, HSV_NUMBERS_BLUE},
    {12, 6, HSV_NUMBERS_BLUE},
    {18, 6, HSV_NUMBERS_BLUE},
    {24, 4, HSV_NUMBERS_BLUE},
    {28, 3, HSV_NUMBERS_BLUE}, // underglow
    {31, 3, HSV_NUMBERS_BLUE}, // underglow
    // right side
    {34, 6, HSV_NUMBERS_BLUE},
    {40, 6, HSV_NUMBERS_BLUE},
    {46, 6, HSV_NUMBERS_BLUE},
    {52, 6, HSV_NUMBERS_BLUE},
    {58, 2, HSV_NUMBERS_BLUE},
    {60, 1, HSV_NUMBERS_BLUE},
    {61, 1, HSV_NUMBERS_BLUE},
    {62, 3, HSV_NUMBERS_BLUE}, // underglow
    {65, 3, HSV_NUMBERS_BLUE} // underglow
);

const rgblight_segment_t PROGMEM SYMBOLS_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side - Symbols red (Red: #ff0000 = HSV(0,255,255))
    {0, 6, HSV_SYMBOLS_RED},
    {6, 6, HSV_SYMBOLS_RED},
    {12, 6, HSV_SYMBOLS_RED},
    {18, 6, HSV_SYMBOLS_RED},
    {24, 4, HSV_SYMBOLS_RED},
    {28, 3, HSV_SYMBOLS_RED}, // underglow
    {31, 3, HSV_SYMBOLS_RED}, // underglow
    // right side
    {34, 6, HSV_SYMBOLS_RED},
    {40, 6, HSV_SYMBOLS_RED},
    {46, 6, HSV_SYMBOLS_RED},
    {52, 6, HSV_SYMBOLS_RED},
    {58, 4, HSV_SYMBOLS_RED},
    {60, 2, HSV_SYMBOLS_RED},
    {61, 2, HSV_SYMBOLS_RED},
    {62, 3, HSV_SYMBOLS_RED}, // underglow
    {65, 3, HSV_SYMBOLS_RED} // underglow
);

const rgblight_segment_t PROGMEM SYSTEM_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side - System yellow (Busy Bee: #f6ff00 = HSV(61,255,255))
    {0, 6, HSV_SYSTEM_YELLOW},
    {6, 6, HSV_SYSTEM_YELLOW},
    {12, 6, HSV_SYSTEM_YELLOW},
    {18, 6, HSV_SYSTEM_YELLOW},
    {24, 2, HSV_SYSTEM_YELLOW},
    {26, 1, HSV_SYSTEM_YELLOW},
    {27, 1, HSV_SYSTEM_YELLOW},
    {28, 3, HSV_SYSTEM_YELLOW}, // underglow
    {31, 3, HSV_SYSTEM_YELLOW}, // underglow
    // right side
    {34, 6, HSV_SYSTEM_YELLOW},
    {40, 6, HSV_SYSTEM_YELLOW},
    {46, 6, HSV_SYSTEM_YELLOW},
    {52, 6, HSV_SYSTEM_YELLOW},
    {58, 4, HSV_SYSTEM_YELLOW},
    {62, 3, HSV_SYSTEM_YELLOW}, // underglow
    {65, 3, HSV_SYSTEM_YELLOW} // underglow
);

const rgblight_segment_t PROGMEM GAMING_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side - Gaming turquoise (Turquoise Blue: #00fff4 = HSV(178,255,255))
    {0, 6, HSV_GAMING_TURQUOISE},
    {6, 6, HSV_GAMING_TURQUOISE},
    {12, 6, HSV_GAMING_TURQUOISE},
    {18, 6, HSV_GAMING_TURQUOISE},
    {24, 2, HSV_GAMING_TURQUOISE},
    {26, 1, HSV_GAMING_TURQUOISE},
    {27, 1, HSV_GAMING_TURQUOISE},
    {28, 3, HSV_GAMING_TURQUOISE}, // underglow
    {31, 3, HSV_GAMING_TURQUOISE}, // underglow
    // right side
    {34, 6, HSV_GAMING_TURQUOISE},
    {40, 6, HSV_GAMING_TURQUOISE},
    {46, 6, HSV_GAMING_TURQUOISE},
    {52, 6, HSV_GAMING_TURQUOISE},
    {58, 2, HSV_GAMING_TURQUOISE},
    {60, 1, HSV_GAMING_TURQUOISE},
    {61, 1, HSV_GAMING_TURQUOISE},
    {62, 3, HSV_GAMING_TURQUOISE}, // underglow
    {65, 3, HSV_GAMING_TURQUOISE} // underglow
);

const rgblight_segment_t PROGMEM MACRO_LIGHT_LAYER[] = RGBLIGHT_LAYER_SEGMENTS(
    // left side - Macro pink (Pink Panther: #ff008e = HSV(335,255,255))
    {0, 6, HSV_MACRO_PINK},
    {6, 6, HSV_MACRO_PINK},
    {12, 6, HSV_MACRO_PINK},
    {18, 6, HSV_MACRO_PINK},
    {24, 2, HSV_MACRO_PINK},
    {26, 1, HSV_MACRO_PINK},
    {27, 1, HSV_MACRO_PINK},
    {28, 3, HSV_MACRO_PINK}, // underglow
    {31, 3, HSV_MACRO_PINK}, // underglow
    // right side
    {34, 6, HSV_MACRO_PINK},
    {40, 6, HSV_MACRO_PINK},
    {46, 6, HSV_MACRO_PINK},
    {52, 6, HSV_MACRO_PINK},
    {58, 4, HSV_MACRO_PINK},
    {62, 3, HSV_MACRO_PINK}, // underglow
    {65, 3, HSV_MACRO_PINK} // underglow
);

const rgblight_segment_t* const PROGMEM MY_LIGHT_LAYERS[] = RGBLIGHT_LAYERS_LIST(
    BASE_LIGHT_LAYER,
    FUNCTION_LIGHT_LAYER,
    NUMBERS_LIGHT_LAYER,
    SYMBOLS_LIGHT_LAYER,
    SYSTEM_LIGHT_LAYER,
    GAMING_LIGHT_LAYER,
    MACRO_LIGHT_LAYER
);

void keyboard_post_init_user(void) {
    rgblight_layers = MY_LIGHT_LAYERS;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_BASE, layer_state_cmp(state, _BASE));

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FUNCTION));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUMBERS));
    rgblight_set_layer_state(3, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(4, layer_state_cmp(state, _SYSTEM));
    rgblight_set_layer_state(5, layer_state_cmp(state, _GAMING));
    rgblight_set_layer_state(6, layer_state_cmp(state, _MACRO));
    return state;
}

static int counter = 0;
static int c1;
static int c2;

void do_jiggle(void) {
    counter = counter + 1;
    SEND_STRING(SS_DELAY(1));
    c1 = counter % 13;
    c2 = counter % 37;
    if (c1 == 0) {
        SEND_STRING(SS_DELAY(10000));
        tap_code(MS_UP);
        tap_code(MS_DOWN);
    }
    if (c2 == 0) {
        SEND_STRING(SS_DELAY(30000));
        tap_code(MS_LEFT);
        tap_code(MS_RGHT);
    }
    if (counter == 1000) {
        counter = 0;
    }
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
    if (jiggle_macro) {
        do_jiggle();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case JIGGLER:
            if (record->event.pressed) {
                jiggle_macro = !jiggle_macro;
                if (jiggle_macro) {
                    // Turn on a light or provide feedback
                    rgblight_setrgb(0x00, 0xFF, 0x00); // Green
                } else {
                    // Turn off the light or revert feedback
                    rgblight_setrgb(0xFF, 0x00, 0x00); // Red
                }
            }
            return false;
        case TURBO:
            if (record->event.pressed) {
                turbo_macro = !turbo_macro;
                if (turbo_macro) {
                    rgblight_setrgb(0x00, 0x00, 0xFF); // Blue
                } else {
                    rgblight_setrgb(0xFF, 0x00, 0x00); // Red
                }
            }
            return false;
    }
    return true;
}

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

// Layer system - IMPORTANT: Follow this pattern when adding new layers
// 1. Add new layer enum entry here with _PREFIX format (e.g., _NEWLAYER)
// 2. Add corresponding layer alias below (e.g., #define NEW_LAYER _NEWLAYER)
// 3. Add RGB layer definition with HSV color below
// 4. Add layer to keymaps[] array in the correct order
// 5. Add RGB light layer to MY_LIGHT_LAYERS array
// 6. Add layer case to layer_state_set_user() function
// 7. Add CSS styling rule to keymap-drawer-config.yaml (svg.keymap g.layer-NEWLAYER)
// 8. Add text styling rule to keymap-drawer-config.yaml for proper contrast
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
#define HSV_NUMBERS_BLUE 240, 255, 255     // #2000ff - Blue Pencil
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

// Tap dance declarations - based on Moonlander implementation
enum tap_dance_codes {
    TD_LSFT_CAPS, // Left Shift or Caps Lock
    TD_GRV_ESC,   // Grave or Escape
    TD_RALT_ENT,  // Right Alt or Enter
    TD_LCTL_ESC,  // Left Control or Escape - DEPRECATED
    TD_LSPC,      // Left GUI or Space
    // Moonlander-style number tap dances (DANCE_0-4 equivalent)
    TD_1_FN,      // 1 tap, double-hold to switch to FUNCTION layer
    TD_2_NUM,     // 2 tap, double-hold to switch to NUMBERS layer
    TD_3_SYS,     // 3 tap, double-hold to switch to SYSTEM layer
    TD_4_GAME,    // 4 tap, double-hold to switch to GAMING layer
    TD_5_MACRO,   // 5 tap, double-hold to switch to MACRO layer
    // Additional Moonlander utility tap dances where space allows
    TD_6_BS,      // 6 tap, double-tap and hold for base layer
    TD_9_MIN,     // 9 tap, double-tap and hold for minus
    TD_0_EQ,      // 0 tap, double-tap and hold for equals
    TD_ENT_BSLS,   // Enter tap, double-tap and hold for backslash
    TD_BSLS_RSFT,  // Backslash tap, double-tap and hold for right shift
    TD_LCTL_GAME,  // Left Control tap, double-hold for GAMING layer
    TD_MEDIA_PREV, // Media Previous tap, double-tap for browser back
    TD_MEDIA_PLAY, // Media Play/Pause tap, double-tap for browser home
    TD_MEDIA_NEXT, // Media Next tap, double-tap for browser forward
    TD_LCTL_BASE, // Left Control tap, double-hold to return to base layer
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

static tap_state_t tap_state[15]; // Array for 15 tap dances

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

// Moonlander-style tap dance for number 1 - tap for 1, double-hold for FUNCTION layer
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_fn_finished(tap_dance_state_t *state, void *user_data);
void dance_1_fn_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_1);
        tap_code16(KC_1);
        tap_code16(KC_1);
    }
    if(state->count > 3) {
        tap_code16(KC_1);
    }
}

void dance_1_fn_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[0].step = get_tap_dance_step(state);
    switch (tap_state[0].step) {
        case SINGLE_TAP: register_code16(KC_1); break;
        case DOUBLE_TAP: register_code16(KC_1); register_code16(KC_1); break;
        case DOUBLE_HOLD: layer_move(_FUNCTION); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_1); register_code16(KC_1);
    }
}

void dance_1_fn_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_1); break;
        case DOUBLE_TAP: unregister_code16(KC_1); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_1); break;
    }
    tap_state[0].step = 0;
}

// Moonlander-style tap dance for number 2 - tap for 2, double-hold for NUMBERS layer
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_num_finished(tap_dance_state_t *state, void *user_data);
void dance_2_num_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_2);
        tap_code16(KC_2);
        tap_code16(KC_2);
    }
    if(state->count > 3) {
        tap_code16(KC_2);
    }
}

void dance_2_num_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[1].step = get_tap_dance_step(state);
    switch (tap_state[1].step) {
        case SINGLE_TAP: register_code16(KC_2); break;
        case DOUBLE_TAP: register_code16(KC_2); register_code16(KC_2); break;
        case DOUBLE_HOLD: layer_move(_NUMBERS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_2); register_code16(KC_2);
    }
}

void dance_2_num_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_2); break;
        case DOUBLE_TAP: unregister_code16(KC_2); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_2); break;
    }
    tap_state[1].step = 0;
}

// Moonlander-style tap dance for number 3 - tap for 3, double-hold for SYSTEM layer
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_sys_finished(tap_dance_state_t *state, void *user_data);
void dance_3_sys_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_3);
        tap_code16(KC_3);
        tap_code16(KC_3);
    }
    if(state->count > 3) {
        tap_code16(KC_3);
    }
}

void dance_3_sys_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[2].step = get_tap_dance_step(state);
    switch (tap_state[2].step) {
        case SINGLE_TAP: register_code16(KC_3); break;
        case DOUBLE_TAP: register_code16(KC_3); register_code16(KC_3); break;
        case DOUBLE_HOLD: layer_move(_SYSTEM); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3);
    }
}

void dance_3_sys_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_3); break;
        case DOUBLE_TAP: unregister_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;
    }
    tap_state[2].step = 0;
}

// Moonlander-style tap dance for number 4 - tap for 4, double-hold for GAMING layer
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_game_finished(tap_dance_state_t *state, void *user_data);
void dance_4_game_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_4);
        tap_code16(KC_4);
        tap_code16(KC_4);
    }
    if(state->count > 3) {
        tap_code16(KC_4);
    }
}

void dance_4_game_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[3].step = get_tap_dance_step(state);
    switch (tap_state[3].step) {
        case SINGLE_TAP: register_code16(KC_4); break;
        case DOUBLE_TAP: register_code16(KC_4); register_code16(KC_4); break;
        case DOUBLE_HOLD: layer_move(_GAMING); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_4); register_code16(KC_4);
    }
}

void dance_4_game_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_4); break;
        case DOUBLE_TAP: unregister_code16(KC_4); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_4); break;
    }
    tap_state[3].step = 0;
}

// Moonlander-style tap dance for number 5 - tap for 5, double-hold for MACRO layer
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_macro_finished(tap_dance_state_t *state, void *user_data);
void dance_5_macro_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_5);
        tap_code16(KC_5);
        tap_code16(KC_5);
    }
    if(state->count > 3) {
        tap_code16(KC_5);
    }
}

void dance_5_macro_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[4].step = get_tap_dance_step(state);
    switch (tap_state[4].step) {
        case SINGLE_TAP: register_code16(KC_5); break;
        case DOUBLE_TAP: register_code16(KC_5); register_code16(KC_5); break;
        case DOUBLE_HOLD: layer_move(_MACRO); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_5); register_code16(KC_5);
    }
}

void dance_5_macro_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[4].step) {
        case SINGLE_TAP: unregister_code16(KC_5); break;
        case DOUBLE_TAP: unregister_code16(KC_5); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_5); break;
    }
    tap_state[4].step = 0;
}

// Moonlander-style tap dance for number 6 - tap for 6, double-hold for backspace functionality
void on_dance_6(tap_dance_state_t *state, void *user_data);
void dance_6_bsp_finished(tap_dance_state_t *state, void *user_data);
void dance_6_bsp_reset(tap_dance_state_t *state, void *user_data);

void on_dance_6(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_6);
        tap_code16(KC_6);
        tap_code16(KC_6);
    }
    if(state->count > 3) {
        tap_code16(KC_6);
    }
}

void dance_6_bsp_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[5].step = get_tap_dance_step(state);
    switch (tap_state[5].step) {
        case SINGLE_TAP: register_code16(KC_6); break;
        case DOUBLE_TAP: register_code16(KC_6); register_code16(KC_6); break;
        case DOUBLE_HOLD: layer_move(_BASE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_6); register_code16(KC_6);
    }
}

void dance_6_bsp_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[5].step) {
        case SINGLE_TAP: unregister_code16(KC_6); break;
        case DOUBLE_TAP: unregister_code16(KC_6); break;
        case DOUBLE_HOLD: break; // No unregister needed for layer move
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_6); break;
    }
    tap_state[5].step = 0;
}

// Moonlander-style tap dance for 9/Minus - tap for 9, double-tap and hold for minus
void on_dance_9(tap_dance_state_t *state, void *user_data);
void dance_9_ent_finished(tap_dance_state_t *state, void *user_data);
void dance_9_ent_reset(tap_dance_state_t *state, void *user_data);

void on_dance_9(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_9);
        tap_code16(KC_9);
        tap_code16(KC_9);
    }
    if(state->count > 3) {
        tap_code16(KC_9);
    }
}

void dance_9_min_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[6].step = get_tap_dance_step(state);
    switch (tap_state[6].step) {
        case SINGLE_TAP: register_code16(KC_9); break;
        case DOUBLE_TAP: register_code16(KC_9); register_code16(KC_9); break;
        case DOUBLE_HOLD: register_code16(KC_MINS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_9); register_code16(KC_9);
    }
}

void dance_9_min_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[6].step) {
        case SINGLE_TAP: unregister_code16(KC_9); break;
        case DOUBLE_TAP: unregister_code16(KC_9); break;
        case DOUBLE_HOLD: unregister_code16(KC_MINS); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_9); break;
    }
    tap_state[6].step = 0;
}

// Left Control tap dance - tap for Left Control, double-hold to return to base layer
void on_dance_lctl_base(tap_dance_state_t *state, void *user_data);
void dance_lctl_base_finished(tap_dance_state_t *state, void *user_data);
void dance_lctl_base_reset(tap_dance_state_t *state, void *user_data);

void on_dance_lctl_base(tap_dance_state_t *state, void *user_data) {
    // No special multi-tap functionality needed for this one
}

void dance_lctl_base_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[7].step = get_tap_dance_step(state);
    switch (tap_state[7].step) {
        case SINGLE_TAP: register_code16(KC_LCTL); break;
        case SINGLE_HOLD: register_code16(KC_LCTL); break;
        case DOUBLE_TAP: register_code16(KC_LCTL); register_code16(KC_LCTL); break;
        case DOUBLE_HOLD: layer_move(_BASE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LCTL); register_code16(KC_LCTL);
    }
}

void dance_lctl_base_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[7].step) {
        case SINGLE_TAP: unregister_code16(KC_LCTL); break;
        case SINGLE_HOLD: unregister_code16(KC_LCTL); break;
        case DOUBLE_TAP: unregister_code16(KC_LCTL); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LCTL); break;
    }
    tap_state[7].step = 0;
}

// 0 key tap dance - tap for 0, double-tap and hold for equals
void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_eq_finished(tap_dance_state_t *state, void *user_data);
void dance_0_eq_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_0);
        tap_code16(KC_0);
        tap_code16(KC_0);
    }
    if(state->count > 3) {
        tap_code16(KC_0);
    }
}

void dance_0_eq_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[8].step = get_tap_dance_step(state);
    switch (tap_state[8].step) {
        case SINGLE_TAP: register_code16(KC_0); break;
        case DOUBLE_TAP: register_code16(KC_0); register_code16(KC_0); break;
        case DOUBLE_HOLD: register_code16(KC_EQL); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_0); register_code16(KC_0);
    }
}

void dance_0_eq_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[8].step) {
        case SINGLE_TAP: unregister_code16(KC_0); break;
        case DOUBLE_TAP: unregister_code16(KC_0); break;
        case DOUBLE_HOLD: unregister_code16(KC_EQL); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_0); break;
    }
    tap_state[8].step = 0;
}

// Enter or Backslash tap dance functions
void on_dance_ent_bsls(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
    }
    if (state->count > 3) {
        tap_code16(KC_ENT);
    }
}

void dance_ent_bsls_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[9].step = get_tap_dance_step(state);
    switch (tap_state[9].step) {
        case SINGLE_TAP: register_code16(KC_ENT); break;
        case SINGLE_HOLD: register_code16(KC_ENT); break;
        case DOUBLE_TAP: register_code16(KC_ENT); break;
        case DOUBLE_HOLD: register_code16(KC_BSLS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ENT); register_code16(KC_ENT);
    }
}

void dance_ent_bsls_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[9].step) {
        case SINGLE_TAP: unregister_code16(KC_ENT); break;
        case DOUBLE_TAP: unregister_code16(KC_ENT); break;
        case DOUBLE_HOLD: unregister_code16(KC_BSLS); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ENT); break;
    }
    tap_state[9].step = 0;
}

// Backslash or Right Shift tap dance functions
void on_dance_bsls_rsft(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_BSLS);
        tap_code16(KC_BSLS);
    }
    if (state->count > 3) {
        tap_code16(KC_BSLS);
    }
}

void dance_bsls_rsft_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[10].step = get_tap_dance_step(state);
    switch (tap_state[10].step) {
        case SINGLE_TAP: register_code16(KC_BSLS); break;
        case SINGLE_HOLD: register_code16(KC_BSLS); break;
        case DOUBLE_TAP: register_code16(KC_BSLS); break;
        case DOUBLE_HOLD: register_code16(KC_RSFT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_BSLS); register_code16(KC_BSLS);
    }
}

void dance_bsls_rsft_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[10].step) {
        case SINGLE_TAP: unregister_code16(KC_BSLS); break;
        case DOUBLE_TAP: unregister_code16(KC_BSLS); break;
        case DOUBLE_HOLD: unregister_code16(KC_RSFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_BSLS); break;
    }
    tap_state[10].step = 0;
}

// Left Control or Gaming layer tap dance functions
void on_dance_lctl_game(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_LCTL);
        tap_code16(KC_LCTL);
    }
    if (state->count > 3) {
        tap_code16(KC_LCTL);
    }
}

void dance_lctl_game_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[11].step = get_tap_dance_step(state);
    switch (tap_state[11].step) {
        case SINGLE_TAP: register_code16(KC_LCTL); break;
        case SINGLE_HOLD: register_code16(KC_LCTL); break;
        case DOUBLE_TAP: register_code16(KC_LCTL); break;
        case DOUBLE_HOLD: layer_move(_GAMING); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LCTL); register_code16(KC_LCTL);
    }
}

void dance_lctl_game_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[11].step) {
        case SINGLE_TAP: unregister_code16(KC_LCTL); break;
        case DOUBLE_TAP: unregister_code16(KC_LCTL); break;
        case DOUBLE_HOLD: break; // No need to unregister layer move
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LCTL); break;
    }
    tap_state[11].step = 0;
}

// Media Previous or Browser Back tap dance functions
void on_dance_media_prev(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_MEDIA_PREV_TRACK);
        tap_code16(KC_MEDIA_PREV_TRACK);
        tap_code16(KC_MEDIA_PREV_TRACK);
    }
    if (state->count > 3) {
        tap_code16(KC_MEDIA_PREV_TRACK);
    }
}

void dance_media_prev_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[12].step = get_tap_dance_step(state);
    switch (tap_state[12].step) {
        case SINGLE_TAP: register_code16(KC_MEDIA_PREV_TRACK); break;
        case DOUBLE_TAP: register_code16(KC_WWW_BACK); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MEDIA_PREV_TRACK); register_code16(KC_MEDIA_PREV_TRACK);
    }
}

void dance_media_prev_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[12].step) {
        case SINGLE_TAP: unregister_code16(KC_MEDIA_PREV_TRACK); break;
        case DOUBLE_TAP: unregister_code16(KC_WWW_BACK); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MEDIA_PREV_TRACK); break;
    }
    tap_state[12].step = 0;
}

// Media Play/Pause or Browser Home tap dance functions
void on_dance_media_play(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_MEDIA_PLAY_PAUSE);
        tap_code16(KC_MEDIA_PLAY_PAUSE);
        tap_code16(KC_MEDIA_PLAY_PAUSE);
    }
    if (state->count > 3) {
        tap_code16(KC_MEDIA_PLAY_PAUSE);
    }
}

void dance_media_play_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[13].step = get_tap_dance_step(state);
    switch (tap_state[13].step) {
        case SINGLE_TAP: register_code16(KC_MEDIA_PLAY_PAUSE); break;
        case DOUBLE_TAP: register_code16(KC_WWW_HOME); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MEDIA_PLAY_PAUSE); register_code16(KC_MEDIA_PLAY_PAUSE);
    }
}

void dance_media_play_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[13].step) {
        case SINGLE_TAP: unregister_code16(KC_MEDIA_PLAY_PAUSE); break;
        case DOUBLE_TAP: unregister_code16(KC_WWW_HOME); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MEDIA_PLAY_PAUSE); break;
    }
    tap_state[13].step = 0;
}

// Media Next or Browser Forward tap dance functions
void on_dance_media_next(tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        tap_code16(KC_MEDIA_NEXT_TRACK);
        tap_code16(KC_MEDIA_NEXT_TRACK);
        tap_code16(KC_MEDIA_NEXT_TRACK);
    }
    if (state->count > 3) {
        tap_code16(KC_MEDIA_NEXT_TRACK);
    }
}

void dance_media_next_finished(tap_dance_state_t *state, void *user_data) {
    tap_state[14].step = get_tap_dance_step(state);
    switch (tap_state[14].step) {
        case SINGLE_TAP: register_code16(KC_MEDIA_NEXT_TRACK); break;
        case DOUBLE_TAP: register_code16(KC_WWW_FORWARD); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MEDIA_NEXT_TRACK); register_code16(KC_MEDIA_NEXT_TRACK);
    }
}

void dance_media_next_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state[14].step) {
        case SINGLE_TAP: unregister_code16(KC_MEDIA_NEXT_TRACK); break;
        case DOUBLE_TAP: unregister_code16(KC_WWW_FORWARD); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MEDIA_NEXT_TRACK); break;
    }
    tap_state[14].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_GRV_ESC]   = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
    [TD_RALT_ENT]  = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_ENT),
    [TD_LSPC]      = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_SPC),
    [TD_1_FN]      = ACTION_TAP_DANCE_DOUBLE(KC_1, MO(_FUNCTION)),  // 1 tap, tap-hold for FUNCTION layer
    [TD_2_NUM]     = ACTION_TAP_DANCE_DOUBLE(KC_2, MO(_NUMBERS)),   // 2 tap, tap-hold for NUMBERS layer
    [TD_3_SYS]     = ACTION_TAP_DANCE_DOUBLE(KC_3, MO(_SYSTEM)),    // 3 tap, tap-hold for SYSTEM layer
    [TD_4_GAME]    = ACTION_TAP_DANCE_DOUBLE(KC_4, MO(_GAMING)),    // 4 tap, tap-hold for GAMING layer
    [TD_5_MACRO]   = ACTION_TAP_DANCE_DOUBLE(KC_5, MO(_MACRO)),     // 5 tap, tap-hold for MACRO layer
    [TD_6_BS]      = ACTION_TAP_DANCE_DOUBLE(KC_6, MO(_BASE)),       // 6 tap, tap-hold for BASE layer
    [TD_9_MIN]     = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_MINS),        // 9 tap, tap-hold for minus
    [TD_0_EQ]      = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_EQL),         // 0 tap, tap-hold for equals
    [TD_ENT_BSLS]  = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_BSLS),      // Enter tap, tap-hold for backslash
    [TD_BSLS_RSFT] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_RSFT),     // Backslash tap, tap-hold for right shift
    [TD_LCTL_GAME] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, MO(_GAMING)),  // Left Control tap, tap-hold for GAMING layer
    [TD_MEDIA_PREV] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_media_prev, dance_media_prev_finished, dance_media_prev_reset),  // Media Previous tap, double-tap for browser back
    [TD_MEDIA_PLAY] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_media_play, dance_media_play_finished, dance_media_play_reset),  // Media Play/Pause tap, double-tap for browser home
    [TD_MEDIA_NEXT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_media_next, dance_media_next_finished, dance_media_next_reset),  // Media Next tap, double-tap for browser forward
    [TD_LCTL_BASE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_lctl_base, dance_lctl_base_finished, dance_lctl_base_reset),  // LCTL tap, double-hold for BASE layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       TD(TD_GRV_ESC), TD(TD_1_FN),    TD(TD_2_NUM),   TD(TD_3_SYS),   TD(TD_4_GAME),  TD(TD_5_MACRO),                                          TD(TD_6_BS),    KC_7,           KC_8,           TD(TD_9_MIN),   TD(TD_0_EQ),    KC_BSPC,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                                    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_QUOT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
      TD(TD_LSFT_CAPS),KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                    KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_ENT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
      TD(TD_LCTL_GAME),KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRC,                 KC_RBRC,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        TD(TD_BSLS_RSFT),
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                       KC_LGUI,        MO_FN,          KC_SPC,                  KC_SPC,         MO_NU,          KC_RCTL
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_FUNCTION] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_ESC,         KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,          KC_MINS,      KC_EQL,         KC_DELETE,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,        KC_TRNS,        KC_TRNS,        MS_UP,          KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_UP,          KC_LBRC,        KC_RBRC,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_CAPS,        KC_TRNS,        MS_LEFT,        MS_DOWN,        MS_RGHT,        KC_TRNS,                                                 KC_TRNS,        KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
      TD(TD_LCTL_BASE),KC_TRNS,        MS_BTN1,        MS_BTN3,        MS_BTN2,        KC_TRNS,        KC_TRNS,                 KC_TRNS,        KC_TRNS,        MS_BTN1,        MS_BTN3,        MS_BTN2,        KC_TRNS,        KC_TRNS,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                       KC_TRNS,        KC_TRNS,         KC_TRNS,                KC_TRNS,        KC_TRNS,        KC_TRNS
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_NUMBERS] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       TD(TD_GRV_ESC), KC_F10,         KC_F11,         KC_F12,         KC_PSCR,        KC_SCRL,                                                 KC_PAUSE,       KC_NUM,         KC_SLSH,        KC_ASTR,        KC_MINS,        KC_BSPC,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,        KC_F7,          KC_F8,          KC_F9,          KC_INSERT,      KC_HOME,                                                 KC_PGUP,        KC_7,           KC_8,           KC_9,           KC_PLUS,        KC_ENT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,        KC_F4,          KC_F5,          KC_F6,          KC_DELETE,      KC_END,                                                  KC_PGDN,        KC_4,           KC_5,           KC_6,           KC_COMM,        KC_ENT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
      TD(TD_LCTL_BASE),KC_F1,          KC_F2,          KC_F3,          KC_V,           KC_B,           KC_LBRC,                 KC_RBRC,        KC_0,           KC_1,           KC_2,           KC_3,           KC_EQL,         KC_TRNS,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                       KC_TRNS,        KC_TRNS,        KC_TRNS,                 KC_TRNS,        KC_0,           KC_DOT
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_SYMBOLS] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       TD(TD_GRV_ESC), TD(TD_1_FN),    TD(TD_2_NUM),   TD(TD_3_SYS),   TD(TD_4_GAME),  TD(TD_5_MACRO),                                          TD(TD_6_BS),    KC_7,           KC_8,           TD(TD_9_MIN),   TD(TD_0_EQ),    KC_BSPC,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                                    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_QUOT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
      TD(TD_LSFT_CAPS),KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                    KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_ENT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
      TD(TD_LCTL_BASE),KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRC,                 KC_RBRC,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,       TD(TD_BSLS_RSFT),
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                       KC_LGUI,        MO_FN,          KC_SPC,                  KC_SPC,         MO_NU,          KC_RCTL
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_SYSTEM] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_MY_COMPUTER, KC_TRNS,                                                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
      TD(TD_LCTL_BASE),KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,                 KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                      KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,  KC_AUDIO_VOL_UP,     TD(TD_MEDIA_PREV),TD(TD_MEDIA_PLAY),TD(TD_MEDIA_NEXT)
    //                                                                └───────────────┴───────────────┴───────────────┘        └───────────────┴───────────────┴───────────────┘
    ),

    [_GAMING] = LAYOUT(
    //┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐                                        ┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐
       KC_ESC,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                                    KC_6,           KC_7,           KC_8,           TD(TD_9_MIN),   TD(TD_0_EQ),    KC_BSPC,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                                    KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           TD(TD_ENT_BSLS),
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤                                        ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_LSFT,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                                    KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    //├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┐        ┌───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
       KC_LCTL,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRC,                 KC_RBRC,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_ENT,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                       KC_LGUI,       TD(TD_LCTL_BASE),KC_SPC,                  KC_SPC,         MO_NU,          KC_RCTL
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
      TD(TD_LCTL_BASE),  _______,        _______,        _______,        _______,        _______,        _______,                 _______,        _______,        _______,        _______,        _______,        _______,        _______,
    //└───────────────┴───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┘        └───────────────┼───────────────┼───────────────┼───────────────┴───────────────┴───────────────┴───────────────┘
                                                                       KC_LGUI,        MO_FN,          KC_SPC,                  KC_SPC,         MO_NU,          KC_RCTL
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
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
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

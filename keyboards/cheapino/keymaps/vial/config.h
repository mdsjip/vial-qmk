#pragma once

// Vial configuration
#define VIAL_KEYBOARD_UID {0x79, 0xED, 0x40, 0xBB, 0x09, 0x8B, 0xC1, 0x9E}
// Unlock combo is two inner thumb keys.
#define VIAL_UNLOCK_COMBO_ROWS { 6, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 11, 5 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 14

// Chordal Hold: Implements "opposite hands" rule for home row mods
// Only triggers hold when keys on opposite hands are pressed together
// This is the built-in QMK equivalent of Achordion
// NOTE: Chordal Hold requires either PERMISSIVE_HOLD or HOLD_ON_OTHER_KEY_PRESS to work
#ifndef CHORDAL_HOLD
#define CHORDAL_HOLD
#endif

// Home row mods configuration - optimized based on QMK docs and Pascal Getreuer's recommendations
// https://docs.qmk.fm/tap_hold
// https://getreuer.info/posts/keyboards/achordion/index.html

// Tapping term: Set relatively high for home row mods to avoid accidental activations
// Recommended range: 160-220ms for most users, 200-250ms for home row mods
// Override the keyboard.json default of 230ms with a slightly lower value
#undef TAPPING_TERM
#define TAPPING_TERM 200

// Permissive Hold: Immediately select hold action when another key is tapped (nested press)
// This is essential for home row mods to work well with fast typing
#define PERMISSIVE_HOLD

//// Hold on Other Key Press: Immediately select hold action when another key is pressed
//// This is more aggressive than PERMISSIVE_HOLD and works better with Chordal Hold
//// because it triggers the hold decision earlier, allowing Chordal Hold to intercept it
//#define HOLD_ON_OTHER_KEY_PRESS

// Quick Tap Term: Disable auto-repeat on home row mods to prevent accidental mod triggers
// Setting to 0 forces hold behavior when quickly tapping the same key
#define QUICK_TAP_TERM 0

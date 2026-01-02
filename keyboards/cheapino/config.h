// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral.
#define WS2812_PIO_USE_PIO1
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

// Encoders
#define NUM_ENCODERS 1
#define ENCODER_RESOLUTION 2
//#define NUM_ENCODERS_LEFT 0
//#define NUM_ENCODERS_RIGHT 1
//#define NUM_ENCODERS_MAX_PER_SIDE 1


#ifndef CHORDAL_HOLD
#    define CHORDAL_HOLD
#endif
#ifndef FLOW_TAP_TERM
#    define FLOW_TAP_TERM 150
#endif


// The default is 300. Let's try and make this as low as possible while keeping the cursor responsive
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0
// Set the mouse settings to a comfortable speed/accuracy trade-off,
// assuming a screen refresh rate of 60 Htz or higher
// The default is 50. This makes the mouse ~3 times faster and more accurate
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 16
// It makes sense to use the same delay for the mouseweel
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0
// The default is 20. Since we made the mouse about 3 times faster with the previous setting,
// give it more time to accelerate to max speed to retain precise control over short distances.
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 40
// The default is 100
#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL 50
// The default is 40
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

//#undef TAPPING_TERM
//#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// Auto Shift for numbers and symbols
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#ifndef FLOW_TAP_TERM
#define AUTO_SHIFT_NO_SETUP
#endif

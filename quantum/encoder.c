// Copyright 2022-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>
#include "action.h"
#include "encoder.h"
#include "wait.h"

#ifndef ENCODER_MAP_KEY_DELAY
#    define ENCODER_MAP_KEY_DELAY TAP_CODE_DELAY
#endif

__attribute__((weak)) bool should_process_encoder(void) {
    return is_keyboard_master();
}

static encoder_events_t encoder_events;
static bool             signal_queue_drain = false;

void encoder_init(void) {
    memset(&encoder_events, 0, sizeof(encoder_events));
    encoder_driver_init();
}

static void encoder_queue_drain(void) {
    encoder_events.tail     = encoder_events.head;
    encoder_events.dequeued = encoder_events.enqueued;
}

static bool encoder_handle_queue(void) {
    bool    changed = false;
    uint8_t index;
    bool    clockwise;
    while (encoder_dequeue_event(&index, &clockwise)) {
#ifdef ENCODER_MAP_ENABLE

        // The delays below cater for Windows and its wonderful requirements.
        action_exec(clockwise ? MAKE_ENCODER_CW_EVENT(index, true) : MAKE_ENCODER_CCW_EVENT(index, true));
#    if ENCODER_MAP_KEY_DELAY > 0
        wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

        action_exec(clockwise ? MAKE_ENCODER_CW_EVENT(index, false) : MAKE_ENCODER_CCW_EVENT(index, false));
#    if ENCODER_MAP_KEY_DELAY > 0
        wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

#else // ENCODER_MAP_ENABLE

        encoder_update_kb(index, clockwise);

#endif // ENCODER_MAP_ENABLE

        changed = true;
    }
    return changed;
}

bool encoder_task(void) {
    bool changed = false;

#ifdef SPLIT_KEYBOARD
    // Attempt to process existing encoder events in case split handling has already enqueued events
    if (should_process_encoder()) {
        changed |= encoder_handle_queue();
    }
#endif // SPLIT_KEYBOARD

    if (signal_queue_drain) {
        signal_queue_drain = false;
        encoder_queue_drain();
    }

    // Let the encoder driver produce events
    encoder_driver_task();

    // Process any events that were enqueued
    if (should_process_encoder()) {
        changed |= encoder_handle_queue();
    }

    return changed;
}

bool encoder_queue_full_advanced(encoder_events_t *events) {
    return events->tail == (events->head + 1) % MAX_QUEUED_ENCODER_EVENTS;
}

bool encoder_queue_full(void) {
    return encoder_queue_full_advanced(&encoder_events);
}

bool encoder_queue_empty_advanced(encoder_events_t *events) {
    return events->head == events->tail;
}

bool encoder_queue_empty(void) {
    return encoder_queue_empty_advanced(&encoder_events);
}

bool encoder_queue_event_advanced(encoder_events_t *events, uint8_t index, bool clockwise) {
    // Drop out if we're full
    if (encoder_queue_full_advanced(events)) {
        return false;
    }

    // Append the event
    encoder_event_t new_event   = {.index = index, .clockwise = clockwise ? 1 : 0};
    events->queue[events->head] = new_event;

    // Increment the head index
    events->head = (events->head + 1) % MAX_QUEUED_ENCODER_EVENTS;
    events->enqueued++;

    return true;
}

bool encoder_dequeue_event_advanced(encoder_events_t *events, uint8_t *index, bool *clockwise) {
    if (encoder_queue_empty_advanced(events)) {
        return false;
    }

    // Retrieve the event
    encoder_event_t event = events->queue[events->tail];
    *index                = event.index;
    *clockwise            = event.clockwise;

    // Increment the tail index
    events->tail = (events->tail + 1) % MAX_QUEUED_ENCODER_EVENTS;
    events->dequeued++;

    return true;
}

bool encoder_queue_event(uint8_t index, bool clockwise) {
    return encoder_queue_event_advanced(&encoder_events, index, clockwise);
}

bool encoder_dequeue_event(uint8_t *index, bool *clockwise) {
    return encoder_dequeue_event_advanced(&encoder_events, index, clockwise);
}

void encoder_retrieve_events(encoder_events_t *events) {
    memcpy(events, &encoder_events, sizeof(encoder_events));
}

void encoder_signal_queue_drain(void) {
    signal_queue_drain = true;
}

__attribute__((weak)) bool encoder_update_user(uint8_t index, bool clockwise) {
    return true;
}

__attribute__((weak)) bool encoder_update_kb(uint8_t index, bool clockwise) {
    bool res = encoder_update_user(index, clockwise);
#if !defined(ENCODER_TESTS)
    if (res) {
        if (clockwise) {
#    if defined(EXTRAKEY_ENABLE)
            tap_code_delay(KC_VOLU, 10);
#    elif defined(MOUSEKEY_ENABLE)
            tap_code_delay(QK_MOUSE_WHEEL_UP, 10);
#    else
            tap_code_delay(KC_PGDN, 10);
#    endif
        } else {
#    if defined(EXTRAKEY_ENABLE)
            tap_code_delay(KC_VOLD, 10);
#    elif defined(MOUSEKEY_ENABLE)
            tap_code_delay(QK_MOUSE_WHEEL_DOWN, 10);
#    else
            tap_code_delay(KC_PGUP, 10);
#    endif
        }
    }
#endif // ENCODER_TESTS
    return res;
}

__attribute__((weak)) bool should_process_encoder(void) {
    return is_keyboard_master();
}

void encoder_init(void) {
#ifdef SPLIT_KEYBOARD
    thisHand  = isLeftHand ? 0 : NUM_ENCODERS_LEFT;
    thatHand  = NUM_ENCODERS_LEFT - thisHand;
    thisCount = isLeftHand ? NUM_ENCODERS_LEFT : NUM_ENCODERS_RIGHT;
    thatCount = isLeftHand ? NUM_ENCODERS_RIGHT : NUM_ENCODERS_LEFT;
#else // SPLIT_KEYBOARD
    thisCount                = NUM_ENCODERS;
#endif

#ifdef ENCODER_TESTS
    // Annoying that we have to clear out values during initialisation here, but
    // because all the arrays are static locals, rerunning tests in the same
    // executable doesn't reset any of these. Kinda crappy having test-only code
    // here, but it's the simplest solution.
    memset(encoder_value, 0, sizeof(encoder_value));
    memset(encoder_state, 0, sizeof(encoder_state));
    memset(encoder_pulses, 0, sizeof(encoder_pulses));
    static const pin_t encoders_pad_a_left[] = ENCODERS_PAD_A;
    static const pin_t encoders_pad_b_left[] = ENCODERS_PAD_B;
    for (uint8_t i = 0; i < thisCount; i++) {
        encoders_pad_a[i] = encoders_pad_a_left[i];
        encoders_pad_b[i] = encoders_pad_b_left[i];
    }
#endif

#if defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)
    // Re-initialise the pads if it's the right-hand side
    if (!isLeftHand) {
        static const pin_t encoders_pad_a_right[] = ENCODERS_PAD_A_RIGHT;
        static const pin_t encoders_pad_b_right[] = ENCODERS_PAD_B_RIGHT;
        for (uint8_t i = 0; i < thisCount; i++) {
            encoders_pad_a[i] = encoders_pad_a_right[i];
            encoders_pad_b[i] = encoders_pad_b_right[i];
        }
    }
#endif // defined(SPLIT_KEYBOARD) && defined(ENCODERS_PAD_A_RIGHT) && defined(ENCODERS_PAD_B_RIGHT)

    // Encoder resolutions is handled purely master-side, so concatenate the two arrays
#if defined(SPLIT_KEYBOARD) && defined(ENCODER_RESOLUTIONS)
#    if defined(ENCODER_RESOLUTIONS_RIGHT)
    static const uint8_t encoder_resolutions_right[NUM_ENCODERS_RIGHT] = ENCODER_RESOLUTIONS_RIGHT;
#    else  // defined(ENCODER_RESOLUTIONS_RIGHT)
    static const uint8_t encoder_resolutions_right[NUM_ENCODERS_RIGHT] = ENCODER_RESOLUTIONS;
#    endif // defined(ENCODER_RESOLUTIONS_RIGHT)
    for (uint8_t i = 0; i < NUM_ENCODERS_RIGHT; i++) {
        encoder_resolutions[NUM_ENCODERS_LEFT + i] = encoder_resolutions_right[i];
    }
#endif // defined(SPLIT_KEYBOARD) && defined(ENCODER_RESOLUTIONS)

    for (uint8_t i = 0; i < thisCount; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);
    }
    encoder_wait_pullup_charge();
    for (uint8_t i = 0; i < thisCount; i++) {
        encoder_state[i] = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
    }
}

#ifdef ENCODER_MAP_ENABLE
__attribute__((weak)) void encoder_exec_mapping(uint8_t index, bool clockwise) {
    // The delays below cater for Windows and its wonderful requirements.
    action_exec(clockwise ? MAKE_ENCODER_CW_EVENT(index, true) : MAKE_ENCODER_CCW_EVENT(index, true));
#    if ENCODER_MAP_KEY_DELAY > 0
    wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0

    action_exec(clockwise ? MAKE_ENCODER_CW_EVENT(index, false) : MAKE_ENCODER_CCW_EVENT(index, false));
#    if ENCODER_MAP_KEY_DELAY > 0
    wait_ms(ENCODER_MAP_KEY_DELAY);
#    endif // ENCODER_MAP_KEY_DELAY > 0
}
#endif // ENCODER_MAP_ENABLE

static bool encoder_update(uint8_t index, uint8_t state) {
    bool    changed = false;
    uint8_t i       = index;

#ifdef ENCODER_RESOLUTIONS
    const uint8_t resolution = encoder_resolutions[i];
#else
    const uint8_t resolution = ENCODER_RESOLUTION;
#endif

#ifdef SPLIT_KEYBOARD
    index += thisHand;
#endif
    encoder_pulses[i] += encoder_LUT[state & 0xF];

#ifdef ENCODER_DEFAULT_POS
    if ((encoder_pulses[i] >= resolution) || (encoder_pulses[i] <= -resolution) || ((state & 0x3) == ENCODER_DEFAULT_POS)) {
        if (encoder_pulses[i] >= 1) {
#else
    if (encoder_pulses[i] >= resolution) {
#endif

            encoder_value[index]++;
            changed = true;
#ifdef SPLIT_KEYBOARD
            if (should_process_encoder())
#endif // SPLIT_KEYBOARD
#ifdef ENCODER_MAP_ENABLE
                encoder_exec_mapping(index, ENCODER_COUNTER_CLOCKWISE);
#else  // ENCODER_MAP_ENABLE
        encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
#endif // ENCODER_MAP_ENABLE
        }

#ifdef ENCODER_DEFAULT_POS
        if (encoder_pulses[i] <= -1) {
#else
    if (encoder_pulses[i] <= -resolution) { // direction is arbitrary here, but this clockwise
#endif
            encoder_value[index]--;
            changed = true;
#ifdef SPLIT_KEYBOARD
            if (should_process_encoder())
#endif // SPLIT_KEYBOARD
#ifdef ENCODER_MAP_ENABLE
                encoder_exec_mapping(index, ENCODER_CLOCKWISE);
#else  // ENCODER_MAP_ENABLE
        encoder_update_kb(index, ENCODER_CLOCKWISE);
#endif // ENCODER_MAP_ENABLE
        }
        encoder_pulses[i] %= resolution;
#ifdef ENCODER_DEFAULT_POS
        encoder_pulses[i] = 0;
    }
#endif
    return changed;
}

bool encoder_read(void) {
    bool changed = false;
    for (uint8_t i = 0; i < thisCount; i++) {
        uint8_t new_status = (readPin(encoders_pad_a[i]) << 0) | (readPin(encoders_pad_b[i]) << 1);
        if ((encoder_state[i] & 0x3) != new_status) {
            encoder_state[i] <<= 2;
            encoder_state[i] |= new_status;
            changed |= encoder_update(i, encoder_state[i]);
        }
    }
    return changed;
}

#ifdef SPLIT_KEYBOARD
void last_encoder_activity_trigger(void);

void encoder_state_raw(uint8_t *slave_state) {
    memcpy(slave_state, &encoder_value[thisHand], sizeof(uint8_t) * thisCount);
}

void encoder_update_raw(uint8_t *slave_state) {
    bool changed = false;
    for (uint8_t i = 0; i < thatCount; i++) { // Note inverted logic -- we want the opposite side
        const uint8_t index = i + thatHand;
        int8_t        delta = slave_state[i] - encoder_value[index];
        while (delta > 0) {
            delta--;
            encoder_value[index]++;
            changed = true;
#    ifdef ENCODER_MAP_ENABLE
            encoder_exec_mapping(index, ENCODER_COUNTER_CLOCKWISE);
#    else  // ENCODER_MAP_ENABLE
            encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
#    endif // ENCODER_MAP_ENABLE
        }
        while (delta < 0) {
            delta++;
            encoder_value[index]--;
            changed = true;
#    ifdef ENCODER_MAP_ENABLE
            encoder_exec_mapping(index, ENCODER_CLOCKWISE);
#    else  // ENCODER_MAP_ENABLE
            encoder_update_kb(index, ENCODER_CLOCKWISE);
#    endif // ENCODER_MAP_ENABLE
        }
    }

    // Update the last encoder input time -- handled external to encoder_read() when we're running a split
    if (changed) last_encoder_activity_trigger();
}
#endif

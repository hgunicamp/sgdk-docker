#include "../inc/joystick_mediator.h"

#define JOY_DPAD_MASK 0x000f
#define JOY_BUTTON_MASK 0x0ff0

joystick_event_struct joy_last_event[JOY_MAX_NUMBER];
u16 joy_last_frame[JOY_MAX_NUMBER];

void joystick_mediator_reduce_locking_time(joystick_mediator_struct *mediator) {
    if (mediator->dpad_lock_frames) mediator->dpad_lock_frames--;
    if (mediator->button_lock_frames) mediator->button_lock_frames--;
}

void joystick_init(u16 joy) {
    joy_last_event[joy].dpad_event = JOY_DPAD_IDLE;
    joy_last_event[joy].button_event = JOY_BUTTON_IDLE;
    joy_last_frame[joy] = 0x0000;
}

#define JOY_DPAD_EVENT(current_events, current_state, key)  \
    current_events |= (BUTTON_##key & current_state) ? JOY_DPAD_PRESSED_##key :  JOY_DPAD_RELEASED_##key

#define JOY_BUTTON_EVENT(current_events, current_state, key)  \
    current_events |= (BUTTON_##key & current_state) ? JOY_BUTTON_PRESSED_##key : JOY_BUTTON_RELEASED_##key

u16 joystick_update_dpad_event(u16 current_state) {
    u16 current_dpad_events = 0x00;

    JOY_DPAD_EVENT(current_dpad_events, current_state, UP);
    JOY_DPAD_EVENT(current_dpad_events, current_state, DOWN);
    JOY_DPAD_EVENT(current_dpad_events, current_state, LEFT);
    JOY_DPAD_EVENT(current_dpad_events, current_state,  RIGHT);

    return current_dpad_events;
}

u16 joystick_update_button_event(u16 current_state) {
    u32 current_button_events = 0x000;

    JOY_BUTTON_EVENT(current_button_events, current_state, A);
    JOY_BUTTON_EVENT(current_button_events, current_state, B);
    JOY_BUTTON_EVENT(current_button_events, current_state, C);
    JOY_BUTTON_EVENT(current_button_events, current_state, X);
    JOY_BUTTON_EVENT(current_button_events, current_state, Y);
    JOY_BUTTON_EVENT(current_button_events, current_state, Z);
    JOY_BUTTON_EVENT(current_button_events, current_state, START);

    return current_button_events;
}

void joystick_update_last_event(u16 joy) {
    u16 joy_current_state = JOY_readJoypad(joy);
    u16 difference = joy_current_state ^ joy_last_frame[joy];
    joy_last_frame[joy] = joy_current_state;

    joy_last_event[joy].dpad_chaged = (difference & JOY_DPAD_MASK) != 0;
    joy_last_event[joy].action_changed = (difference & JOY_BUTTON_MASK) != 0;

    if (joy_last_event[joy].dpad_chaged)
        joy_last_event[joy].dpad_event = joystick_update_dpad_event(joy_current_state);
    if (joy_last_event[joy].action_changed)
        joy_last_event[joy].button_event = joystick_update_button_event(joy_current_state);
}

void joystick_update_state_after_frame(joystick_mediator_struct *mediator) {
    joystick_mediator_reduce_locking_time(mediator);
    joystick_update_last_event(mediator->joy);
}

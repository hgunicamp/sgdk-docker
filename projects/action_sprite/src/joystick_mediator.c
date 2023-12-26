#include "../inc/joystick_mediator.h"

u16 joy_last_event[JOY_NUM] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };

u16 joystick_mediator_no_button_action(joystick_mediator_struct *mediator) {
    return JOY_NO_ACTION_TAKEN;
}

void joystick_mediator_reduce_locking_time(joystick_mediator_struct *mediator) {
    if (!(mediator->lock_frames)) return;
    mediator->lock_frames--;
}

void joystick_event_listener(u16 joy, u16 changed, u16 state) {
    if (!changed) return;
    joy_last_event[joy] = state;
}

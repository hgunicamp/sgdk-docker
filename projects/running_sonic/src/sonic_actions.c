#include <types.h>
#include <vdp.h>
#include <vdp_tile.h>
#include "../inc/sprite.h"
#include "../inc/states.h"
#include "../inc/sonic_actions.h"
#include "../inc/joystick_mediator.h"

joystick_mediator_struct sonic_joy_mediator;

const u16 SONIC_ANIMATION[] = { 1, 0, 2, 3, 4, 5, 6 };

void set_sonic_animation(joystick_mediator_struct *mediator, enum states state) {
    sprite_struct *sonic = (sprite_struct *) mediator->resource_index;
    mediator->world_state->state = state;
    sonic->current_animation_index = SONIC_ANIMATION[state];
    SPR_setAnim(sonic->sprite, SONIC_ANIMATION[state]);
    SPR_setHFlip(sonic->sprite, !(mediator->world_state->facing_right));
}

void sonic_set_idle_state(joystick_mediator_struct *mediator) {
    set_sonic_animation(mediator, ST_IDLE);
}

void sonic_set_flip_state(joystick_mediator_struct *mediator) {
    mediator->world_state->facing_right = !(mediator->world_state->facing_right);
    mediator->dpad_lock_frames = 12;
    set_sonic_animation(mediator, ST_FLIP);
}

void sonic_set_speeding_up_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 15;
    set_sonic_animation(mediator, ST_SPEED_UP);
}

void sonic_set_running_state(joystick_mediator_struct *mediator) {
    set_sonic_animation(mediator, ST_RUNNING);
}

void sonic_set_slow_dow_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 20;
    set_sonic_animation(mediator, ST_SLOW_DOWN);
}

void sonic_set_face_up_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 12;
    set_sonic_animation(mediator, ST_FACING_UP);
}

void sonic_set_face_dow_state(joystick_mediator_struct *mediator) {
    mediator->dpad_lock_frames = 12;
    set_sonic_animation(mediator, ST_FACING_DOWN);
}

void (*functions[])(joystick_mediator_struct *mediator) = {
    sonic_set_idle_state,
    sonic_set_flip_state,
    sonic_set_speeding_up_state,
    sonic_set_running_state,
    sonic_set_slow_dow_state,
    sonic_set_face_up_state,
    sonic_set_face_dow_state
};

#define SONIC_CONNECT_STRUCTURES(mediator, ptr_sprite, ptr_world_state) do { \
    ptr_world_state->state = ST_IDLE; \
    ptr_world_state->facing_right = TRUE; \
    mediator.world_state = ptr_world_state; \
    mediator.resource_index = (void *) ptr_sprite; \
    mediator.dpad_lock_frames = 0; \
    mediator.button_lock_frames = 0; \
    mediator.joy = JOY_1; \
    mediator.actions = functions; \
} while(0)

void install_sonic_sprite(
    sprite_struct *sonic,
    const SpriteDefinition *sonic_sprite,
    state_struct *world_state
) {
    SONIC_CONNECT_STRUCTURES(sonic_joy_mediator, sonic, world_state);
}

#define IS_SONIC_FACING_RIGHT() (sonic_joy_mediator.world_state->facing_right)

////////////////// Transition functions. //////////////////////////
/**
 * \brief
 *     Handles the event of hold RIGHT on the joystick's DPAD.
 * \param current_state
 *     Current mesured dpad state.
 */
void sonic_handle_dpad_hold_right(enum states current_state) {
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_IDLE && !IS_SONIC_FACING_RIGHT(), ST_FLIP, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE((current_state == ST_IDLE || current_state == ST_FLIP) && IS_SONIC_FACING_RIGHT(), ST_SPEED_UP, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_SPEED_UP, ST_RUNNING, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_RUNNING && !IS_SONIC_FACING_RIGHT(), ST_SLOW_DOWN,dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_SLOW_DOWN && !IS_SONIC_FACING_RIGHT(), ST_FLIP, dpad, (&sonic_joy_mediator));
}

/**
 * \brief
 *     Handles the event of hold LEFT on the joystick's DPAD.
 * \param current_state
 *     Current mesured dpad state.
 */
void sonic_handle_dpad_hold_left(enum states current_state) {
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_IDLE && IS_SONIC_FACING_RIGHT(), ST_FLIP, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE((current_state == ST_IDLE || current_state == ST_FLIP) && !IS_SONIC_FACING_RIGHT(), ST_SPEED_UP, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_SPEED_UP, ST_RUNNING, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_RUNNING && IS_SONIC_FACING_RIGHT(), ST_SLOW_DOWN, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_SLOW_DOWN && IS_SONIC_FACING_RIGHT(), ST_FLIP, dpad, (&sonic_joy_mediator));
}

/**
 * \brief
 *     Handles the event of hold UP on the joystick's DPAD.
 * \param current_state
 *     Current mesured dpad state.
 */
void sonic_handle_dpad_hold_up(enum states current_state) {
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_IDLE, ST_FACING_UP, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_RUNNING, ST_SLOW_DOWN, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_SLOW_DOWN, ST_FACING_UP, dpad, (&sonic_joy_mediator));
}

/**
 * \brief
 *     Handles the event of hold DOWN on the joystick's DPAD.
 * \param current_state
 *     Current mesured dpad state.
 */
void sonic_handle_dpad_hold_down(enum states current_state) {
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_IDLE, ST_FACING_DOWN, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_RUNNING, ST_SLOW_DOWN, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_SLOW_DOWN, ST_FACING_DOWN, dpad, (&sonic_joy_mediator));
}

/**
 * \brief
 *     Handles the event of IDLE the joystick's DPAD.
 * \param current_state
 *     Current mesured dpad state.
 */
void sonic_handle_dpad_idle(enum states current_state) {
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_RUNNING, ST_SLOW_DOWN, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_SLOW_DOWN, ST_IDLE, dpad, (&sonic_joy_mediator));
    JOY_HANDLE_EVENT_TEMPLATE(current_state == ST_FLIP, ST_IDLE, dpad, (&sonic_joy_mediator));
}

enum dpad_event { DPAD_IDLE, DPAD_LEFT, DPAD_RIGHT, DPAD_UP, DPAD_DOWN };

#define SONIC_TRIGGER_JOY_DPAD_EVENT(key, handle_func) if (dpad_events[key]) handle_func(sonic_joy_mediator.world_state->state)

/** 
 * \brief
 *     Interpret the dpad events.
 */
void sonic_interpret_joystick_status() {
    joystick_event_struct current_event = JOY_GET_CURRENT_EVENT(sonic_joy_mediator.joy);
    enum dpad_event dpad_events[] = {
        JOY_HANDLE_FILTER_JOYSTICK_EXCLUSIVE_EVENT(JOY_DPAD_IDLE, current_event.dpad_event),
        JOY_HANDLE_FILTER_JOYSTICK_EVENT(JOY_DPAD_PRESSED_LEFT, current_event.dpad_event),
        JOY_HANDLE_FILTER_JOYSTICK_EVENT(JOY_DPAD_PRESSED_RIGHT, current_event.dpad_event),
        JOY_HANDLE_FILTER_JOYSTICK_EXCLUSIVE_EVENT(JOY_DPAD_PRESSED_UP, current_event.dpad_event),
        JOY_HANDLE_FILTER_JOYSTICK_EXCLUSIVE_EVENT(JOY_DPAD_PRESSED_DOWN, current_event.dpad_event),
    };

    SONIC_TRIGGER_JOY_DPAD_EVENT(DPAD_IDLE, sonic_handle_dpad_idle);
    SONIC_TRIGGER_JOY_DPAD_EVENT(DPAD_LEFT, sonic_handle_dpad_hold_left);
    SONIC_TRIGGER_JOY_DPAD_EVENT(DPAD_RIGHT, sonic_handle_dpad_hold_right);
    SONIC_TRIGGER_JOY_DPAD_EVENT(DPAD_UP, sonic_handle_dpad_hold_up);
    SONIC_TRIGGER_JOY_DPAD_EVENT(DPAD_DOWN, sonic_handle_dpad_hold_down);
}

void update_sonic_sprite_after_frame() {
    sonic_interpret_joystick_status();
    joystick_update_state_after_frame(&sonic_joy_mediator);
}
